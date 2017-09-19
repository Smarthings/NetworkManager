/*
 * File:   mainForm.cpp
 * Author: warren
 *
 * Created on October 25, 2012, 11:43 AM
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <climits>
#include <QtCore>
#include <QString>
#include <QThread>
#include <QEventLoop>
#include <QtWidgets>
#include <QDateTime>
#include <QHeaderView>
#include <QAbstractItemModel>
#include <QMainWindow>
#include <QMessageBox>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/regex.hpp>
#include "Custom.h"
#include "MainForm.h"
#include "Getter.h"
#include "AboutBox.h"
#include "passBox.h"
#include "prefsDialog.h"
#include "ui_MainForm.h"

extern int lastBlockRequested;
extern int lastBlockReceived;
extern qint64 startTime;
extern string endBlockString;
extern string pipeName;
extern ofstream linssidLog;
extern bool closing;

extern string genPipeName(int);

using namespace std;

// define a few things

// the cellData structure is replicated for each attach point (cell) found

struct MainForm::cellData {
    string macAddr;
    string essid;
    string mode; // master, managed, etc.
    string security; // on or off
    string privacy; // group cipher
    string cipher; // pairwise cipher
    int channel;
    string frequency;
    string protocol; // b,g,n,ac
    int quality; // per microsoft definition, derived from signal
    int signal; // try to get dBm
    int minSignal; // lowest seen
    int maxSignal; // highest seen
    int BW; // max BW in any protocol 20 or 40 or 80 or 160 MHz
    int cenChan; // center channel in 40/80/160 MHz bandwidths
    string vendor;
    long firstSeen;
    long lastSeen;
    string netType;
    QColor color;
    QwtPlotCurve* pBandCurve;
    double xPlot[4];
    double yPlot[4];
    History* pHistory;
    QwtPlotCurve* pTimeCurve;
    QTableWidgetItem * pTableItem[MAX_TABLE_COLS];
    int timesSeen; // believe it or not, some drivers report a MAC more than once per scan
};

struct MainForm::History {
    // This structure is created to record the history of each cell. It's a ring buffer.
    // Sample buffers are TWICE the size needed so that we can efficiently give the
    // plotting package contiguous arrays of size MAX_SAMPLES. Each sample is entered
    // twice: at index 0<=i<MAX_SAMPLES and again at MAX_SAMPLES <= i+MAX_SAMPLES  < (MAX_SAMPLES * 2)
    int totalSamples; // modulo max_samples gives index into sample array
    double sampleSec[MAX_SAMPLES * 2];
    double signal[MAX_SAMPLES * 2];
};

struct MainForm::vendorStruct {
    unsigned int ID;
    string name;
};

struct MainForm::sSort {
    int column;
    int order;
};

struct MainForm::sMaingeom {
    int x;
    int y;
    int width;
    int height;
};

struct MainForm::sMainsplit {
    int topheight;
    int bottomheight;
};

struct MainForm::sPlotprefs {
    int plotlb;
    int plutub;
    bool showgrid;
};

struct MainForm::sDefPref {
    string version;
    int colwidth[MAX_TABLE_COLS];
    bool colvis[MAX_TABLE_COLS];
    int visorder[MAX_TABLE_COLS];
    sSort sort;
    sMaingeom maingeom;
    sMainsplit mainsplit;
    int plottab;
    int naptime;
    sPlotprefs plotprefs;
    int logData;
};



// declare some variables
Getter* MainForm::pGetter; // a pointer to our data getter
QThread* MainForm::pGetterThread; // a pointer to its thread
vector<MainForm::cellData> MainForm::cellDataRay;
MainForm::vendorStruct* MainForm::vendor;
fstream MainForm::logDataStream;
int MainForm::maxTableIndex; // holds the highest index pointer into cellData
int MainForm::numVendors;
int MainForm::maxVendorRecL;
long MainForm::runStartTime;
long MainForm::now; // absolute time of the block
pageBlockType pageBlock; // which section of page is data coming from
int MainForm::logDataState;
long MainForm::blockSampleTime; // time of the block relative to runStartTime
bool MainForm::firstScan; // do we need to get sudo privileges?

string MainForm::chan24Freq[15] {
    "0.000","2.412","2.417","2.422","2.427",
    "2.432","2.437","2.442","2.447","2.452",
    "2.457","2.462","2.467","2.472","2.484"
};
string MainForm::chan50Freq[42][2] {
    {"7","5.035"},{"8","5.040"},{"9","5.045"},
    {"11","5.055"},{"12","5.060"},{"16","5.080"},
    {"34","5.170"},{"36","5.180"},{"38","5.190"},
    {"40","5.200"},{"42","5.210"},{"44","5.220"},
    {"46","5.230"},{"48","5.240"},{"52","5.260"},
    {"56","5.280"},{"60","5.300"},{"64","5.320"},
    {"100","5.500"},{"104","5.520"},{"108","5.540"},
    {"112","5.560"},{"116","5.580"},{"120","5.600"},
    {"124","5.620"},{"128","5.640"},{"132","5.660"},
    {"136","5.680"},{"140","5.700"},{"149","5.745"},
    {"153","5.765"},{"157","5.785"},{"161","5.805"},
    {"165","5.825"},{"183","4.915"},{"184","4.920"},
    {"185","4.925"},{"187","4.935"},{"188","4.940"},
    {"189","4.945"},{"192","4.960"},{"196","4.980"}
};
QColor MainForm::qColorArray[NUMBER_OF_COLORS]
{
    Qt::red, Qt::green, Qt::blue, Qt::darkRed, Qt::darkGreen, Qt::darkBlue,
            Qt::cyan, Qt::magenta, Qt::gray, Qt::darkCyan, Qt::darkMagenta,
            Qt::darkYellow, Qt::darkGray
};
QAction* MainForm::colToQAction[MAX_TABLE_COLS];
int MainForm::columnWidth[MAX_TABLE_COLS]; // since Qt doesn't see fit to remember for us...
QwtPlotGrid* MainForm::chan24Grid;
QwtPlotGrid* MainForm::chan5Grid;
QwtPlotGrid* MainForm::timeGrid;
prefsDialog* MainForm::prefsDlg1;
MainForm::sDefPref MainForm::defPref = {// default prefs defined here
    /* version  */ LINSSIDPREFSVER,
    /* colwidth */
    {100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
    /* colvis   */
    {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    /* visorder */
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18},
    /* sort     */
    { 18, 1},
    /* maingeom */
    {389, 83, 721, 542},
    ///* mainsplit*/
    {154, 223},
    /* plottab  */ 0,
    /* naptime  */ 2,
    /* plotprefs*/
    {-100, -20, 1},
    /* logdata */ 0
};

MainForm::MainForm() {

    MainForm::mainFormWidget.setupUi(this);
    connect(MainForm::mainFormWidget.runBtn, SIGNAL(clicked()), this, SLOT(doRun()));
    connect(MainForm::mainFormWidget.allBtn, SIGNAL(clicked()), this, SLOT(doPlotAll()));
    connect(MainForm::mainFormWidget.noneBtn, SIGNAL(clicked()), this, SLOT(doPlotNone()));
    connect(MainForm::mainFormWidget.mainTableWidget, SIGNAL(cellChanged(int,int)),
        this,SLOT(doTableChanged(int,int)));
    connect(MainForm::mainFormWidget.actionSSID, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionMAC, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionChannel, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionMode, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionProtocol, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionSecurity, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionPrivacy, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionCipher, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionFrequency, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionQuality, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionSignal, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionBW, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionMin_Signal, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionMax_Signal, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionCenChan, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionFirst_Seen, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionLast_Seen, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionVendor, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionType, SIGNAL(changed()), this, SLOT(reDrawTable()));
    connect(MainForm::mainFormWidget.actionAbout, SIGNAL(triggered()), this, SLOT(showAboutBox()));
    connect(MainForm::mainFormWidget.actionPrefs, SIGNAL(triggered()), this, SLOT(showPrefsDlg()));
    connect(MainForm::mainFormWidget.mainTableWidget->horizontalHeader(),
            SIGNAL(sectionResized(int, int, int)), this, SLOT(columnWidthSave(int, int, int)));

    MainForm::cellDataRay.reserve(15); // expect about 15 cells to be found. More or less is OK.
    lastBlockRequested = 0; // these global variables should be made protected
    lastBlockReceived = 0;
    startTime = QDateTime::currentMSecsSinceEpoch();
    MainForm::firstScan = true;
}

MainForm::~MainForm() {
    MainForm::pGetter->quit();
}

void MainForm::init() {
    srand(time(NULL)); //initialize the random number generator seed
    MainForm::getUserID(); // will exit here if needed and can't get
    MainForm::addInterfaces(); // find the wifi interface names and add them to the comboBox
    MainForm::setInterface(0); // set the interface select arbitrarily to 0
    MainForm::maxTableIndex = -1;
    MainForm::drawTable();
    MainForm::initPlotGrids(); // must do before reading prefs, since prefs will modify
    MainForm::initColtoAction(); // init pointers to view menu items
    MainForm::readPrefsFile();
    MainForm::drawTable(); // do it again after application of prefs
    MainForm::drawChan24Plot();
    MainForm::drawChan5Plot();
    MainForm::drawTimePlot();
    MainForm::loadVendorDb(); // do last 'cause it takes some time
}
// saving as comments in case ever need it again...
// reimplemented from QApplication so we can throw exceptions in slots

//virtual bool notify(QObject * receiver, QEvent * event) {
//    try {
//        return QApplication::notify(receiver, event);
//    } catch (std::exception& e) {
//        qCritical() << "Exception thrown:" << e.what();
//        linssidLog << "Exception caught by notify: " << e.what() << endl;
//    }
//    return false;
//}

void MainForm::initColtoAction() {
    // brutal -- set the array of pointers from columns to their menu items
    // these should have the same elements as the enum in 'custom.h'
    // PLOT, SSID, MAC, CHANNEL, MODE, SECURITY, PRIVACY,
    // CIPHER, FREQUENCY, QUALITY, SIGNAL, BW, MINSIGNAL, MAXSIGNAL, CENCHAN,
    // FIRST_SEEN, LAST_SEEN, VENDOR, PROTOCOL
    MainForm::colToQAction[PLOT] = MainForm::mainFormWidget.actionPlot;
    MainForm::colToQAction[SSID] = MainForm::mainFormWidget.actionSSID;
    MainForm::colToQAction[MAC] = MainForm::mainFormWidget.actionMAC;
    MainForm::colToQAction[CHANNEL] = MainForm::mainFormWidget.actionChannel;
    MainForm::colToQAction[MODE] = MainForm::mainFormWidget.actionMode;
    MainForm::colToQAction[PROTOCOL] = MainForm::mainFormWidget.actionProtocol;
    MainForm::colToQAction[SECURITY] = MainForm::mainFormWidget.actionSecurity;
    MainForm::colToQAction[PRIVACY] = MainForm::mainFormWidget.actionPrivacy;
    MainForm::colToQAction[CIPHER] = MainForm::mainFormWidget.actionCipher;
    MainForm::colToQAction[FREQUENCY] = MainForm::mainFormWidget.actionFrequency;
    MainForm::colToQAction[QUALITY] = MainForm::mainFormWidget.actionQuality;
    MainForm::colToQAction[SIGNAL] = MainForm::mainFormWidget.actionSignal;
    MainForm::colToQAction[BW] = MainForm::mainFormWidget.actionBW;
    MainForm::colToQAction[MINSIGNAL] = MainForm::mainFormWidget.actionMin_Signal;
    MainForm::colToQAction[MAXSIGNAL] = MainForm::mainFormWidget.actionMax_Signal;
    MainForm::colToQAction[CENCHAN] = MainForm::mainFormWidget.actionCenChan;
    MainForm::colToQAction[FIRST_SEEN] = MainForm::mainFormWidget.actionFirst_Seen;
    MainForm::colToQAction[LAST_SEEN] = MainForm::mainFormWidget.actionLast_Seen;
    MainForm::colToQAction[VENDOR] = MainForm::mainFormWidget.actionVendor;
}

void MainForm::initPlotGrids() {
    // add some grids to our plots
    MainForm::chan24Grid = new QwtPlotGrid();
    MainForm::chan24Grid->enableX(false);
    MainForm::chan24Grid->attach(MainForm::mainFormWidget.chan24Plot);
    MainForm::chan5Grid = new QwtPlotGrid();
    MainForm::chan5Grid->enableX(false);
    MainForm::chan5Grid->attach(MainForm::mainFormWidget.chan5Plot);
    MainForm::timeGrid = new QwtPlotGrid();
    MainForm::timeGrid->enableX(false);
    MainForm::timeGrid->attach(MainForm::mainFormWidget.timePlot);
}

void MainForm::loadVendorDb() {
    // now deal with the vendor data array
    // first record is number of vendors then max record length
    ifstream vendorFile;
    vendorFile.open(VENDOR_FILE_NAME, ios::in);
    vendorFile >> MainForm::numVendors >> MainForm::maxVendorRecL;
    string tempString;
    // load vendor array with ID and name
    MainForm::vendor = new MainForm::vendorStruct[MainForm::numVendors];
    int vRecNo = 0;
    istringstream tempStream;
    getline(vendorFile, tempString); // clear the end of line above
    while (getline(vendorFile, tempString)) {
        tempStream.str(tempString.substr(0, 6));
        tempStream.clear();
        tempStream >> hex >> MainForm::vendor[vRecNo].ID;
        MainForm::vendor[vRecNo].name = tempString.substr(6);
        vRecNo++;
    }
    vendorFile.close();
}

string MainForm::findVendor(string MACaddr) {
    int left = 0;
    int right = MainForm::numVendors - 1;
    int mid;
    istringstream convert(MACaddr.substr(0, 2) + MACaddr.substr(3, 2) + MACaddr.substr(6, 2));
    unsigned int key;
    convert >> hex >> key;
    while (left <= right) {
        mid = (int) ((left + right) / 2);
        if (key == MainForm::vendor[mid].ID) {
            return MainForm::vendor[mid].name;
        } else if (key > MainForm::vendor[mid].ID)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return "<unrecognized>";
}

void MainForm::getUserID() {
    // must get userid to get full interface scan
    if (geteuid() == 0) {
        pwStatus = NOTNEEDED; // must be running as root or with root privilege
    } else {
        passBox pwDialog1;
        for (int pwTry = 0; pwTry < 3; pwTry++) {
            if (pwTry == 0) pwDialog1.setPassPrompt("First shot:");
            else if (pwTry == 1) pwDialog1.setPassPrompt("Second try:");
            else pwDialog1.setPassPrompt("Last chance!");
            // pwDialog1.show();
            pwDialog1.exec();
            if (pwStatus == CANCELLED) {
                MainForm::mainFormWidget.runBtn->setChecked(false);
                //return;
                break;
            }
            if (pwStatus == GOOD) break;
        }
        if (pwStatus == BAD || pwStatus == CANCELLED) {
            MainForm::mainFormWidget.runBtn->setChecked(false);
            QMessageBox::warning(0, "password fail", "Unable to verify password");
            exit(1);
        }
    }
}

void MainForm::addInterfaces() {
    string somePipeName = genPipeName(10);
    string eof = "###EOF###";
    mkfifo(somePipeName.c_str(), 0666);
    static fstream ifs(somePipeName);
    string commandLine = "iw dev >> " + somePipeName;
    if (pwStatus == GOOD) {
        commandLine = "echo \'" + password + "\' | sudo -kS -p \"\" " + commandLine;
        //        cout << commandLine + "\n";
    }
    if (system(commandLine.c_str()) == 0) {
        commandLine = "echo \'" + eof + "\' >> " + somePipeName;
        waste(system(commandLine.c_str()));
        string interfaceLine;
        mainFormWidget.interfaceCbx->clear();
        boost::smatch sm;
        boost::regex rx("^[ \\t]+Interface +([^ ]+) *");
        while (getline(ifs, interfaceLine) && interfaceLine != eof) {
            //            cout << interfaceLine + "\n";
            if (boost::regex_match(interfaceLine, sm, rx))
                mainFormWidget.interfaceCbx->addItem(QString::fromStdString(sm[1]));
        }
    } else {
        QMessageBox::critical(0, "Bad Stuff", QString("Unable to continue.\nCannot find interface pipe"));
        ifs.close();
        remove(somePipeName.c_str());
        exit(1);
    }
    //
    // Now repeat the whole mess because linux wifi drivers can't decide where to announce themselves
    //
    commandLine = "cat /proc/net/wireless >> " + somePipeName;
    if (pwStatus == GOOD) {
        commandLine = "echo \'" + password + "\' | sudo -kS -p \"\" " + commandLine;
        //        cout << commandLine + "\n";
    }
    if (system(commandLine.c_str()) == 0) {
        commandLine = "echo \'" + eof + "\' >> " + somePipeName;
        waste(system(commandLine.c_str()));
        string interfaceLine;
        QString interface;
        boost::smatch sm2;
        boost::regex rx2("^ *([0-9A-Za-z_-]+) *:.+");
        while (getline(ifs, interfaceLine) && interfaceLine != eof) {
            //            cout << interfaceLine + "\n";
            if (boost::regex_match(interfaceLine, sm2, rx2)) {
                interface = QString::fromStdString(sm2[1]);
                bool found = false;
                for (int i = 0; i < mainFormWidget.interfaceCbx->count(); i++) {
                    if (interface == mainFormWidget.interfaceCbx->itemText(i)) {
                        found = true;
                        break;
                    }
                }
                if (!found) mainFormWidget.interfaceCbx->addItem(interface);
            }
        }
        if (mainFormWidget.interfaceCbx->count() <= 0) {
            QMessageBox::critical(0, "Bad Stuff",
                    QString("Unable to continue.\nNo wireless interfaces found"));
            exit(1);
        }
    } else {
        QMessageBox::critical(0, "Bad Stuff", QString("Unable to continue.\nCannot find interface pipe"));
        ifs.close();
        remove(somePipeName.c_str());
        exit(1);
    }
    ifs.close();
    remove(somePipeName.c_str());
}

void MainForm::setInterface(int ifIndx) {
    MainForm::mainFormWidget.interfaceCbx->setCurrentIndex(ifIndx);
}

string MainForm::getCurrentInterface() {
    return ((mainFormWidget.interfaceCbx->currentText()).toStdString());
}

// Define the custom event identifier
const QEvent::Type MainForm::DATA_READY_EVENT = static_cast<QEvent::Type> (DATAREADY);
// Define the custom event subclass

class MainForm::DataReadyEvent : public QEvent {
public:

    DataReadyEvent(const int customData1) :
    QEvent(MainForm::DATA_READY_EVENT), readyBlockNo(customData1) {
    }

    int getReadyBlockNo() const {
        return readyBlockNo;
    }
private:
    int readyBlockNo;
};

int MainForm::getNapTime() {
    return MainForm::mainFormWidget.napTimeSlider->value();
}

void MainForm::updatePlotPrefs(int plotMin, int plotMax, bool showGrid) {
    // a slot called from the prefs dialog to dynamically update the plots
    MainForm::mainFormWidget.timePlot->setAxisScale(QwtPlot::yLeft, plotMin, plotMax, 20);
    MainForm::mainFormWidget.chan24Plot->setAxisScale(QwtPlot::yLeft, plotMin, plotMax, 20);
    MainForm::mainFormWidget.chan5Plot->setAxisScale(QwtPlot::yLeft, plotMin, plotMax, 20);
    MainForm::timeGrid->enableY(showGrid);
    MainForm::chan24Grid->enableY(showGrid);
    MainForm::chan5Grid->enableY(showGrid);
    MainForm::mainFormWidget.timePlot->replot();
    MainForm::mainFormWidget.chan24Plot->replot();
    MainForm::mainFormWidget.chan5Plot->replot();
}

void MainForm::logPrefChanged(int state) {
    MainForm::logDataState = state;
}

void MainForm::writePrefsFile() {
    struct passwd *pw = getpwuid(getuid());
    const char *homeDir = pw->pw_dir;
    ofstream prefs;
    prefs.open(string(homeDir) + "/" + string(PREFS_FILE_NAME), ios::out);
    prefs << "version " << LINSSIDPREFSVER << endl;
    // col number must match the enum in "custom.h"
    prefs << "colwidth";
    for (int col = 0; col < MAX_TABLE_COLS; col++) {
        int colWidth = mainFormWidget.mainTableWidget->columnWidth(col);
        if (colWidth == 0) colWidth = columnWidth[col];
        prefs << " " << colWidth;
    }
    prefs << endl;
    prefs << "colvis";
    for (int col = 0; col < MAX_TABLE_COLS; col++)
        prefs << " " << !mainFormWidget.mainTableWidget->isColumnHidden(col);
    prefs << endl;
    prefs << "visorder";
    for (int visCol = 0; visCol < MAX_TABLE_COLS; visCol++)
        prefs << " " << mainFormWidget.mainTableWidget->horizontalHeader()->logicalIndex(visCol);
    prefs << endl;
    prefs << "sort "
            << MainForm::mainFormWidget.mainTableWidget->horizontalHeader()->sortIndicatorSection() << " "
            << MainForm::mainFormWidget.mainTableWidget->horizontalHeader()->sortIndicatorOrder() << endl;
    prefs << "maingeom " << this->x() << " "
            << this->y() << " "
            << this->width() << " "
            << this->height() << endl;
    prefs << "mainsplit " << MainForm::mainFormWidget.splitter->sizes().value(0) << " "
            << MainForm::mainFormWidget.splitter->sizes().value(1) << endl;
    prefs << "plottab " << MainForm::mainFormWidget.mainTabWgt->currentIndex() << endl;
    prefs << "naptime " << MainForm::mainFormWidget.napTimeSlider->value() << endl;
    prefs << "plotprefs "
            << int(MainForm::mainFormWidget.timePlot->axisScaleDiv(QwtPlot::yLeft).lowerBound()) << " "
            << int(MainForm::mainFormWidget.timePlot->axisScaleDiv(QwtPlot::yLeft).upperBound()) << " "
            << MainForm::timeGrid->yEnabled() << endl;
    prefs << "logdata " << MainForm::logDataState << endl;
    prefs.close();
}

void MainForm::writePrefsBlock(string absPrefsFileName, MainForm::sDefPref prefBlock) {
    // Writes a block of preferences of the structure sDefPref struct.
    // At entry, the file must either not exist or be closed.
    // At exit, the newly written file will be closed.
    fstream prefs;
    prefs.open(absPrefsFileName, ios::out);
    prefs << "version " << LINSSIDPREFSVER << endl;
    prefs << "colwidth";
    for (int i = 0; i < MAX_TABLE_COLS; i++)
        prefs << " " << prefBlock.colwidth[i];
    prefs << endl;
    prefs << "colvis";
    for (int i = 0; i < MAX_TABLE_COLS; i++)
        prefs << " " << prefBlock.colvis[i];
    prefs << endl;
    prefs << "visorder";
    for (int i = 0; i < MAX_TABLE_COLS; i++)
        prefs << " " << prefBlock.visorder[i];
    prefs << endl;
    prefs << "sort " << prefBlock.sort.column
            << " " << prefBlock.sort.order << endl;
    prefs << "maingeom " << prefBlock.maingeom.x
            << " " << prefBlock.maingeom.y
            << " " << prefBlock.maingeom.width
            << " " << prefBlock.maingeom.height << endl;
    prefs << "mainsplit " << prefBlock.mainsplit.topheight
            << " " << prefBlock.mainsplit.bottomheight << endl;
    prefs << "plottab " << prefBlock.plottab << endl;
    prefs << "naptime " << prefBlock.naptime << endl;
    prefs << "plotprefs " << prefBlock.plotprefs.plotlb
            << " " << prefBlock.plotprefs.plutub
            << " " << prefBlock.plotprefs.showgrid << endl;
    prefs << "logdata " << prefBlock.logData << endl;
    prefs.close();
}

void MainForm::readPrefsFile() {
    struct passwd *pw = getpwuid(getuid());
    const char *homeDir = pw->pw_dir;
    string absPrefsFileName = string(homeDir) + "/" + string(PREFS_FILE_NAME);
    fstream prefs;
    prefs.open(absPrefsFileName, ios::in);
    if (!prefs.is_open()) { // no prefs file, so create new with default values
        writePrefsBlock(absPrefsFileName, MainForm::defPref);
        prefs.open(absPrefsFileName, ios::in);
    }
    // make sure right version
    string line, tag, vers;
    istringstream lineParse;
    while (getline(prefs, line)) {
        lineParse.str(line);
        lineParse.clear();
        lineParse >> tag;
        if (tag == "version") {
            lineParse >> vers;
            break;
        }
    }
    if (vers != LINSSIDPREFSVER) { // old version so trash and replace with defaults
        prefs.close();
        writePrefsBlock(absPrefsFileName, MainForm::defPref);
        prefs.open(absPrefsFileName, ios::in);
    }
    // have a prefs file so parse
    prefs.seekg(0);
    prefs.clear();
    int colWidth, sortCol, sortDir;
    int x, y, winWidth, winHeight;
    int tab, splitHeight0, splitHeight1;
    int napTime;
    bool vis;
    sortCol = -1;
    int visOrder[MAX_TABLE_COLS]; // holds mapping from logical to visual as they change
    for (int lcol = 0; lcol < MAX_TABLE_COLS; lcol++) visOrder[lcol] = lcol;
    while (getline(prefs, line)) {
        lineParse.str(line);
        lineParse.clear();
        lineParse >> tag;
        if (tag == "colwidth") {
            for (int col = 0; col < MAX_TABLE_COLS; col++) {
                lineParse >> colWidth;
                if (colWidth > 0) {
                    MainForm::mainFormWidget.mainTableWidget->setColumnWidth(col, colWidth);
                    columnWidth[col] = colWidth;
                }
            }
        } else if (tag == "colvis") {
            for (int col = 0; col < MAX_TABLE_COLS; col++) {
                lineParse >> vis;
                MainForm::colToQAction[col]->setChecked(vis);
                MainForm::mainFormWidget.mainTableWidget->setColumnHidden(col, !vis);
            }
        } else if (tag == "sort") {
            lineParse >> sortCol >> sortDir;
            if (sortCol >= 0 && sortCol < MAX_TABLE_COLS) {
                MainForm::mainFormWidget.mainTableWidget->horizontalHeader()
                        ->setSortIndicator(sortCol, Qt::SortOrder(sortDir));
            }
        } else if (tag == "maingeom") {
            lineParse >> x >> y >> winWidth >> winHeight;
            this->setGeometry(x, y, winWidth, winHeight);
        } else if (tag == "visorder") {
            for (int i = 0; i < MAX_TABLE_COLS; i++)
                lineParse >> visOrder[i];
            for (int i = 0; i < MAX_TABLE_COLS - 1; i++) { // loop through visual order
                if (visOrder[i] != mainFormWidget.mainTableWidget->horizontalHeader()->logicalIndex(i)) {
                    // find the index of the visual column that has the desired logical column
                    for (int j = i + 1; j < MAX_TABLE_COLS; j++) { // and swap
                        if (visOrder[i] == mainFormWidget.mainTableWidget->horizontalHeader()->logicalIndex(j)) {
                            mainFormWidget.mainTableWidget->horizontalHeader()->swapSections(i, j);
                            break;
                        }
                    }
                }
            }
        } else if (tag == "plottab") {
            lineParse >> tab;
            MainForm::mainFormWidget.mainTabWgt->setCurrentIndex(tab);
        } else if (tag == "mainsplit") {
            lineParse >> splitHeight0 >> splitHeight1;
            QList<int> bullshit; // Nokia didn't have to rewrite the entire c++ syntax
            bullshit << splitHeight0 << splitHeight1;
            MainForm::mainFormWidget.splitter->setSizes(bullshit);
        } else if (tag == "naptime") {
            lineParse >> napTime;
            MainForm::mainFormWidget.napTimeSlider->setValue(napTime);
        } else if (tag == "plotprefs") {
            int plotLb, plotUb;
            bool showGrid;
            lineParse >> plotLb >> plotUb >> showGrid;
            // validate or the mess gets big
            if ((plotLb < -100) || (plotUb > 0) || (plotUb < (plotLb + 10))) { // prefs were hosed
                plotLb = -100;
                plotUb = -20; // so reset them to nominal values
            }
            MainForm::mainFormWidget.timePlot->setAxisScale(QwtPlot::yLeft, plotLb, plotUb, 20);
            MainForm::mainFormWidget.chan24Plot->setAxisScale(QwtPlot::yLeft, plotLb, plotUb, 20);
            MainForm::mainFormWidget.chan5Plot->setAxisScale(QwtPlot::yLeft, plotLb, plotUb, 20);
            MainForm::timeGrid->enableY(showGrid);
            MainForm::chan24Grid->enableY(showGrid);
            MainForm::chan5Grid->enableY(showGrid);
        } else if (tag == "logdata") {
            lineParse >> MainForm::logDataState;
        }
    }
    prefs.close();
}

void MainForm::postDataReadyEvent(const int customData1) {
    // This method (postDataReadyEvent) can be called from any thread
    QApplication::postEvent(this, new DataReadyEvent(customData1));
}

void MainForm::doRun() {
    if (MainForm::mainFormWidget.runBtn->isChecked()) {
        if (firstScan) {
            firstScan = false;
            MainForm::runStartTime = time(NULL);
        }
        MainForm::mainFormWidget.statusTxt->setText("Scanning ...");
        MainForm::pGetter->Getter::postDataWantedEvent(++lastBlockRequested);
        MainForm::drawTable();
        MainForm::drawChan24Plot();
        MainForm::drawChan5Plot();
        MainForm::drawTimePlot();
    } else {
        MainForm::mainFormWidget.statusTxt->setText("Waiting for wifi to terminate scan ...");    
    }
}

void MainForm::doPlotAll() {
    for (int tbi = 0; tbi <= maxTableIndex; tbi++) {
        MainForm::cellDataRay[tbi].pTableItem[PLOT]->setCheckState(Qt::Checked);
    }
    fillPlots();
}

void MainForm::doPlotNone() {
    for (int tbi = 0; tbi <= maxTableIndex; tbi++) {
        MainForm::cellDataRay[tbi].pTableItem[PLOT]->setCheckState(Qt::Unchecked);
    }
    fillPlots();
}

void MainForm::doTableChanged(int row, int column) {
    if (column == PLOT) {
        waste(row);
        fillPlots();
    }
}

void MainForm::reDrawTable() {

    MainForm::drawTable();
    MainForm::fillTable();
}

void MainForm::showAboutBox() {
    AboutBox aboutBox1;
//    aboutBox1.show();
    aboutBox1.exec();
//    aboutBox1.raise();
}

void MainForm::showPrefsDlg() {
    if (MainForm::prefsDlg1 != 0) return; // already a prefs dialog open somewhere...
    MainForm::prefsDlg1 = new prefsDialog(
            int(MainForm::mainFormWidget.timePlot->axisScaleDiv(QwtPlot::yLeft).lowerBound()),
            int(MainForm::mainFormWidget.timePlot->axisScaleDiv(QwtPlot::yLeft).upperBound()),
            MainForm::timeGrid->yEnabled(),
            MainForm::logDataState,
            (QObject*)this);
//    MainForm::prefsDlg1->show();
    MainForm::prefsDlg1->exec();
//    MainForm::prefsDlg1->raise();
    delete MainForm::prefsDlg1; // release the heap
    MainForm::prefsDlg1 = 0; // null pointer
}

void MainForm::columnWidthSave(int col, int oldWidth, int newWidth) {
    if (newWidth > 0) MainForm::columnWidth[col] = newWidth;
    else if (oldWidth > 0) MainForm::columnWidth[col] = oldWidth;
}

void MainForm::customEvent(QEvent * event) {
    // When we get here, we've crossed the thread boundary and are now
    // executing in the Qt object's thread
    if (event->type() == MainForm::DATA_READY_EVENT) {
        handleDataReadyEvent(static_cast<DataReadyEvent *> (event));
    }
    // use more else ifs to handle other custom events
}

void MainForm::closeEvent(QCloseEvent * event) {
//    cout << "closeEvent intercepted..." << endl;
    closing = true; // don't let Getter take a nap
    MainForm::mainFormWidget.statusTxt->setText("Exiting, waiting for wifi driver ...");
    MainForm::mainFormWidget.statusTxt->repaint();
    pGetterThread->QThread::quit();
    writePrefsFile();
    pGetterThread->QThread::wait();
    MainForm::mainFormWidget.statusTxt->setText("Closing ...");
    MainForm::mainFormWidget.statusTxt->repaint();
    remove(pipeName.c_str());
    linssidLog.close();
    if (MainForm::logDataStream.is_open()) MainForm::logDataStream.close();
    //    QMainWindow::closeEvent(event);
    event->accept();
    std::exit(0); // that's the system exit, not the Qt version
}

void MainForm::drawTable() {
    //    QMessageBox::information(0, "checkpoint", "entered drawTable");

    MainForm::mainFormWidget.mainTableWidget->setColumnCount(MAX_TABLE_COLS);
    MainForm::mainFormWidget.mainTableWidget->setRowCount(MainForm::maxTableIndex + 1);
    // Make sure the column labels below are same order as the enum <colTitle>
    /*
    enum colTitle {
    PLOT, SSID, MAC, CHANNEL, MODE, SECURITY, PRIVACY,
    CIPHER, FREQUENCY, QUALITY, SIGNAL, BW, MINSIGNAL, MAXSIGNAL, CENCHAN,
    FIRST_SEEN, LAST_SEEN, VENDOR, PROTOCOL // TYPE not yet impl
}; */
    MainForm::mainFormWidget.mainTableWidget->setHorizontalHeaderLabels(
            QString("Plot|SSID|MAC|Channel|Mode|Security|Privacy|Cipher|Frequency\
|Quality|Signal|BW MHz|Min Sig|Max Sig|Cen Chan|First Seen|Last Seen|Vendor|Protocol|Type").split("|"));
    setVisibleCols();
    MainForm::mainFormWidget.mainTableWidget->horizontalHeader()->setSectionsMovable(true);
    MainForm::mainFormWidget.mainTableWidget->horizontalHeader()
            ->setToolTip("Click to sort\nDrag and Drop to re-order\nClick and drag divider to fit");
    MainForm::mainFormWidget.mainTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainForm::setVisibleCols() {
    // the Plot column is always visible
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(SSID,
            !(MainForm::mainFormWidget.actionSSID->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(MAC,
            !(MainForm::mainFormWidget.actionMAC->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(CHANNEL,
            !(MainForm::mainFormWidget.actionChannel->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(MODE,
            !(MainForm::mainFormWidget.actionMode->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(PROTOCOL,
            !(MainForm::mainFormWidget.actionProtocol->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(SECURITY,
            !(MainForm::mainFormWidget.actionSecurity->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(PRIVACY,
            !(MainForm::mainFormWidget.actionPrivacy->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(CIPHER,
            !(MainForm::mainFormWidget.actionCipher->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(FREQUENCY,
            !(MainForm::mainFormWidget.actionFrequency->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(QUALITY,
            !(MainForm::mainFormWidget.actionQuality->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(SIGNAL,
            !(MainForm::mainFormWidget.actionSignal->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(BW,
            !(MainForm::mainFormWidget.actionBW->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(MINSIGNAL,
            !(MainForm::mainFormWidget.actionMin_Signal->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(MAXSIGNAL,
            !(MainForm::mainFormWidget.actionMax_Signal->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(CENCHAN,
            !(MainForm::mainFormWidget.actionCenChan->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(FIRST_SEEN,
            !(MainForm::mainFormWidget.actionFirst_Seen->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(LAST_SEEN,
            !(MainForm::mainFormWidget.actionLast_Seen->isChecked()));
    MainForm::mainFormWidget.mainTableWidget->setColumnHidden(VENDOR,
            !(MainForm::mainFormWidget.actionVendor->isChecked()));
}

void MainForm::fillTable() {
    // fill in the x-y, also set each cell text alignment
    MainForm::mainFormWidget.mainTableWidget->setRowCount(maxTableIndex + 1);
    for (int row = 0; row <= maxTableIndex; row++) {
        MainForm::cellDataRay[row].pTableItem[PLOT]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[SSID]->
                setText(MainForm::cellDataRay[row].essid.c_str());
        MainForm::cellDataRay[row].pTableItem[MAC]->
                setText(MainForm::cellDataRay[row].macAddr.c_str());
        MainForm::cellDataRay[row].pTableItem[MAC]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[CHANNEL]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].channel);
        MainForm::cellDataRay[row].pTableItem[CHANNEL]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[MODE]->
                setText(MainForm::cellDataRay[row].mode.c_str());
        MainForm::cellDataRay[row].pTableItem[MODE]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[PROTOCOL]->
                setText(MainForm::cellDataRay[row].protocol.c_str());
        MainForm::cellDataRay[row].pTableItem[PROTOCOL]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[SECURITY]->
                setText(MainForm::cellDataRay[row].security.c_str());
        MainForm::cellDataRay[row].pTableItem[SECURITY]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[PRIVACY]->
                setText((MainForm::cellDataRay[row].privacy).c_str());
        MainForm::cellDataRay[row].pTableItem[PRIVACY]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[CIPHER]->
                setText((MainForm::cellDataRay[row].cipher).c_str());
        MainForm::cellDataRay[row].pTableItem[CIPHER]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[FREQUENCY]->
                setText(MainForm::cellDataRay[row].frequency.c_str());
        MainForm::cellDataRay[row].pTableItem[FREQUENCY]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[QUALITY]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].quality);
        MainForm::cellDataRay[row].pTableItem[QUALITY]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[SIGNAL]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].signal);
        MainForm::cellDataRay[row].pTableItem[SIGNAL]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[BW]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].BW);
        MainForm::cellDataRay[row].pTableItem[BW]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[MINSIGNAL]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].minSignal);
        MainForm::cellDataRay[row].pTableItem[MINSIGNAL]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[MAXSIGNAL]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].maxSignal);
        MainForm::cellDataRay[row].pTableItem[MAXSIGNAL]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[CENCHAN]->
                setData(Qt::DisplayRole, MainForm::cellDataRay[row].cenChan);
        MainForm::cellDataRay[row].pTableItem[CENCHAN]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[FIRST_SEEN]->
                setText(QDateTime::fromTime_t(MainForm::cellDataRay[row].firstSeen).toString("MM/dd-hh:mm:ss"));
        MainForm::cellDataRay[row].pTableItem[FIRST_SEEN]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[LAST_SEEN]->
                setText(QDateTime::fromTime_t(MainForm::cellDataRay[row].lastSeen).toString("MM/dd-hh:mm:ss"));
        MainForm::cellDataRay[row].pTableItem[LAST_SEEN]->setTextAlignment(Qt::AlignCenter);
        MainForm::cellDataRay[row].pTableItem[VENDOR]->
                setText(MainForm::cellDataRay[row].vendor.c_str());
    }
    setVisibleCols();
    MainForm::mainFormWidget.mainTableWidget->setSortingEnabled(true);
}

class MainForm::Chan24ScaleDraw : public QwtScaleDraw {
public:

    Chan24ScaleDraw() {
    }

    virtual QwtText label(double v) const {
        if (v >= 1 && v <= 14) return (QString::number(int(v)));

        else return (QString(""));
    }
};

class MainForm::Chan5ScaleDraw : public QwtScaleDraw {
public:

    Chan5ScaleDraw() {
    }

    virtual QwtText label(double v) const {
        if ((v >= 1.0) && (v <= 160.0) && (int(v) % 10 == 0)) return (QString::number(int(v)));

        else return (QString(""));
    }
};

void MainForm::drawChan24Plot() {

    MainForm::mainFormWidget.chan24Plot->setAxisScale(QwtPlot::xBottom, -1, 16, 1);
    MainForm::mainFormWidget.chan24Plot->setAxisMaxMinor(QwtPlot::xBottom, 0);
    MainForm::mainFormWidget.chan24Plot->setAxisScaleDraw(QwtPlot::xBottom, new Chan24ScaleDraw());
    //    MainForm::mainFormWidget.chan24Plot->setAxisScale(QwtPlot::yLeft, -100, -20, 20);
    MainForm::mainFormWidget.chan24Plot->replot();
}

void MainForm::drawChan5Plot() {

    MainForm::mainFormWidget.chan5Plot->setAxisScale(QwtPlot::xBottom, 0, 170, 10);
    MainForm::mainFormWidget.chan5Plot->setAxisMaxMinor(QwtPlot::xBottom, 5);
    MainForm::mainFormWidget.chan5Plot->setAxisScaleDraw(QwtPlot::xBottom, new Chan5ScaleDraw());
    //    MainForm::mainFormWidget.chan5Plot->setAxisScale(QwtPlot::yLeft, -100, -20, 20);
    MainForm::mainFormWidget.chan5Plot->replot();
}

void MainForm::drawTimePlot() {

    MainForm::mainFormWidget.timePlot->setAxisScale(QwtPlot::xBottom,
            MainForm::blockSampleTime - TIME_PLOT_SCALE,
            MainForm::blockSampleTime, 10);
    MainForm::mainFormWidget.timePlot->setAxisMaxMinor(QwtPlot::xBottom, 5);
    //    MainForm::mainFormWidget.timePlot->setAxisScale(QwtPlot::yLeft, -100, -20, 20);
    MainForm::mainFormWidget.timePlot->replot();
}

void MainForm::fillPlots() {
    // rescale the time plot
    MainForm::mainFormWidget.timePlot->setAxisScale(QwtPlot::xBottom,
            MainForm::blockSampleTime - TIME_PLOT_SCALE,
            MainForm::blockSampleTime, 10);
    for (int tbi = 0; tbi <= maxTableIndex; tbi++) {
        // first the 2.5GHz and 5GHz channel vs signal plots
        float spread = MainForm::cellDataRay[tbi].BW / 10.0;
        MainForm::cellDataRay[tbi].xPlot[0] = MainForm::cellDataRay[tbi].cenChan - spread;
        MainForm::cellDataRay[tbi].xPlot[1] = MainForm::cellDataRay[tbi].cenChan - spread + 1.0;
        MainForm::cellDataRay[tbi].xPlot[2] = MainForm::cellDataRay[tbi].cenChan + spread - 1.0;
        MainForm::cellDataRay[tbi].xPlot[3] = MainForm::cellDataRay[tbi].cenChan + spread;
        MainForm::cellDataRay[tbi].yPlot[0] = MainForm::cellDataRay[tbi].yPlot[3] = -100.0;
        MainForm::cellDataRay[tbi].yPlot[1] = MainForm::cellDataRay[tbi].yPlot[2]
                = MainForm::cellDataRay[tbi].signal;
        if (MainForm::cellDataRay[tbi].pTableItem[PLOT]->checkState() == Qt::Checked) {
            MainForm::cellDataRay[tbi].pBandCurve->setRawSamples(MainForm::cellDataRay[tbi].xPlot,
                    MainForm::cellDataRay[tbi].yPlot, 4);
        } else {
            MainForm::cellDataRay[tbi].pBandCurve->setSamples(0, 0, 0);
        }
        // now the signal history plot
        int ixStart;
        int ixLength;
        int numSamples = MainForm::cellDataRay[tbi].pHistory->totalSamples;
        if (numSamples < MAX_SAMPLES) {
            ixLength = numSamples;
            ixStart = 0;
        } else {
            ixLength = MAX_SAMPLES;
            ixStart = numSamples % MAX_SAMPLES;
        }
        if (MainForm::cellDataRay[tbi].pTableItem[PLOT]->checkState() == Qt::Checked) {
            MainForm::cellDataRay[tbi].pTimeCurve->setRawSamples(
                    &(MainForm::cellDataRay[tbi].pHistory->sampleSec[ixStart]),
                    &(MainForm::cellDataRay[tbi].pHistory->signal[ixStart]), ixLength);
        } else {

            MainForm::cellDataRay[tbi].pTimeCurve->setSamples(0, 0, 0);
        }
    }
    MainForm::mainFormWidget.chan24Plot->replot();
    MainForm::mainFormWidget.chan5Plot->replot();
    MainForm::mainFormWidget.timePlot->replot();
}

void MainForm::initNewCell(string macAddress, int tbi) {
    // Initialize a newly found cell.
    MainForm::cellData* emptyStruct;               // C++ is really stupid
    emptyStruct = new MainForm::cellData();        // unintuitive as heck
    MainForm::cellDataRay.push_back(*emptyStruct); // This is the only way to
    delete emptyStruct;                            // create a new initialized element
    MainForm::cellDataRay[tbi].macAddr = macAddress; // insert MAC address
    MainForm::cellDataRay[tbi].essid = "<hidden>"; // nl80211 iw doesn't report SSID line if hidden
    MainForm::cellDataRay[tbi].minSignal = 0;
    MainForm::cellDataRay[tbi].maxSignal = -120;
    MainForm::cellDataRay[tbi].firstSeen = now;
    MainForm::cellDataRay[tbi].protocol = "unknown";
    MainForm::cellDataRay[tbi].vendor = MainForm::findVendor(macAddress);
    MainForm::cellDataRay[tbi].pHistory = new History(); // give it a history
    MainForm::cellDataRay[tbi].pTimeCurve = new QwtPlotCurve(""); // and a history curve
    QColor tempColor = qColorArray[tbi % NUMBER_OF_COLORS];
    MainForm::cellDataRay[tbi].color = tempColor; // assign a color from the palette
    MainForm::cellDataRay[tbi].pTimeCurve->setPen(* new QPen(tempColor, 3.0));
    MainForm::cellDataRay[tbi].pTimeCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    MainForm::cellDataRay[tbi].pTimeCurve->attach(MainForm::mainFormWidget.timePlot);
    MainForm::cellDataRay[tbi].pBandCurve = new QwtPlotCurve("");
    MainForm::cellDataRay[tbi].pBandCurve->setPen(* new QPen(MainForm::cellDataRay[tbi].color, 3.0));
    MainForm::cellDataRay[tbi].pBandCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    // attaching plot curve waits 'till know frequency
    MainForm::mainFormWidget.mainTableWidget->setRowCount(tbi + 1);
    for (int ix = 0; ix < MAX_TABLE_COLS; ix++) {
        MainForm::cellDataRay[tbi].pTableItem[ix] = new QTableWidgetItem(); // Give it a table item for each column
        MainForm::mainFormWidget.mainTableWidget->setItem(tbi, ix,
                MainForm::cellDataRay[tbi].pTableItem[ix]); // Give it a spot in the table
    }
    MainForm::cellDataRay[tbi].pTableItem[PLOT]->setFlags(
            Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    MainForm::cellDataRay[tbi].pTableItem[PLOT]->setCheckState(Qt::Checked);
    MainForm::cellDataRay[tbi].pTableItem[SSID]->setTextColor(MainForm::cellDataRay[tbi].color);
}

void MainForm::extractData(string tl, int &tbi) {
    // extract the information from each line recovered from the pipe from getter
    static int newBSS;
    boost::smatch sm;
    if (boost::regex_match(tl, sm, boost::regex("^BSS.*?(([A-Fa-f0-9]{2}:){5}[A-Fa-f0-9]{2}).*",
          boost::regex_constants::icase))) {
        pageBlock = BT_BSS;
        string macAddress = sm[1];
        //string macAddress = boost::regex_replace(tl,
        //        boost::regex(".+?((?:[A-Fa-f0-9]{2}:){5}[A-Fa-f0-9]{2}).*"), "$1");
        for (unsigned int ic=0; ic< macAddress.length(); ic++) macAddress[ic] = toupper(macAddress[ic]);
        tbi = MainForm::maxTableIndex + 1;
        for (int i = 0; i <= MainForm::maxTableIndex; i++) {
            if (macAddress == MainForm::cellDataRay[i].macAddr) {
                tbi = i;
                newBSS = 0; // Have seen this BSS before
                break;
            }
        }
        if (MainForm::maxTableIndex < tbi) {
            // at this point we have found a **new** mac address. Initialize accordingly.
            MainForm::initNewCell(macAddress, tbi);
            MainForm::maxTableIndex = tbi;
            newBSS = 1; // Flag first time through for new BSS
        }
        MainForm::cellDataRay[tbi].timesSeen++;
        MainForm::cellDataRay[tbi].lastSeen = now;
        MainForm::cellDataRay[tbi].BW = 20; // all have at least 20 MHz bandwidth
        MainForm::cellDataRay[tbi].protocol = "";
    } 
       else if (boost::regex_match(tl, sm, boost::regex("^.+?SSID: +(.*)"))) {
        string tempSSID = sm[1];
        MainForm::cellDataRay[tbi].essid = tempSSID;
    }  else if (boost::regex_match(tl, sm, boost::regex(
            "^[ \\t]+Supported rates: (.*)", boost::regex_constants::icase))) { // protocol
        string tempStr = sm[1];
        if (MainForm::MinIntStr(tempStr) < 11) MainForm::cellDataRay[tbi].protocol += "b";
        if (MainForm::MaxIntStr(tempStr) >= 11) MainForm::cellDataRay[tbi].protocol += "g";
    }  else if (boost::regex_match(tl, sm, boost::regex(
            "^[ \\t]+HT Capabilities:", boost::regex_constants::icase))) { // protocol
        pageBlock = BT_HT_CAPABILITIES;
        MainForm::cellDataRay[tbi].protocol += "n";
    }  else if (boost::regex_match(tl, sm, boost::regex(
            "^.*?VHT Capabilities:", boost::regex_constants::icase))) { // protocol
        pageBlock = BT_VHT_CAPABILITIES;
        MainForm::cellDataRay[tbi].protocol += "ac";
    } else if (boost::regex_match(tl, sm, boost::regex(".*?capability:.*?( ESS( .*|$))",
            boost::regex_constants::icase))) {
        MainForm::cellDataRay[tbi].mode = "AP"; // http://unix.stackexchange.com/questions/63069/the-n-mode-on-iwlist-wlan0-scan
    } else if (boost::regex_match(tl, sm, boost::regex(".*?capability:.*?( IBSS( .*|$))",
            boost::regex_constants::icase))) {
        MainForm::cellDataRay[tbi].mode = "Ad Hoc";
    } else if (boost::regex_match(tl, sm,
          boost::regex("^.*?primary channel: +([0-9]+).*", boost::regex_constants::icase))) {
        string tempChan = sm[1];
        MainForm::cellDataRay[tbi].channel = atoi(tempChan.c_str());
        MainForm::cellDataRay[tbi].cenChan = MainForm::cellDataRay[tbi].channel;
    } else if (boost::regex_match(tl, sm,
          boost::regex("^.*?DS Parameter set: +(channel)?.*?([0-9]+).*", boost::regex_constants::icase))
          && MainForm::cellDataRay[tbi].channel == 0) {
        string tempChan = sm[2];
        MainForm::cellDataRay[tbi].channel = atoi(tempChan.c_str());
        MainForm::cellDataRay[tbi].cenChan = MainForm::cellDataRay[tbi].channel;
    } else if (boost::regex_match(tl, sm, boost::regex("^.*?secondary channel offset: *([^ \\t]+).*",
          boost::regex_constants::icase))) { // secondary channel offset
        string tempString = sm[1];
        if (tempString == "above") MainForm::cellDataRay[tbi].cenChan = MainForm::cellDataRay[tbi].channel + 2;
        else if (tempString == "below") MainForm::cellDataRay[tbi].cenChan = MainForm::cellDataRay[tbi].channel - 2;
    } else if (boost::regex_match(tl, sm, 
            boost::regex("^.*?freq:.*?([0-9]+).*",
            boost::regex_constants::icase))) {
        string tempFreq = sm[1];
        MainForm::cellDataRay[tbi].frequency = tempFreq;
        if (newBSS) {
            if (tempFreq.substr(0, 1) == "2") {
                MainForm::cellDataRay[tbi].pBandCurve->attach(MainForm::mainFormWidget.chan24Plot);
            } else {
                MainForm::cellDataRay[tbi].pBandCurve->attach(MainForm::mainFormWidget.chan5Plot);
            }
        }
    } else if (boost::regex_match(tl, sm, boost::regex("^.*?signal:.*?([\\-0-9]+).*?dBm.*",
            boost::regex_constants::icase))) {
            string tempSig = sm[1];
            MainForm::cellDataRay[tbi].signal = atoi(tempSig.c_str());
            if (MainForm::cellDataRay[tbi].signal < MainForm::cellDataRay[tbi].minSignal)
                MainForm::cellDataRay[tbi].minSignal = MainForm::cellDataRay[tbi].signal;
            if (MainForm::cellDataRay[tbi].signal > MainForm::cellDataRay[tbi].maxSignal)
                MainForm::cellDataRay[tbi].maxSignal = MainForm::cellDataRay[tbi].signal;
            // add to history
            if (MainForm::cellDataRay[tbi].timesSeen == 1) {
                int ixTemp = MainForm::cellDataRay[tbi].pHistory->totalSamples % MAX_SAMPLES;
                MainForm::cellDataRay[tbi].pHistory->sampleSec[ixTemp] = MainForm::blockSampleTime;
                MainForm::cellDataRay[tbi].pHistory->sampleSec[ixTemp + MAX_SAMPLES]
                    = MainForm::blockSampleTime;
                MainForm::cellDataRay[tbi].pHistory->signal[ixTemp] = MainForm::cellDataRay[tbi].signal;
                MainForm::cellDataRay[tbi].pHistory->signal[ixTemp + MAX_SAMPLES] = MainForm::cellDataRay[tbi].signal;
                MainForm::cellDataRay[tbi].pHistory->totalSamples++;
            } else {
                int ixTemp = (MainForm::cellDataRay[tbi].pHistory->totalSamples - 1) % MAX_SAMPLES;
                MainForm::cellDataRay[tbi].pHistory->sampleSec[ixTemp] = MainForm::blockSampleTime;
                MainForm::cellDataRay[tbi].pHistory->sampleSec[ixTemp + MAX_SAMPLES]
                    = MainForm::blockSampleTime;
                MainForm::cellDataRay[tbi].pHistory->signal[ixTemp] = MainForm::cellDataRay[tbi].signal;
                MainForm::cellDataRay[tbi].pHistory->signal[ixTemp + MAX_SAMPLES] = MainForm::cellDataRay[tbi].signal;
            }
            if (MainForm::cellDataRay[tbi].signal <= -100) MainForm::cellDataRay[tbi].quality = 0;
            else if(MainForm::cellDataRay[tbi].signal >= -50) MainForm::cellDataRay[tbi].quality = 100;
            else MainForm::cellDataRay[tbi].quality = 2 * (MainForm::cellDataRay[tbi].signal + 100);
    } else if (boost::regex_match(tl, sm, boost::regex(".*?Group cipher: *(.*)",
            boost::regex_constants::icase))) { // group cipher
        MainForm::cellDataRay[tbi].privacy = sm[1];
    } else if (pageBlock == BT_HT_CAPABILITIES && boost::regex_match(tl, sm, boost::regex(".*?HT20/HT40.*",
            boost::regex_constants::icase))) { // Bandwidth HT 40 MHz
        MainForm::cellDataRay[tbi].BW = 40;
    } else if (pageBlock == BT_VHT_OPERATION && boost::regex_match(tl, sm, boost::regex(".*?\\* channel width:.*?([0-9]+) MHz.*",
            boost::regex_constants::icase))) { // Bandwidth VHT
        string tempString = sm[1];
        MainForm::cellDataRay[tbi].BW = atoi(tempString.c_str());
    } else if (boost::regex_match(tl, sm, boost::regex(".*?Pairwise ciphers: *(.*)",
            boost::regex_constants::icase))) { // pairwise ciphers
        MainForm::cellDataRay[tbi].cipher = sm[1];
    } else if (boost::regex_match(tl, sm, boost::regex(".*?Authentication suites: *(.*)",
            boost::regex_constants::icase))) { // authentication
            MainForm::cellDataRay[tbi].security = sm[1];
    } else if (boost::regex_match(tl, sm, boost::regex(".*?RSN: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_RSN;
    } else if (boost::regex_match(tl, sm, boost::regex(".*?BSS Load: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_BSS_LOAD;
    } else if (boost::regex_match(tl, sm, boost::regex("[^V]*HT operation: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_HT_OPERATION;
    } else if (boost::regex_match(tl, sm, boost::regex(".*?Extended capabilities: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_EXTENDED_CAPABILITIES;
    } else if (boost::regex_match(tl, sm, boost::regex(".*?VHT operation:.*",
            boost::regex_constants::icase))) { pageBlock = BT_VHT_OPERATION;
    } else if (boost::regex_match(tl, sm, boost::regex(".*?WPA: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_WPA;
    } else if (boost::regex_match(tl, sm, boost::regex(".*?WPS: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_WPS;
    } else if (boost::regex_match(tl, sm, boost::regex(".*?WMM: *(.*)",
            boost::regex_constants::icase))) { pageBlock = BT_WMM;
    }
} // extractData()

void MainForm::doLogData() {
    if (!MainForm::logDataStream.is_open()) { // if data log file is not open...
        struct passwd *pw = getpwuid(getuid());
        const char *homeDir = pw->pw_dir;
        string logDataFileName = string(homeDir) + "/" + string(LOG_DATA_FILE_NAME);
        MainForm::logDataStream.open(logDataFileName, ios::in); // open for read to see if file already exists
        if (MainForm::logDataStream) { // if it exists.,..
            string arg1 = ""; string arg2 = "";
            logDataStream >> arg1 >> arg2;
            if (arg1 != "LINSSIDDATALOGVER" || arg2 != LINSSIDDATALOGVER) { // old log file version
                MainForm::logDataStream.close(); // close it for read
                rename(logDataFileName.c_str(), (logDataFileName + ".old").c_str());
                writeLogDataHeader(logDataFileName); // open a new file for write append, insert header
            } else {  // is new log format so open for write append
                MainForm::logDataStream.close(); // close it for read
                MainForm::logDataStream.open(logDataFileName, ios::out | ios::app);
            }
        } else { // if not exists... open for append and write headers
            writeLogDataHeader(logDataFileName);
        }
    }
    // now write data
    char nowStr[64], firstStr[64], lastStr[64];
    std::strftime(nowStr, 100, "%Y/%m/%d.%H:%M:%S", std::localtime(&MainForm::now));
    for (int tbi = 0; tbi <= MainForm::maxTableIndex; tbi++) {
        std::strftime(firstStr, 100, "%Y/%m/%d.%H:%M:%S", std::localtime(&MainForm::cellDataRay[tbi].firstSeen));
        std::strftime(lastStr, 100, "%Y/%m/%d.%H:%M:%S", std::localtime(&MainForm::cellDataRay[tbi].lastSeen));
        MainForm::logDataStream << nowStr << "\t"
                << "\"" << MainForm::cellDataRay[tbi].essid << "\"\t"
                << MainForm::cellDataRay[tbi].macAddr << "\t"
                << MainForm::cellDataRay[tbi].channel << "\t"
                << MainForm::cellDataRay[tbi].mode << "\t"
                << MainForm::cellDataRay[tbi].protocol << "\t"
                << MainForm::cellDataRay[tbi].security << "\t"
                << MainForm::cellDataRay[tbi].privacy << "\t"
                << MainForm::cellDataRay[tbi].cipher << "\t"
                << MainForm::cellDataRay[tbi].frequency << "\t"
                << MainForm::cellDataRay[tbi].quality << "\t"
                << MainForm::cellDataRay[tbi].signal << "\t"
                << MainForm::cellDataRay[tbi].BW << "\t"
                << MainForm::cellDataRay[tbi].minSignal << "\t"
                << MainForm::cellDataRay[tbi].maxSignal << "\t"
                << MainForm::cellDataRay[tbi].cenChan << "\t"
                << firstStr << "\t"
                << lastStr << "\t"
                << "\"" << MainForm::cellDataRay[tbi].vendor << "\"\n";
    }
}

void MainForm::writeLogDataHeader(string logDataFileName) {
    MainForm::logDataStream.close(); // close it for read if was open (don't really need to...)
    MainForm::logDataStream.open(logDataFileName, ios::out | ios::app); // open for write append
    MainForm::logDataStream << "LINSSIDDATALOGVER " << LINSSIDDATALOGVER << "\n";
    MainForm::logDataStream << "Time\tSSID\tMAC\tChannel\tMode\tProtocol\tSecurity\tPrivacy\t\
Cipher\tFrequency\tQuality\tSignal\tBW\tMin_Sig\tMax_Sig\tCen_Chan\tFirst_Seen\tLast_Seen\tVendor\n";
}

void MainForm::handleDataReadyEvent(const DataReadyEvent * /*event*/) {
    // Now something can be safely done with the Qt objects.
    // Access the custom data using event->getReadyBlockNo() etc.
    QCoreApplication::processEvents(QEventLoop::AllEvents); // TODO is this necessary?

    static fstream thePipe(pipeName);
    // reset some stuff from last pass
    for (int ix = 0; ix <= maxTableIndex; ix++) {
        MainForm::cellDataRay[ix].protocol = "";
        MainForm::cellDataRay[ix].signal = -110;
        MainForm::cellDataRay[ix].timesSeen = 0;
        // MainForm::cellDataRay[ix].BW = 20; // no bandwidth less than 20 MHz
    }
    // disable column sorting to prevent segfaults while we muck with the table
    MainForm::mainFormWidget.mainTableWidget->setSortingEnabled(false);
    string tempLine;
    bool lastLine = false;
    MainForm::now = time(NULL);
    MainForm::blockSampleTime = now - MainForm::runStartTime;
    int tableIndex = -1; // holds current index pointer into cellData
    while (!lastLine && getline(thePipe, tempLine)) {
        // cout << "tempLine:" << tempLine << endl; //debug
        MainForm::extractData(tempLine, tableIndex); // the heavy lifting here
        lastLine = tempLine.substr(0, endBlockString.length()) == endBlockString;
        if (lastLine) {
            int block = atoi(tempLine.substr(endBlockString.length() + 1, std::string::npos).c_str());
            if (block >= 0) lastBlockReceived = block;
            if (MainForm::mainFormWidget.runBtn->isChecked()) {
                if (block >= 0) lastBlockRequested++;
                MainForm::pGetter->postDataWantedEvent(lastBlockRequested);
            } else {
                MainForm::mainFormWidget.statusTxt->setText("Paused");
            }
            if (block >= 0) {
                MainForm::fillTable();
                MainForm::fillPlots();
                if (MainForm::logDataState == Qt::Checked) {
                    doLogData();
                }
            }
        }
    }
}

inline void MainForm::waste(int) {
    // This silliness is to ignore an argument function's return code without
    // having the compiler whine about it.
}

int MainForm::MaxIntStr(const string &s) {
    stringstream ss(s);
    string item;
    int retInt = INT_MIN;
    int tempInt;
    while (getline(ss, item, ' ')) {
        if (item.back() == '*') item=item.substr(0,item.length()-1);
        tempInt = atoi(item.c_str());
        if (tempInt > retInt) retInt = tempInt;
    }
    return retInt;
}

int MainForm::MinIntStr(const string &s) {
    stringstream ss(s);
    string item;
    int retInt = INT_MAX;
    int tempInt;
    while (getline(ss, item, ' ')) {
        if (item.back() == '*') item=item.substr(0,item.length()-1);
        tempInt = atoi(item.c_str());
        if (tempInt < retInt) retInt = tempInt;
    }
    return retInt;
}

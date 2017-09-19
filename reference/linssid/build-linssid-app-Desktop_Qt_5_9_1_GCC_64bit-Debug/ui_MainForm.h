/********************************************************************************
** Form generated from reading UI file 'MainForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_mainForm
{
public:
    QAction *actionExport_to_NS1;
    QAction *actionExit;
    QAction *actionSSID;
    QAction *actionChannel;
    QAction *actionMAC;
    QAction *actionMode;
    QAction *actionSecurity;
    QAction *actionPrivacy;
    QAction *actionCipher;
    QAction *actionFrequency;
    QAction *actionQuality;
    QAction *actionSignal;
    QAction *actionBW;
    QAction *actionVendor;
    QAction *actionFirst;
    QAction *actionLast;
    QAction *actionType;
    QAction *actionAbout;
    QAction *actionCenChan;
    QAction *actionMin_Signal;
    QAction *actionMax_Signal;
    QAction *actionFirst_Seen;
    QAction *actionLast_Seen;
    QAction *actionPlot;
    QAction *actionPrefs;
    QAction *actionProtocol;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *buttonFrame;
    QFormLayout *formLayout;
    QGridLayout *gridLayout;
    QComboBox *interfaceCbx;
    QLabel *interfaceLbl;
    QLabel *runLbl;
    QPushButton *runBtn;
    QSlider *napTimeSlider;
    QLabel *napTimeLbl;
    QLabel *statusTxt;
    QLabel *statusLbl;
    QLabel *graphLbl;
    QHBoxLayout *horizontalLayout;
    QPushButton *allBtn;
    QPushButton *noneBtn;
    QSplitter *splitter;
    QTableWidget *mainTableWidget;
    QTabWidget *mainTabWgt;
    QWidget *timePlotTab;
    QVBoxLayout *verticalLayout_4;
    QwtPlot *timePlot;
    QWidget *chan24Tab;
    QVBoxLayout *verticalLayout_2;
    QwtPlot *chan24Plot;
    QWidget *chan5Tab;
    QVBoxLayout *verticalLayout_3;
    QwtPlot *chan5Plot;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainForm)
    {
        if (mainForm->objectName().isEmpty())
            mainForm->setObjectName(QStringLiteral("mainForm"));
        mainForm->resize(759, 561);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainForm->sizePolicy().hasHeightForWidth());
        mainForm->setSizePolicy(sizePolicy);
        actionExport_to_NS1 = new QAction(mainForm);
        actionExport_to_NS1->setObjectName(QStringLiteral("actionExport_to_NS1"));
        actionExport_to_NS1->setVisible(false);
        actionExit = new QAction(mainForm);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSSID = new QAction(mainForm);
        actionSSID->setObjectName(QStringLiteral("actionSSID"));
        actionSSID->setCheckable(true);
        actionSSID->setChecked(true);
        actionSSID->setEnabled(true);
        actionChannel = new QAction(mainForm);
        actionChannel->setObjectName(QStringLiteral("actionChannel"));
        actionChannel->setCheckable(true);
        actionChannel->setChecked(true);
        actionMAC = new QAction(mainForm);
        actionMAC->setObjectName(QStringLiteral("actionMAC"));
        actionMAC->setCheckable(true);
        actionMAC->setChecked(true);
        actionMode = new QAction(mainForm);
        actionMode->setObjectName(QStringLiteral("actionMode"));
        actionMode->setCheckable(true);
        actionMode->setChecked(false);
        actionSecurity = new QAction(mainForm);
        actionSecurity->setObjectName(QStringLiteral("actionSecurity"));
        actionSecurity->setCheckable(true);
        actionSecurity->setChecked(false);
        actionPrivacy = new QAction(mainForm);
        actionPrivacy->setObjectName(QStringLiteral("actionPrivacy"));
        actionPrivacy->setCheckable(true);
        actionPrivacy->setChecked(true);
        actionCipher = new QAction(mainForm);
        actionCipher->setObjectName(QStringLiteral("actionCipher"));
        actionCipher->setCheckable(true);
        actionCipher->setChecked(true);
        actionFrequency = new QAction(mainForm);
        actionFrequency->setObjectName(QStringLiteral("actionFrequency"));
        actionFrequency->setCheckable(true);
        actionQuality = new QAction(mainForm);
        actionQuality->setObjectName(QStringLiteral("actionQuality"));
        actionQuality->setCheckable(true);
        actionQuality->setChecked(false);
        actionSignal = new QAction(mainForm);
        actionSignal->setObjectName(QStringLiteral("actionSignal"));
        actionSignal->setCheckable(true);
        actionSignal->setChecked(true);
        actionBW = new QAction(mainForm);
        actionBW->setObjectName(QStringLiteral("actionBW"));
        actionBW->setCheckable(true);
        actionVendor = new QAction(mainForm);
        actionVendor->setObjectName(QStringLiteral("actionVendor"));
        actionVendor->setCheckable(true);
        actionVendor->setEnabled(true);
        actionVendor->setVisible(true);
        actionFirst = new QAction(mainForm);
        actionFirst->setObjectName(QStringLiteral("actionFirst"));
        actionFirst->setCheckable(true);
        actionFirst->setEnabled(true);
        actionFirst->setVisible(true);
        actionLast = new QAction(mainForm);
        actionLast->setObjectName(QStringLiteral("actionLast"));
        actionLast->setCheckable(true);
        actionLast->setEnabled(true);
        actionLast->setVisible(true);
        actionType = new QAction(mainForm);
        actionType->setObjectName(QStringLiteral("actionType"));
        actionType->setCheckable(true);
        actionType->setEnabled(false);
        actionType->setVisible(false);
        actionAbout = new QAction(mainForm);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCenChan = new QAction(mainForm);
        actionCenChan->setObjectName(QStringLiteral("actionCenChan"));
        actionCenChan->setCheckable(true);
        actionMin_Signal = new QAction(mainForm);
        actionMin_Signal->setObjectName(QStringLiteral("actionMin_Signal"));
        actionMin_Signal->setCheckable(true);
        actionMax_Signal = new QAction(mainForm);
        actionMax_Signal->setObjectName(QStringLiteral("actionMax_Signal"));
        actionMax_Signal->setCheckable(true);
        actionFirst_Seen = new QAction(mainForm);
        actionFirst_Seen->setObjectName(QStringLiteral("actionFirst_Seen"));
        actionFirst_Seen->setCheckable(true);
        actionLast_Seen = new QAction(mainForm);
        actionLast_Seen->setObjectName(QStringLiteral("actionLast_Seen"));
        actionLast_Seen->setCheckable(true);
        actionPlot = new QAction(mainForm);
        actionPlot->setObjectName(QStringLiteral("actionPlot"));
        actionPlot->setEnabled(false);
        actionPlot->setVisible(false);
        actionPrefs = new QAction(mainForm);
        actionPrefs->setObjectName(QStringLiteral("actionPrefs"));
        actionProtocol = new QAction(mainForm);
        actionProtocol->setObjectName(QStringLiteral("actionProtocol"));
        actionProtocol->setCheckable(true);
        actionProtocol->setChecked(true);
        centralwidget = new QWidget(mainForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonFrame = new QFrame(centralwidget);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonFrame->sizePolicy().hasHeightForWidth());
        buttonFrame->setSizePolicy(sizePolicy1);
        buttonFrame->setMinimumSize(QSize(500, 75));
        buttonFrame->setFrameShape(QFrame::StyledPanel);
        buttonFrame->setFrameShadow(QFrame::Sunken);
        formLayout = new QFormLayout(buttonFrame);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        interfaceCbx = new QComboBox(buttonFrame);
        interfaceCbx->setObjectName(QStringLiteral("interfaceCbx"));
        interfaceCbx->setMinimumSize(QSize(100, 27));

        gridLayout->addWidget(interfaceCbx, 0, 0, 1, 1);

        interfaceLbl = new QLabel(buttonFrame);
        interfaceLbl->setObjectName(QStringLiteral("interfaceLbl"));
        interfaceLbl->setMinimumSize(QSize(100, 20));
        interfaceLbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(interfaceLbl, 1, 0, 1, 1);

        runLbl = new QLabel(buttonFrame);
        runLbl->setObjectName(QStringLiteral("runLbl"));
        runLbl->setBaseSize(QSize(52, 20));
        runLbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(runLbl, 1, 1, 1, 1);

        runBtn = new QPushButton(buttonFrame);
        runBtn->setObjectName(QStringLiteral("runBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(runBtn->sizePolicy().hasHeightForWidth());
        runBtn->setSizePolicy(sizePolicy2);
        runBtn->setMinimumSize(QSize(52, 40));
        runBtn->setMaximumSize(QSize(52, 40));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../usr/share/linssid/linssid-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral("../../../../usr/share/linssid/linssid-pause.png"), QSize(), QIcon::Normal, QIcon::On);
        runBtn->setIcon(icon);
        runBtn->setIconSize(QSize(32, 32));
        runBtn->setCheckable(true);
        runBtn->setChecked(false);

        gridLayout->addWidget(runBtn, 0, 1, 1, 1);

        napTimeSlider = new QSlider(buttonFrame);
        napTimeSlider->setObjectName(QStringLiteral("napTimeSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(napTimeSlider->sizePolicy().hasHeightForWidth());
        napTimeSlider->setSizePolicy(sizePolicy3);
        napTimeSlider->setMinimumSize(QSize(120, 20));
        napTimeSlider->setBaseSize(QSize(120, 20));
        napTimeSlider->setMaximum(5);
        napTimeSlider->setPageStep(1);
        napTimeSlider->setSliderPosition(2);
        napTimeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(napTimeSlider, 0, 5, 1, 1);

        napTimeLbl = new QLabel(buttonFrame);
        napTimeLbl->setObjectName(QStringLiteral("napTimeLbl"));
        napTimeLbl->setMinimumSize(QSize(100, 0));
        napTimeLbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(napTimeLbl, 1, 5, 1, 1);

        statusTxt = new QLabel(buttonFrame);
        statusTxt->setObjectName(QStringLiteral("statusTxt"));
        sizePolicy1.setHeightForWidth(statusTxt->sizePolicy().hasHeightForWidth());
        statusTxt->setSizePolicy(sizePolicy1);
        statusTxt->setWordWrap(true);

        gridLayout->addWidget(statusTxt, 0, 3, 1, 1);

        statusLbl = new QLabel(buttonFrame);
        statusLbl->setObjectName(QStringLiteral("statusLbl"));
        sizePolicy1.setHeightForWidth(statusLbl->sizePolicy().hasHeightForWidth());
        statusLbl->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(statusLbl, 1, 3, 1, 1);

        graphLbl = new QLabel(buttonFrame);
        graphLbl->setObjectName(QStringLiteral("graphLbl"));
        graphLbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(graphLbl, 1, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        allBtn = new QPushButton(buttonFrame);
        allBtn->setObjectName(QStringLiteral("allBtn"));
        allBtn->setEnabled(true);
        allBtn->setMinimumSize(QSize(45, 0));
        allBtn->setMaximumSize(QSize(45, 16777215));

        horizontalLayout->addWidget(allBtn);

        noneBtn = new QPushButton(buttonFrame);
        noneBtn->setObjectName(QStringLiteral("noneBtn"));
        noneBtn->setEnabled(true);
        noneBtn->setMinimumSize(QSize(45, 0));
        noneBtn->setMaximumSize(QSize(45, 16777215));

        horizontalLayout->addWidget(noneBtn);


        gridLayout->addLayout(horizontalLayout, 0, 4, 1, 1);


        formLayout->setLayout(0, QFormLayout::SpanningRole, gridLayout);


        verticalLayout->addWidget(buttonFrame);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        splitter->setOpaqueResize(true);
        mainTableWidget = new QTableWidget(splitter);
        mainTableWidget->setObjectName(QStringLiteral("mainTableWidget"));
        sizePolicy.setHeightForWidth(mainTableWidget->sizePolicy().hasHeightForWidth());
        mainTableWidget->setSizePolicy(sizePolicy);
        mainTableWidget->setMinimumSize(QSize(0, 150));
        mainTableWidget->setSortingEnabled(true);
        splitter->addWidget(mainTableWidget);
        mainTabWgt = new QTabWidget(splitter);
        mainTabWgt->setObjectName(QStringLiteral("mainTabWgt"));
        sizePolicy.setHeightForWidth(mainTabWgt->sizePolicy().hasHeightForWidth());
        mainTabWgt->setSizePolicy(sizePolicy);
        mainTabWgt->setMinimumSize(QSize(0, 150));
        timePlotTab = new QWidget();
        timePlotTab->setObjectName(QStringLiteral("timePlotTab"));
        sizePolicy.setHeightForWidth(timePlotTab->sizePolicy().hasHeightForWidth());
        timePlotTab->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(timePlotTab);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        timePlot = new QwtPlot(timePlotTab);
        timePlot->setObjectName(QStringLiteral("timePlot"));

        verticalLayout_4->addWidget(timePlot);

        mainTabWgt->addTab(timePlotTab, QString());
        chan24Tab = new QWidget();
        chan24Tab->setObjectName(QStringLiteral("chan24Tab"));
        chan24Tab->setMinimumSize(QSize(0, 100));
        verticalLayout_2 = new QVBoxLayout(chan24Tab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        chan24Plot = new QwtPlot(chan24Tab);
        chan24Plot->setObjectName(QStringLiteral("chan24Plot"));
        sizePolicy.setHeightForWidth(chan24Plot->sizePolicy().hasHeightForWidth());
        chan24Plot->setSizePolicy(sizePolicy);
        chan24Plot->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(chan24Plot);

        mainTabWgt->addTab(chan24Tab, QString());
        chan5Tab = new QWidget();
        chan5Tab->setObjectName(QStringLiteral("chan5Tab"));
        sizePolicy.setHeightForWidth(chan5Tab->sizePolicy().hasHeightForWidth());
        chan5Tab->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(chan5Tab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        chan5Plot = new QwtPlot(chan5Tab);
        chan5Plot->setObjectName(QStringLiteral("chan5Plot"));

        verticalLayout_3->addWidget(chan5Plot);

        mainTabWgt->addTab(chan5Tab, QString());
        splitter->addWidget(mainTabWgt);

        verticalLayout->addWidget(splitter);

        mainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainForm);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 759, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        mainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(mainForm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        mainForm->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExport_to_NS1);
        menuFile->addSeparator();
        menuFile->addAction(actionPrefs);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionPlot);
        menuView->addAction(actionSSID);
        menuView->addAction(actionMAC);
        menuView->addAction(actionChannel);
        menuView->addAction(actionMode);
        menuView->addAction(actionSecurity);
        menuView->addAction(actionPrivacy);
        menuView->addAction(actionCipher);
        menuView->addAction(actionFrequency);
        menuView->addAction(actionQuality);
        menuView->addAction(actionSignal);
        menuView->addAction(actionBW);
        menuView->addAction(actionVendor);
        menuView->addAction(actionType);
        menuView->addAction(actionMin_Signal);
        menuView->addAction(actionMax_Signal);
        menuView->addAction(actionCenChan);
        menuView->addAction(actionFirst_Seen);
        menuView->addAction(actionLast_Seen);
        menuView->addAction(actionProtocol);
        menuHelp->addAction(actionAbout);

        retranslateUi(mainForm);
        QObject::connect(actionExit, SIGNAL(triggered()), mainForm, SLOT(close()));

        mainTabWgt->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(mainForm);
    } // setupUi

    void retranslateUi(QMainWindow *mainForm)
    {
        mainForm->setWindowTitle(QApplication::translate("mainForm", "LinSSID", Q_NULLPTR));
        actionExport_to_NS1->setText(QApplication::translate("mainForm", "&Export to NS1", Q_NULLPTR));
        actionExit->setText(QApplication::translate("mainForm", "E&xit", Q_NULLPTR));
        actionSSID->setText(QApplication::translate("mainForm", "&SSID", Q_NULLPTR));
        actionChannel->setText(QApplication::translate("mainForm", "&Channel", Q_NULLPTR));
        actionMAC->setText(QApplication::translate("mainForm", "&MAC", Q_NULLPTR));
        actionMode->setText(QApplication::translate("mainForm", "M&ode", Q_NULLPTR));
        actionSecurity->setText(QApplication::translate("mainForm", "S&ecurity", Q_NULLPTR));
        actionPrivacy->setText(QApplication::translate("mainForm", "P&rivacy", Q_NULLPTR));
        actionCipher->setText(QApplication::translate("mainForm", "C&ipher", Q_NULLPTR));
        actionFrequency->setText(QApplication::translate("mainForm", "&Frequency", Q_NULLPTR));
        actionQuality->setText(QApplication::translate("mainForm", "&Quality", Q_NULLPTR));
        actionSignal->setText(QApplication::translate("mainForm", "Si&gnal", Q_NULLPTR));
        actionBW->setText(QApplication::translate("mainForm", "&BW MHz", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionBW->setToolTip(QApplication::translate("mainForm", "Max Bandwidth", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionVendor->setText(QApplication::translate("mainForm", "&Vendor", Q_NULLPTR));
        actionFirst->setText(QApplication::translate("mainForm", "First", Q_NULLPTR));
        actionLast->setText(QApplication::translate("mainForm", "Last", Q_NULLPTR));
        actionType->setText(QApplication::translate("mainForm", "&Type", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("mainForm", "&About", Q_NULLPTR));
        actionCenChan->setText(QApplication::translate("mainForm", "Cen Chan", Q_NULLPTR));
        actionMin_Signal->setText(QApplication::translate("mainForm", "Mi&n Signal", Q_NULLPTR));
        actionMax_Signal->setText(QApplication::translate("mainForm", "Ma&x Signal", Q_NULLPTR));
        actionFirst_Seen->setText(QApplication::translate("mainForm", "First Seen", Q_NULLPTR));
        actionLast_Seen->setText(QApplication::translate("mainForm", "&Last Seen", Q_NULLPTR));
        actionPlot->setText(QApplication::translate("mainForm", "&Plot", Q_NULLPTR));
        actionPrefs->setText(QApplication::translate("mainForm", "&Preferences...", Q_NULLPTR));
        actionProtocol->setText(QApplication::translate("mainForm", "Protocol", Q_NULLPTR));
        interfaceCbx->clear();
        interfaceCbx->insertItems(0, QStringList()
         << QString()
        );
#ifndef QT_NO_TOOLTIP
        interfaceCbx->setToolTip(QApplication::translate("mainForm", "Select a wireless interface if you have more than one", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        interfaceLbl->setText(QApplication::translate("mainForm", "Interface", Q_NULLPTR));
        runLbl->setText(QApplication::translate("mainForm", "Run", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        runBtn->setToolTip(QApplication::translate("mainForm", "Start or stop run mode", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        napTimeSlider->setToolTip(QApplication::translate("mainForm", "Time between scans so your wireless interface can do something else", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        napTimeLbl->setText(QApplication::translate("mainForm", "0 - nap time - 5", Q_NULLPTR));
        statusTxt->setText(QApplication::translate("mainForm", "Paused", Q_NULLPTR));
        statusLbl->setText(QApplication::translate("mainForm", "Status", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        graphLbl->setToolTip(QApplication::translate("mainForm", "Select or deselect all visible APs", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        graphLbl->setText(QApplication::translate("mainForm", "Plot", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        allBtn->setToolTip(QApplication::translate("mainForm", "Select all visible APs", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        allBtn->setText(QApplication::translate("mainForm", "all", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        noneBtn->setToolTip(QApplication::translate("mainForm", "Deselect all visible APs", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        noneBtn->setText(QApplication::translate("mainForm", "none", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        mainTabWgt->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        timePlotTab->setToolTip(QApplication::translate("mainForm", "Signal strength over time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        mainTabWgt->setTabText(mainTabWgt->indexOf(timePlotTab), QApplication::translate("mainForm", "Time Graph", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chan24Tab->setToolTip(QApplication::translate("mainForm", "Signal strength by channel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        mainTabWgt->setTabText(mainTabWgt->indexOf(chan24Tab), QApplication::translate("mainForm", "2.4 GHz Channels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chan5Tab->setToolTip(QApplication::translate("mainForm", "Signal strength by channel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        mainTabWgt->setTabText(mainTabWgt->indexOf(chan5Tab), QApplication::translate("mainForm", "5 GHz Channels", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("mainForm", "Fi&le", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("mainForm", "&View", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("mainForm", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainForm: public Ui_mainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H

/*
 * File:   main.cpp
 * Author: warren
 *
 * Created on October 25, 2012, 11:41 AM
 */

#include <QtWidgets/QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <QThread>
#include <sys/stat.h>
#include "MainForm.h"
#include "ui_MainForm.h"
#include "Getter.h"
#include "Custom.h"

using namespace std;

// Globals here - TODO make some local where possible
string pipeName;
string password;
passStatus pwStatus;
string endBlockString = "-=-=-=-=-=-End block";
string beginBlockString = "-=-=-=-=-=-Begin block";
int lastBlockRequested;
int lastBlockReceived;
qint64 startTime;
ofstream linssidLog;
bool closing = false;

string genPipeName(int);

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    //  create instances of the main GUI and the worker thread and initialize
    Getter getter1; // instance of Getter
    MainForm form1; // instance of MainForm
    // make a thread for the getter and "movetothread"
    static QThread getter1Thread;
    getter1.moveToThread(&getter1Thread);
    // DEBUG create a log file
    linssidLog.open("/tmp/linssid_log", ios::out);
    linssidLog << "log file initiated " << endl;
    // create our named pipe for inter-thread data
    pipeName = genPipeName(10);
    mkfifo(pipeName.c_str(), 0666);
    form1.init(); // my own kludgy init, not part of constructor

    // Tell form1 and getter1 how to find each other
    form1.pGetter = &getter1; // form1 has a pointer to getter1
    getter1.pMainForm = &form1; // and getter1 has a pointer to form1
    form1.pGetterThread = &getter1Thread; // and form1 has a pointer to getter1 thread

    //  fire up the event loops and run the app
    getter1Thread.start(); // start getter1 event loop
    form1.show();
    
    return (app.exec());
}

string genPipeName(int len) {
    string charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string name = "/tmp/linssid_";
    for (int i = 0; i < len; i++) {
        name = name + charSet[rand() % charSet.size()];
    }
    return (name);
}
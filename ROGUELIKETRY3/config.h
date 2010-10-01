#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

class configInfo {
public:
    configInfo();      // Constructor (duh)
    configInfo(int x, int y);
    int readConfig();  // Reads configuration file
    void printVars();  // Prints out vars for debuggings
private:
    char *lMapHandler;
    string readTarget;
    ifstream config;   // Config file fstream handler
};

class logFile {
public:
    logFile();

    int readLogFile();
    int closeLogfile();

    ofstream log;
};
#endif

#include "config.h"

//CONSTRUCTORS
configInfo::configInfo() {
}

logFile::logFile() {   
}
//PUBLIC METHODS

// CONFIG FILE

int configInfo::readConfig() {
    config.open(readTarget, ifstream::in);
    char temp[25];
    while (config.good()) { // EOF, badbit and failbit
        config.getline(temp, 24, '=');
        //if (strcmp(temp, "width") == 0) {
        //    config.getline(temp, 10, '\n');
        //    width=atoi(temp);
        //}
    }
    config.close();

    return 0;
}

void configInfo::printVars() {
}

// LOG FILE
int logFile::readLogFile() {
    log.open("lab2.log", ifstream::out);
    return 0;
}

int logFile::closeLogfile() {
    if (log.good())
        log.close();
    return 0;
}
#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
enum LogStatus {
    None, Error, Warning, Verbose
};
class Log {
public:
    ///<summary>
    ///Appends a message into the log file
    ///</summary>
    static void log ( string message );
    static void log ( LogStatus logStatus, string message );
    static void setLogStatus ( LogStatus status );
    static LogStatus getLogStatus();
    static bool isLoggableStatus ( LogStatus status );
private:
    Log();
    ~Log();
    static string filename;
    static ofstream file;
    static LogStatus currentStatus;
};
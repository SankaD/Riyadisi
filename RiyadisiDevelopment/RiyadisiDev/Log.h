#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

class Log {
public:
    ///<summary>
    ///Appends a message into the log file
    ///</summary>
    static void log ( string message );
private:
    Log();
    ~Log();
    static string filename;
    static ofstream file;
};
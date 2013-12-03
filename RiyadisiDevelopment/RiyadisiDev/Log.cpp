#include "Log.h"

Log::Log() {
    filename = "log/log.log";

}

string Log::filename = "log/log.log";
ofstream Log::file = ofstream ( "" );


Log::~Log() {
    file.close();
}

void Log::log ( string message ) {
    log ( LogStatus::Verbose, message );
}
void Log::log ( LogStatus logStatus, string message ) {
    try {
        if ( !isLoggableStatus ( logStatus ) ) {
            return;
        }
        if ( !file.is_open() ) {
            file.open ( filename, fstream::app );
        }
        time_t t = time ( &t );
        file << t << " :: " ;
        file << message.c_str() << endl;
        file.flush();

    } catch ( exception ex ) {
        cerr << ex.what() << endl;
    }
}
void Log::setLogStatus ( LogStatus status ) {
    currentStatus = status;
}
LogStatus Log::getLogStatus() {
    return currentStatus;
}
bool Log::isLoggableStatus ( LogStatus status ) {
    return status <= currentStatus;
}
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
    try {
        if ( !file.is_open() ) {
            file.open ( filename, fstream::app );
        }
        time_t t = time ( &t );
        file << t << " :: " ;
        file << message.c_str() << endl;
    } catch ( exception ex ) {
        cerr << ex.what() << endl;
    }
}
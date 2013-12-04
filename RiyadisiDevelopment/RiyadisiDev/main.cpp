
#include "MainProgram.h"

int main ( int argc, char **argv ) {
    try {
        MainProgram program;

        int key = 0;
        cout << "Select Mode : " << endl;
        cout << "\tNormal = 1\n\tTraining = 2\n\tTrainingFileCreation = 3" << endl;
        //cin >> key;
        key = 1;
        switch ( key ) {
            case 1:
                program.run();
                break;
            case 2:
                program.trainingRun();
                break;
            case 3:
                program.createTrainingFile();
            default:
                break;
        }
    } catch ( exception ex ) {
        Log::log ( LogStatus::Error, ex.what() );
    }
}

#include "MainProgram.h"

int main ( int argc, char **argv ) {
    MainProgram program;

    int key = 0;
    cout << "Select Mode : " << endl;
    cout << "Normal = 1,Training = 2, TrainingFileCreation =3" << endl;
    cin >> key;
    switch ( key ) {
        case 1:
            program.run();
            break;
        case 2:
            program.trainingRun();
            break;
        case 3:
        default:
            break;
    }

}
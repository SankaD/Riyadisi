#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

class TrainingFileCreator {
public:
    TrainingFileCreator ( void );
    ~TrainingFileCreator ( void );
    void trainUsingFile ( string fileName );
};


#include "NoddingOffDetector.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;


time_t t = clock();
int noFrames = 10;
int checkedFrames = 0;
int prv_right_y_cordinate = 0, prv_left_y_cordinate = 0, prv_nose_y_cordinate = 0;
cv::Mat right_seq ( 1, noFrames, CV_32F );
cv::Mat left_seq ( 1, noFrames, CV_32F );
cv::Mat nose_seq ( 1, noFrames, CV_32F );

cv::Mat cordinate ( 1, noFrames, CV_32F );
cv::Mat estates;
int refCheckedFrames = 0;

double TRANSdata[] = {0.584793, 0.415207, 0.770872, 0.229128 };
cv::Mat TRANS = cv::Mat ( 2, 2, CV_64F, TRANSdata ).clone();

double EMISdata[] = {0.460842, 0.296699, 0.242459, 0.323301, 0.349412, 0.327287  };
cv::Mat EMIS = cv::Mat ( 2, 3, CV_64F, EMISdata ).clone();
double INITdata[] = {0.393388, 0.606612 };
cv::Mat INIT = cv::Mat ( 1, 2, CV_64F, INITdata ).clone();

//double TRANSdata[] = {0.562714, 0.437286,0.732984, 0.267016  };
//cv::Mat TRANS = cv::Mat(2,2,CV_64F,TRANSdata).clone();
//
//double EMISdata[] = {0.337905, 0.416392, 0.245703,0.209707, 0.535413, 0.25488  };
//cv::Mat EMIS = cv::Mat(2,3,CV_64F,EMISdata).clone();
//double INITdata[] = {0.401876, 0.598124 };
//cv::Mat INIT = cv::Mat(1,2,CV_64F,INITdata).clone();


double NoddingOffDetector::noddingOffDetect ( FaceFeature feature ) {

    std:: ofstream outputFile ( "states.txt", std::ios::app );
    int prv_x_cordinate = 0;
    int states[3];
    float right_noddingOffLevel = 0, left_noddingOffLevel = 0.0, noddingOffLevel = 0.0, nose_noddingOffLevel = 0.0;
    states[0] = 0, states[1] = 0, states[2] = 0;
    double value = 0.0;
    Rect leftEyeRect;
    Rect rightEyeRect;
    Rect noseRect;

    if ( feature.isAvailable() ) {

        leftEyeRect = feature.getLeftEye()->getFeatureRect();
        rightEyeRect = feature.getRightEye()->getFeatureRect();
        noseRect = feature.getNose()->getFeatureRect();


        rightEyeRect.y = rightEyeRect.x + feature.getFeatureRect().y;
        leftEyeRect.y = leftEyeRect.x + feature.getFeatureRect().y;
        noseRect.y = noseRect.x + feature.getFeatureRect().y;

    } else {

        rightEyeRect.y = prv_right_y_cordinate;
        leftEyeRect.y = prv_left_y_cordinate;
        noseRect.y = prv_nose_y_cordinate;

    }

    if ( checkedFrames < noFrames ) {

        int difference = rightEyeRect.y - prv_right_y_cordinate;

        if ( -2 <= difference && difference <= 2 ) {
            right_seq.at<int> ( 0, checkedFrames ) = 0;
        } else if ( difference > 2 ) {
            right_seq.at<int> ( 0, checkedFrames ) = 1;
        } else if ( difference < -2 ) {
            right_seq.at<int> ( 0, checkedFrames ) = 2;
        }
        prv_right_y_cordinate = rightEyeRect.y;

        difference = leftEyeRect.y - prv_left_y_cordinate;

        if ( -2 <= difference && difference <= 2 ) {
            left_seq.at<int> ( 0, checkedFrames ) = 0;


        }

        else if ( difference > 2 ) {
            left_seq.at<int> ( 0, checkedFrames ) = 1;


        } else if ( difference < -2 ) {
            left_seq.at<int> ( 0, checkedFrames ) = 2;

        }
        prv_left_y_cordinate = leftEyeRect.y;



        difference = noseRect.y - prv_nose_y_cordinate;

        if ( -2 <= difference && difference <= 2 ) {
            nose_seq.at<int> ( 0, checkedFrames ) = 0;


        }

        else if ( difference > 2 ) {
            nose_seq.at<int> ( 0, checkedFrames ) = 1;


        } else if ( difference < -2 ) {
            nose_seq.at<int> ( 0, checkedFrames ) = 2;

        }
        prv_nose_y_cordinate = noseRect.y;
        checkedFrames++;

    } else {

        viterbi ( right_seq.row ( 0 ), TRANS, EMIS, INIT, estates );
        for ( int i = 0; i < estates.cols; i++ ) {
            states[estates.at<int> ( 0, i )]++ ;
            //outputFile<<estates.at<int>(0,i);
        }

        value = static_cast<double> ( states[0] );

        right_noddingOffLevel = value / noFrames ;

        states[0] = 0, states[1] = 0, states[2] = 0;
        viterbi ( left_seq.row ( 0 ), TRANS, EMIS, INIT, estates );
        for ( int i = 0; i < estates.cols; i++ ) {
            states[estates.at<int> ( 0, i )]++ ;
            //outputFile<<estates.at<int>(0,i);
        }
        value = static_cast<double> ( states[0] );

        left_noddingOffLevel = value / noFrames ;


        states[0] = 0, states[1] = 0, states[2] = 0;
        viterbi ( nose_seq.row ( 0 ), TRANS, EMIS, INIT, estates );
        for ( int i = 0; i < estates.cols; i++ ) {
            states[estates.at<int> ( 0, i )]++ ;
            //outputFile<<estates.at<int>(0,i);
        }
        value = static_cast<double> ( states[0] );

        nose_noddingOffLevel = value / noFrames ;

        noddingOffLevel = ( left_noddingOffLevel + right_noddingOffLevel + nose_noddingOffLevel ) / 3;

        checkedFrames = 0 ;

        outputFile << "      Nodding off level  " << noddingOffLevel;
        outputFile << "\n";

        return noddingOffLevel;
    }

    return 0.0;
}

void NoddingOffDetector::train() {

    int line;
    int index = 0;
    string istream_iterator;
    cv::Mat seqMatrix;
    vector<int> seq;

    std:: ifstream  seqfile ( "observations.txt", ios::in );

    if ( seqfile.is_open() ) {
        while ( seqfile >> line ) {

            seq.push_back ( line );

        }

        for ( int i = 0; i < 500; i++ ) {

            for ( int j = 0; j < noFrames; j++ ) {
                seqMatrix.at<int> ( i, j ) = seq[i + j];
            }
        }

        seqfile.close();

    } else { std::cout << "Unable to open file"; }

    double TRGUESSdata[] = {0.4 , 0.6,
                            0.4, 0.6
                           };
    cv::Mat TRGUESS = cv::Mat ( 2, 2, CV_64F, TRGUESSdata ).clone();
    double EMITGUESSdata[] = {1.0 / 3.0 , 1.0 / 3.0 , 1.0 / 3.0 , 1.0 / 3.0 ,
                              1.0 / 3.0 , 1.0 / 3.0
                             };
    cv::Mat EMITGUESS = cv::Mat ( 2, 3, CV_64F, EMITGUESSdata ).clone();
    double INITGUESSdata[] = {0.4  , 0.6 };
    cv::Mat INITGUESS = cv::Mat ( 1, 2, CV_64F, INITGUESSdata ).clone();

    trainBaumWelch ( seqMatrix, 1000, TRGUESS, EMITGUESS, INITGUESS );
}

void NoddingOffDetector::collectTraningData ( FaceFeature feature ) {

    int states[2];
    std:: ofstream outputFile ( "newobservations.txt", std::ios::app );
    Rect leftEyeRect;
    Rect rightEyeRect;
    Rect noseRect;

    states[0] = 0, states[1] = 0;



    if ( feature.isAvailable() ) {

        leftEyeRect = feature.getLeftEye()->getFeatureRect();
        rightEyeRect = feature.getRightEye()->getFeatureRect();
        noseRect = feature.getNose()->getFeatureRect();


        rightEyeRect.y = rightEyeRect.x + feature.getFeatureRect().y;
        leftEyeRect.y = leftEyeRect.x + feature.getFeatureRect().y;
        noseRect.y = noseRect.x + feature.getFeatureRect().y;

    } else {

        rightEyeRect.y = prv_right_y_cordinate;
        leftEyeRect.y = prv_left_y_cordinate;
        noseRect.y = prv_nose_y_cordinate;

    }



    if ( checkedFrames < noFrames ) {

        int difference = rightEyeRect.y - prv_right_y_cordinate;

        if ( -2 <= difference && difference <= 2 ) {
            right_seq.at<int> ( 0, checkedFrames ) = 0;


        }

        else if ( difference > 2 ) {
            right_seq.at<int> ( 0, checkedFrames ) = 1;


        } else if ( difference < -2 ) {
            right_seq.at<int> ( 0, checkedFrames ) = 2;

        }
        prv_right_y_cordinate = rightEyeRect.y;



        difference = leftEyeRect.y - prv_left_y_cordinate;

        if ( -2 <= difference && difference <= 2 ) {
            left_seq.at<int> ( 0, checkedFrames ) = 0;

        }

        else if ( difference > 2 ) {
            left_seq.at<int> ( 0, checkedFrames ) = 1;


        } else if ( difference < -2 ) {
            left_seq.at<int> ( 0, checkedFrames ) = 2;

        }
        prv_left_y_cordinate = leftEyeRect.y;



        difference = noseRect.y - prv_nose_y_cordinate;

        if ( -2 <= difference && difference <= 2 ) {
            nose_seq.at<int> ( 0, checkedFrames ) = 0;


        }

        else if ( difference > 2 ) {
            nose_seq.at<int> ( 0, checkedFrames ) = 1;


        } else if ( difference < -2 ) {
            nose_seq.at<int> ( 0, checkedFrames ) = 2;

        }
        prv_nose_y_cordinate = noseRect.y;
        checkedFrames++;

    }

    else {

        for ( int i = 0; i < noFrames; i++ )

        {
            outputFile << right_seq.at<int> ( 0, i );
            outputFile << ",";
        }
        outputFile << "\n";


        for ( int i = 0; i < noFrames; i++ )

        {
            outputFile << left_seq.at<int> ( 0, i );
            outputFile << ",";
        }
        outputFile << "\n";


        for ( int i = 0; i < noFrames; i++ )

        {
            outputFile << nose_seq.at<int> ( 0, i );
            outputFile << ",";
        }
        outputFile << "\n";



        checkedFrames = 0;

    }

//outputFile<<rightEyeRect.y ;
//outputFile<<"\n";
    outputFile.close();
}

void NoddingOffDetector::viterbi ( const cv::Mat &seq, const cv::Mat &_TRANS, const cv::Mat &_EMIS, const cv::Mat &_INIT, cv::Mat &states ) {
    /* Viterbi Algorithm, Wikipedia */
    cv::Mat TRANS = _TRANS.clone();
    cv::Mat EMIS = _EMIS.clone();
    cv::Mat INIT = _INIT.clone();
    correctModel ( TRANS, EMIS, INIT );
    int nseq = seq.cols;
    int nstates = TRANS.cols;
    int nobs = EMIS.cols;
    cv::Mat v ( nstates, nseq, CV_64F );
    cv::Mat path ( nstates, nseq, CV_32S );
    path = 0.0f;
    cv::Mat newpath ( nstates, nseq, CV_32S );
    newpath = 0.0f;
    for ( int y = 0; y < nstates; y++ ) {
        v.at<double> ( y, 0 ) = log ( INIT.at<double> ( 0, y ) ) + log ( EMIS.at<double> ( y, seq.at<int> ( 0, 0 ) ) );
        path.at<int> ( y, 0 ) = y;
    }
    double maxp, p;
    int state;
    for ( int t = 1; t < nseq; t++ ) {
        for ( int y = 0; y < nstates; y++ ) {
            maxp = -DBL_MAX;
            state = y;
            for ( int y0 = 0; y0 < nstates; y0++ ) {
                p = v.at<double> ( y0, t - 1 ) + log ( TRANS.at<double> ( y0, y ) ) + log ( EMIS.at<double> ( y, seq.at<int> ( 0, t ) ) );
                if ( maxp < p ) {
                    maxp = p;
                    state = y0;
                }
            }
            v.at<double> ( y, t ) = maxp;
            for ( int t1 = 0; t1 < t; t1++ )
            { newpath.at<int> ( y, t1 ) = path.at<int> ( state, t1 ); }
            newpath.at<int> ( y, t ) = y;
        }
        path.release();
        path = newpath.clone();
    }
    maxp = -DBL_MAX;
    for ( int y = 0; y < nstates; y++ ) {
        if ( maxp < v.at<double> ( y, nseq - 1 ) ) {
            maxp = v.at<double> ( y, nseq - 1 );
            state = y;
        }
    }
    states = path.row ( state ).clone();
}


void NoddingOffDetector::getUniformModel ( const int &n_states, const int &n_observations, cv::Mat &TRANS, cv::Mat &EMIS, cv::Mat &INIT ) {
    TRANS = cv::Mat ( n_states, n_states, CV_64F );
    TRANS = 1.0 / n_states;
    INIT = cv::Mat ( 1, n_states, CV_64F );
    INIT = 1.0 / n_states;
    EMIS = cv::Mat ( n_states, n_observations, CV_64F );
    EMIS = 1.0 / n_observations;
}

/* Calculates maximum likelihood estimates of transition and emission probabilities from a sequence of emissions */
void NoddingOffDetector::trainBaumWelch ( const cv::Mat &seq, const int max_iter, cv::Mat &TRANS, cv::Mat &EMIS, cv::Mat &INIT, bool UseUniformPrior ) {
    /* A Revealing Introduction to Hidden Markov Models, Mark Stamp */
    // 1. Initialization
    int iters = 0;
    int T = seq.cols; // number of element per sequence
    int C = seq.rows; // number of sequences
    int N = TRANS.rows; // number of states | also N = TRANS.cols | TRANS = A = {aij} - NxN
    int M = EMIS.cols; // number of observations | EMIS = B = {bj(k)} - NxM
    correctModel ( TRANS, EMIS, INIT );
    cv::Mat FTRANS, FINIT, FEMIS;
    if ( UseUniformPrior )
    { getUniformModel ( N, M, FTRANS, FEMIS, FINIT ); }
    else {
        FTRANS = TRANS.clone();
        FEMIS = EMIS.clone();
        FINIT = INIT.clone();
    }
    // compute a0
    cv::Mat a ( N, T, CV_64F );
    cv::Mat c ( 1, T, CV_64F );
    c.at<double> ( 0, 0 ) = 0;
    for ( int i = 0; i < N; i++ ) {
        a.at<double> ( i, 0 ) = INIT.at<double> ( 0, i ) * EMIS.at<double> ( i, seq.at<int> ( 0, 0 ) );
        c.at<double> ( 0, 0 ) += a.at<double> ( i, 0 );
    }
    // scale the a0(i)
    c.at<double> ( 0, 0 ) = 1 / c.at<double> ( 0, 0 );
    for ( int i = 0; i < N; i++ )
    { a.at<double> ( i, 0 ) *= c.at<double> ( 0, 0 ); }
    double logProb = -DBL_MAX;
    double oldLogProb;
    int data = 0;
    do {
        oldLogProb = logProb;
        // 2. The a-pass
        // compute at(i)
        for ( int t = 1; t < T; t++ ) {
            c.at<double> ( 0, t ) = 0;
            for ( int i = 0; i < N; i++ ) {
                a.at<double> ( i, t ) = 0;
                for ( int j = 0; j < N; j++ )
                { a.at<double> ( i, t ) += a.at<double> ( i, t - 1 ) * TRANS.at<double> ( j, i ); }
                std::cout << EMIS.at<double> ( i, seq.at<int> ( data, t ) );
                std::cout << "\n";
                a.at<double> ( i, t ) = a.at<double> ( i, t ) * EMIS.at<double> ( i, seq.at<int> ( data, t ) );
                c.at<double> ( 0, t ) += a.at<double> ( i, t );
            }
            // scale at(i)
            c.at<double> ( 0, t ) = 1 / c.at<double> ( 0, t );
            for ( int i = 0; i < N; i++ )
            { a.at<double> ( i, t ) = c.at<double> ( 0, t ) * a.at<double> ( i, t ); }
        }
        // 3. The B-pass
        cv::Mat b ( N, T, CV_64F );
        // Let Bt-1(i) = 1 scaled by Ct-1
        for ( int i = 0; i < N; i++ )
        { b.at<double> ( i, T - 1 ) = c.at<double> ( 0, T - 1 ); }
        // B-pass
        for ( int t = T - 2; t > -1; t-- )
            for ( int i = 0; i < N; i++ ) {
                b.at<double> ( i, t ) = 0;
                for ( int j = 0; j < N; j++ )
                { b.at<double> ( i, t ) += TRANS.at<double> ( i, j ) * EMIS.at<double> ( j, seq.at<int> ( data, t + 1 ) ) * b.at<double> ( j, t + 1 ); }
                // scale Bt(i) with same scale factor as at(i)
                b.at<double> ( i, t ) *= c.at<double> ( 0, t );
            }
        // 4. Compute  Yt(i,j) and Yt(i)
        double denom;
        int index;
        cv::Mat YN ( N, T, CV_64F );
        cv::Mat YNN ( N * N, T, CV_64F );
        for ( int t = 0; t < T - 1; t++ ) {
            denom = 0;
            for ( int i = 0; i < N; i++ )
                for ( int j = 0; j < N; j++ )
                { denom += a.at<double> ( i, t ) * TRANS.at<double> ( i, j ) * EMIS.at<double> ( j, seq.at<int> ( data, t + 1 ) ) * b.at<double> ( j, t + 1 ); }
            index = 0;
            for ( int i = 0; i < N; i++ ) {
                YN.at<double> ( i, t ) = 0;
                for ( int j = 0; j < N; j++ ) {
                    YNN.at<double> ( index, t ) = ( a.at<double> ( i, t ) * TRANS.at<double> ( i, j ) * EMIS.at<double> ( j, seq.at<int> ( data, t + 1 ) ) * b.at<double> ( j, t + 1 ) ) / denom;
                    double test = 	YN.at<double> ( i, t ) += YNN.at<double> ( index, t );
                    index++;
                }
            }
        }
        // 5. Re-estimate A,B and pi
        // re-estimate pi
        for ( int i = 0; i < N; i++ )
        { INIT.at<double> ( 0, i ) = YN.at<double> ( i, 0 ); }
        // re-estimate A
        double numer;
        index = 0;
        for ( int i = 0; i < N; i++ )
            for ( int j = 0; j < N; j++ ) {
                numer = 0;
                denom = 0;
                for ( int t = 0; t < T - 1; t++ ) {
                    numer += YNN.at<double> ( index, t );
                    denom += YN.at<double> ( i, t );
                }
                TRANS.at<double> ( i, j ) = numer / denom;
                index++;
            }
        // re-estimate B
        for ( int i = 0; i < N; i++ )
            for ( int j = 0; j < M; j++ ) {
                numer = 0;
                denom = 0;
                for ( int t = 0; t < T - 1; t++ ) {
                    if ( seq.at<int> ( data, t ) == j )
                    { numer += YN.at<double> ( i, t ); }
                    denom += YN.at<double> ( i, t );
                }
                EMIS.at<double> ( i, j ) = numer / denom;
            }
        correctModel ( TRANS, EMIS, INIT );
        FTRANS = ( FTRANS * ( data + 1 ) + TRANS ) / ( data + 2 );
        FEMIS = ( FEMIS * ( data + 1 ) + EMIS ) / ( data + 2 );
        FINIT = ( FINIT * ( data + 1 ) + INIT ) / ( data + 2 );
        // 6. Compute log[P(O|y)]
        logProb = 0;
        for ( int i = 0; i < T; i++ )
        { logProb += log ( c.at<double> ( 0, i ) ); }
        logProb *= -1;
        // 7. To iterate or not
        data++;
        if ( data >= C ) {
            data = 0;
            iters++;
        }
    } while ( iters < max_iter && logProb > oldLogProb );
    correctModel ( FTRANS, FEMIS, FINIT );
    TRANS = FTRANS.clone();
    EMIS = FEMIS.clone();
    INIT = FINIT.clone();
}
void NoddingOffDetector::correctModel ( cv::Mat &TRANS, cv::Mat &EMIS, cv::Mat &INIT ) {
    double eps = 1e-30;
    for ( int i = 0; i < EMIS.rows; i++ )
        for ( int j = 0; j < EMIS.cols; j++ )
            if ( EMIS.at<double> ( i, j ) == 0 )
            { EMIS.at<double> ( i, j ) = eps; }
    for ( int i = 0; i < TRANS.rows; i++ )
        for ( int j = 0; j < TRANS.cols; j++ )
            if ( TRANS.at<double> ( i, j ) == 0 )
            { TRANS.at<double> ( i, j ) = eps; }
    for ( int i = 0; i < INIT.cols; i++ )
        if ( INIT.at<double> ( 0, i ) == 0 )
        { INIT.at<double> ( 0, i ) = eps; }
    double sum;
    for ( int i = 0; i < TRANS.rows; i++ ) {
        sum = 0;
        for ( int j = 0; j < TRANS.cols; j++ )
        { sum += TRANS.at<double> ( i, j ); }
        for ( int j = 0; j < TRANS.cols; j++ )
        { TRANS.at<double> ( i, j ) /= sum; }
    }
    for ( int i = 0; i < EMIS.rows; i++ ) {
        sum = 0;
        for ( int j = 0; j < EMIS.cols; j++ )
        { sum += EMIS.at<double> ( i, j ); }
        for ( int j = 0; j < EMIS.cols; j++ )
        { EMIS.at<double> ( i, j ) /= sum; }
    }
    sum = 0;
    for ( int j = 0; j < INIT.cols; j++ )
    { sum += INIT.at<double> ( 0, j ); }
    for ( int j = 0; j < INIT.cols; j++ )
    { INIT.at<double> ( 0, j ) /= sum; }
}
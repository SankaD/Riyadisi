#include "EyeStateDetector.h"

float EyeStateDetector:: calculateEyeState(Mat eye) {

    //opening matlab engine
    Engine *ep;
    //char *buffer;      // to store the output from matlab
    //int nbuff = 4096; //buffer size

    if (!(ep = engOpen("\0"))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n"); //error message
        return EXIT_FAILURE;
    }


    /*if( (buffer = (char *) malloc(nbuff)) == NULL ) //not enough memory
    printf("Unable to allocate output buffer\n");  //buffer is allocated for each eye

    */

    mxArray *image =mxCreateDoubleMatrix(eye.rows, eye.cols, mxREAL); //matlab array for the image
    mxArray *z=mxCreateDoubleMatrix(1, 1, mxREAL); //array for the matlab output (one element array)

    double *matbuffer=(double*)mxGetPr(image); //get real component of the image(mxArray is of type complex)
    double *matz=(double*)mxGetPr(z);  //get real component of the output array(mxArray is of type complex)


    for(int row=0; row<eye.rows; row++) {
        for(int col=0; col<eye.cols; col++) {


            matbuffer[col*(eye.rows)+row]= (double)eye.at<unsigned char>(row, col); //assign array in col major order

        }
    }


    engPutVariable(ep,"im",image); //put variables in matlab workspace
    engPutVariable(ep,"z",z);


    //engOutputBuffer(ep, buffer, nbuff); //specify the buffer to store matlab output
    engEvalString(ep,"z=Classify(im)"); //call the eye state classifier

    /*	if( buffer != NULL )
    printf(buffer);         //print the output

    free(buffer);*/


    mxArray *mresult;
    double *cresult;
    mresult = engGetVariable(ep,"z");

    if(mresult==NULL)
        cout<< "NULL pointer";


    cresult = mxGetPr(mresult);

    double result= cresult[0];

    cout<< endl;
    if(result==0)
        cout << "Open eye";
    else if(result==1)cout << "Closed eye";
    cout<< endl;

    mxDestroyArray(mresult);
    mxDestroyArray(image);
    mxDestroyArray(z);


    return result;

}
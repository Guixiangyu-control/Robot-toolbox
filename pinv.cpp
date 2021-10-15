#include "pinv.h"

void pinv(){

};

void cross3d(double* A,double* B,double* result){
    result[0]=A[1]*B[2]-B[1]*A[2];
    result[1]=-(A[0]*B[2]-B[0]*A[2]);
    result[2]=A[0]*B[1]-B[0]*A[1];
}

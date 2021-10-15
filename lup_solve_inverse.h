#ifndef LUP_SOLVE_INVERSE_H
#define LUP_SOLVE_INVERSE_H


void LUP_Descomposition(double* A, double* L, double* U, int* P,int n);
double * LUP_Solve(double* L, double* U, int* P, double* b,int n);
int getnext(int i, int m, int n);
int getPre(int i, int m, int n);
void movedata(double *mtx, int i, int m, int n);
void transpose(double *mtx, int m, int n);
double * LUP_solve_inverse(double* A,int n);

#endif // LUP_SOLVE_INVERSE_H

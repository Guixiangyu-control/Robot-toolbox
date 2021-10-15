#include <QDebug>
#include <cmath>
/*
https://blog.csdn.net/weixin_30666401/article/details/97220548
*/
using namespace std;
//LUP分解
void LUP_Descomposition(double* A, double* L, double* U, int* P,int n)
{
    int row = 0;
    for (int i = 0; i < n; i++)
    {
         P[i] = i;
    }
    for (int i = 0; i < n - 1; i++)
    {
         double p = 0.0;
         for (int j = i; j < n; j++)
         {
               if (abs(A[j*n + i]) > p)
               {
                     p = abs(A[j*n + i]);
                     row = j;
                }
         }
         if (0 == p)
         {
                qDebug() << "矩阵奇异，无法计算逆" << endl;
                return;
         }

         //交换P[i]和P[row]
         int tmp = P[i];
         P[i] = P[row];
         P[row] = tmp;

         double tmp2 = 0.0;
         for (int j = 0; j < n; j++)
         {
              //交换A[i][j]和 A[row][j]
              tmp2 = A[i*n + j];
              A[i*n + j] = A[row*n + j];
              A[row*n + j] = tmp2;
         }

         //以下同LU分解
         double u = A[i*n + i], l = 0.0;
         for (int j = i + 1; j < n; j++)
         {
              l = A[j*n + i] / u;
              A[j*n + i] = l;
              for (int k = i + 1; k < n; k++)
              {
                    A[j*n + k] = A[j*n + k] - A[i*n + k] * l;
              }
         }

     }

     //构造L和U
     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j <= i; j++)
          {
                if (i != j)
                {
                     L[i*n + j] = A[i*n + j];
                 }
                 else
                 {
                     L[i*n + j] = 1;
                 }
           }
           for (int k = i; k < n; k++)
           {
                 U[i*n + k] = A[i*n + k];
           }
      }

}

//LUP求解方程
double * LUP_Solve(double* L, double* U, int* P, double* b,int n)
{
    double *x = new double[n]();
    double *y = new double[n]();

    //正向替换
    for (int i = 0; i < n; i++)
    {
          y[i] = b[P[i]];
          for (int j = 0; j < i; j++)
          {
                y[i] = y[i] - L[i*n + j] * y[j];
          }
    }
    //反向替换
    for (int i = n - 1; i >= 0; i--)
    {
         x[i] = y[i];
         for (int j = n - 1; j > i; j--)
         {
              x[i] = x[i] - U[i*n + j] * x[j];
          }
              x[i] /= U[i*n + i];
     }

     delete[] L;
     delete[] U;
     delete[] P;
     return x;
}

/*****************矩阵原地转置BEGIn********************/

/* 后继 */
int getnext(int i, int m, int n)
{
      return (i%n)*m + i / n;
}

/* 前驱 */
int getPre(int i, int m, int n)
{
     return (i%m)*n + i / m;
}

/* 处理以下标i为起点的环 */
void movedata(double *mtx, int i, int m, int n)
{
      double temp = mtx[i]; // 暂存
      int cur = i;    // 当前下标
      int pre = getPre(cur, m, n);
      while (pre != i)
      {
           mtx[cur] = mtx[pre];
           cur = pre;
           pre = getPre(cur, m, n);
      }
      mtx[cur] = temp;
}
/* 转置，即循环处理所有环 */
void transpose(double *mtx, int m, int n)
{
      for(int i = 0; i < m*n; ++i)
      {
            int next = getnext(i, m, n);
            while (next > i){ // 若存在后继小于i说明重复,就不进行下去了（只有不重复时进入while循环）
                next = getnext(next, m, n);
            }
            if (next == i){  // 处理当前环
                movedata(mtx, i, m, n);
            }
      }
}
/*****************矩阵原地转置EnD********************/

//LUP求逆(将每列b求出的各列x进行组装)
double * LUP_solve_inverse(double* A,int n)
{
        //创建矩阵A的副本，注意不能直接用A计算，因为LUP分解算法已将其改变
        double *A_mirror = new double[n*n]();
        double *inv_A = new double[n*n]();//最终的逆矩阵（还需要转置）
        double *inv_A_each = new double[n*n]();//矩阵逆的各列
       //double *B    =new double[n*n]();
        double *b = new double[n*n]();//b阵为B阵的列矩阵分量

        for (int i = 0; i < n; i++)
        {
           double *L = new double[n*n]();
           double *U = new double[n*n]();
           int *P = new int[n]();

           //构造单位阵的每一列
           for (int i = 0; i < n; i++)
           {
                 b[i] = 0;
           }
            b[i] = 1;

           //每次都需要重新将A复制一份
            for (int i = 0; i < n*n; i++)
            {
                  A_mirror[i] = A[i];
            }

            LUP_Descomposition(A_mirror, L, U, P,n);

            inv_A_each = LUP_Solve(L, U, P, b,n);
            memcpy(inv_A + i * n, inv_A_each, n * sizeof(double));//将各列拼接起来
        }
        transpose(inv_A, n, n);//由于现在根据每列b算出的x按行存储，因此需转置

        delete[] A_mirror;
        delete[] b;
        return inv_A;
}

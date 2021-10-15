#include "mythread.h"
#include "lup_solve_inverse.h"
#include <QDebug>

typedef std::vector<double> state_type;
struct state{
    state_type StateX;
    state_type StateY;
    state_type StateZ;
    state_type StateR;
    state_type StateP;
    state_type StateGamma;
    state_type time;
} state;


MyThread::MyThread(QObject *parent) : QObject(parent)
{
}

MyThread::~MyThread(){
    free(inter);
    free(mytimeDiff);
    free(mymat);
}

void MyThread::calcoefficient(double coefficient[][100]){
    if(mypointnumber==2){
        double invT[4][4]={{0}};
        invT[0][0]=1;
        invT[1][2]=1;
        invT[2][0]=-3/(mytimeDiff[0]*mytimeDiff[0]);
        invT[2][1]=3/(mytimeDiff[0]*mytimeDiff[0]);
        invT[2][2]=-2/mytimeDiff[0];
        invT[2][3]=-1/mytimeDiff[0];
        invT[3][0]=2/(mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0]);
        invT[3][1]=-2/(mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0]);
        invT[3][2]=1/(mytimeDiff[0]*mytimeDiff[0]);
        invT[3][3]=1/(mytimeDiff[0]*mytimeDiff[0]);

        double matFor46[4][6]={{0}};
        for(int i=0;i<2;++i){
            for(int j=0;j<6;++j)
            {
                matFor46[i][j]=mymat[i*6+j];
            }
        }


        for(int i=0;i<4;++i){
            for(int j=0;j<6;++j){
                for(int k=0;k<4;++k){
                    coefficient[i][j]+=invT[i][k]*matFor46[k][j];
                }
            }
        }
    }
    else if(mypointnumber==3){
        double T[64]={0};
        T[0]=1,
        T[8]=1,T[9]=mytimeDiff[0],T[10]=mytimeDiff[0]*mytimeDiff[0],T[11]=mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0],
        T[20]=1,T[28]=1,T[29]=mytimeDiff[1],T[30]=mytimeDiff[1]*mytimeDiff[1],T[31]=mytimeDiff[1]*mytimeDiff[1]*mytimeDiff[1],
        T[33]=1,T[45]=1,T[46]=2*mytimeDiff[1],T[47]=3*mytimeDiff[1]*mytimeDiff[1],
        T[49]=1,T[50]=2*mytimeDiff[0],T[51]=3*mytimeDiff[0]*mytimeDiff[0],T[53]=-1,
        T[58]=2,T[59]=6*mytimeDiff[0],T[62]=-2;
        double* invT_mirror=new double[64];
        invT_mirror=LUP_solve_inverse(T,8);
        double invT[8][8]={{0}};
        for(int i=0;i<8;++i){
            for(int j=0;j<8;++j){
                invT[i][j]=invT_mirror[8*i+j];
            }
        }
        delete[] invT_mirror;
        double matFor86[8][6]={{0}};
        for(int i=0;i<2;++i){
            for(int j=0;j<6;++j)
            {
                matFor86[i][j]=mymat[i*6+j];
            }
        }
        for(int j=0;j<6;++j)
        {
            matFor86[2][j]=mymat[1*6+j];
        }
        for(int j=0;j<6;++j)
        {
            matFor86[3][j]=mymat[2*6+j];
        }

        for(int i=0;i<8;++i){
            for(int j=0;j<6;++j){
                for(int k=0;k<8;++k){
                    coefficient[i][j]+=invT[i][k]*matFor86[k][j];
                }
            }
        }
    }else if(mypointnumber==4){
        double T[144]={0};
        T[0]=1,
        T[12]=1,T[13]=mytimeDiff[0],T[14]=mytimeDiff[0]*mytimeDiff[0],T[15]=mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0],
        T[28]=1,
        T[40]=1,T[41]=mytimeDiff[1],T[42]=mytimeDiff[1]*mytimeDiff[1],T[43]=mytimeDiff[1]*mytimeDiff[1]*mytimeDiff[1],
        T[56]=1,T[68]=1,T[69]=mytimeDiff[2],T[70]=mytimeDiff[2]*mytimeDiff[2],T[71]=mytimeDiff[2]*mytimeDiff[2]*mytimeDiff[2];
        T[73]=1,T[93]=1,T[94]=2*mytimeDiff[1],T[95]=3*mytimeDiff[1]*mytimeDiff[1],
        T[97]=1,T[98]=2*mytimeDiff[0], T[99]=3*mytimeDiff[0]*mytimeDiff[0],T[101]=-1,
        T[110]=2,T[111]=6*mytimeDiff[0],T[114]=-2,
        T[125]=1,T[126]=2*mytimeDiff[1],T[127]=3*mytimeDiff[1]*mytimeDiff[1],
        T[129]=-1,T[138]=2,T[139]=6*mytimeDiff[1],T[142]=-2;

        double* invT_mirror=new double[144];
        invT_mirror=LUP_solve_inverse(T,12);
        double invT[12][12]={{0}};
        for(int i=0;i<12;++i){
            for(int j=0;j<12;++j){
                invT[i][j]=invT_mirror[12*i+j];
            }
        }
        delete[] invT_mirror;
        double matFor126[12][6]={{0}};
        for(int i=0;i<6;++i){
            for(int j=0;j<6;++j){
                if(i==0)
                matFor126[i][j]=mymat[0*6+j];
                else if(i==1 || i==2){
                     matFor126[i][j]=mymat[1*6+j];
                }
                else if(i==3 || i==4){
                     matFor126[i][j]=mymat[2*6+j];
                }
                else if(i==5){
                    matFor126[i][j]=mymat[3*6+j];
                }
            }
        }


        for(int i=0;i<12;++i){
            for(int j=0;j<6;++j){
                for(int k=0;k<12;++k){
                    coefficient[i][j]+=invT[i][k]*matFor126[k][j];
                }
            }
        }
    }else if(mypointnumber==5){
        double T[256]={0};
        T[0]=1,T[16]=1,T[17]=mytimeDiff[0],T[18]=mytimeDiff[0]*mytimeDiff[0],T[19]=mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0],
        T[36]=1,T[52]=1,T[53]=mytimeDiff[1],T[54]=mytimeDiff[1]*mytimeDiff[1],T[55]=mytimeDiff[1]*mytimeDiff[1]*mytimeDiff[1],
        T[72]=1,T[88]=1,T[89]=mytimeDiff[2],T[90]=mytimeDiff[2]*mytimeDiff[2],T[91]=mytimeDiff[2]*mytimeDiff[2]*mytimeDiff[2],
        T[108]=1,T[124]=1,T[125]=mytimeDiff[3],T[126]=mytimeDiff[3]*mytimeDiff[3],T[127]=mytimeDiff[3]*mytimeDiff[3]*mytimeDiff[3],
        T[129]=1,T[157]=1,T[158]=2*mytimeDiff[2],T[159]=3*mytimeDiff[2]*mytimeDiff[2],
        T[161]=1,T[162]=2*mytimeDiff[0],T[163]=3*mytimeDiff[0]*mytimeDiff[0],T[165]=-1,
        T[178]=2,T[179]=6*mytimeDiff[0],T[182]=-2,
        T[197]=1,T[198]=2*mytimeDiff[1],T[199]=3*mytimeDiff[1]*mytimeDiff[1],T[201]=-1,
        T[214]=2,T[215]=6*mytimeDiff[1],T[218]=-2,
        T[233]=1,T[234]=2*mytimeDiff[2],T[235]=3*mytimeDiff[2]*mytimeDiff[2],T[237]=-1,
        T[250]=2,T[251]=6*mytimeDiff[2],T[254]=-2;

        double* invT_mirror=new double[256];
        invT_mirror=LUP_solve_inverse(T,16);
        double invT[16][16]={{0}};
        for(int i=0;i<16;++i){
            for(int j=0;j<16;++j){
                invT[i][j]=invT_mirror[16*i+j];
            }
        }
        delete[] invT_mirror;
        double matFor166[16][6]={{0}};
        for(int i=0;i<8;++i){
            for(int j=0;j<6;++j){
                if(i==0)
                matFor166[i][j]=mymat[0*6+j];
                else if(i==1 || i==2){
                     matFor166[i][j]=mymat[1*6+j];
                }
                else if(i==3 || i==4){
                     matFor166[i][j]=mymat[2*6+j];
                }
                else if(i==5 || i==6){
                    matFor166[i][j]=mymat[3*6+j];
                }
                else if(i==7){
                    matFor166[i][j]=mymat[4*6+j];
                }
            }
        }


        for(int i=0;i<16;++i){
            for(int j=0;j<6;++j){
                for(int k=0;k<16;++k){
                    coefficient[i][j]+=invT[i][k]*matFor166[k][j];
                }
            }
        }
    }else if(mypointnumber==6){
        double T[400]={0};
        T[0]=1,T[20]=1,T[21]=mytimeDiff[0],T[22]=mytimeDiff[0]*mytimeDiff[0],T[23]=mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0],
        T[44]=1,T[64]=1,T[65]=mytimeDiff[1],T[66]=mytimeDiff[1]*mytimeDiff[1],T[67]=mytimeDiff[1]*mytimeDiff[1]*mytimeDiff[1],
        T[88]=1,T[108]=1,T[109]=mytimeDiff[2],T[110]=mytimeDiff[2]*mytimeDiff[2],T[111]=mytimeDiff[2]*mytimeDiff[2]*mytimeDiff[2],
        T[132]=1,T[152]=1,T[153]=mytimeDiff[3],T[154]=mytimeDiff[3]*mytimeDiff[3],T[155]=mytimeDiff[3]*mytimeDiff[3]*mytimeDiff[3],
        T[176]=1,T[196]=1,T[197]=mytimeDiff[4],T[198]=mytimeDiff[4]*mytimeDiff[4],T[199]=mytimeDiff[4]*mytimeDiff[4]*mytimeDiff[4],
        T[201]=1,T[237]=1,T[238]=2*mytimeDiff[3],T[239]=3*mytimeDiff[3]*mytimeDiff[3],T[241]=1,T[242]=2*mytimeDiff[0],
        T[243]=3*mytimeDiff[0]*mytimeDiff[0],T[245]=-1,T[262]=2,T[263]=6*mytimeDiff[0],T[266]=-2,T[285]=1,T[286]=2*mytimeDiff[1],
        T[287]=3*mytimeDiff[1]*mytimeDiff[1],T[289]=-1,T[306]=2,T[307]=6*mytimeDiff[1],T[310]=-2,T[329]=1,T[330]=2*mytimeDiff[2],
        T[331]=3*mytimeDiff[2]*mytimeDiff[2],T[333]=-1,T[350]=2,T[351]=6*mytimeDiff[2],T[354]=-2,T[373]=1,T[374]=2*mytimeDiff[3],
        T[375]=3*mytimeDiff[3]*mytimeDiff[3],T[377]=-1,T[394]=2,T[395]=6*mytimeDiff[3],T[398]=-2;

        double* invT_mirror=new double[400];
        invT_mirror=LUP_solve_inverse(T,20);
        double invT[20][20]={{0}};
        for(int i=0;i<20;++i){
            for(int j=0;j<20;++j){
                invT[i][j]=invT_mirror[20*i+j];
            }
        }
        delete[] invT_mirror;
        double matFor206[20][6]={{0}};
        for(int i=0;i<10;++i){
            for(int j=0;j<6;++j){
                if(i==0)
                matFor206[i][j]=mymat[0*6+j];
                else if(i==1 || i==2){
                     matFor206[i][j]=mymat[1*6+j];
                }
                else if(i==3 || i==4){
                     matFor206[i][j]=mymat[2*6+j];
                }
                else if(i==5 || i==6){
                    matFor206[i][j]=mymat[3*6+j];
                }
                else if(i==7 || i==8){
                    matFor206[i][j]=mymat[4*6+j];
                }
                else if(i==9 ){
                    matFor206[i][j]=mymat[5*6+j];
                }
            }
        }


        for(int i=0;i<20;++i){
            for(int j=0;j<6;++j){
                for(int k=0;k<20;++k){
                    coefficient[i][j]+=invT[i][k]*matFor206[k][j];
                }
            }
        }

    }else if(mypointnumber==7){
        double T[576]={0};
        T[0]=1,T[24]=1,T[25]=mytimeDiff[0],T[26]=mytimeDiff[0]*mytimeDiff[0],T[27]=mytimeDiff[0]*mytimeDiff[0]*mytimeDiff[0],
        T[52]=1,T[76]=1,T[77]=mytimeDiff[1],T[78]=mytimeDiff[1]*mytimeDiff[1];T[79]=mytimeDiff[1]*mytimeDiff[1]*mytimeDiff[1],
        T[104]=1,T[128]=1,T[129]=mytimeDiff[2],T[130]=mytimeDiff[2],T[131]=mytimeDiff[2]*mytimeDiff[2]*mytimeDiff[2],
        T[156]=1,T[180]=1,T[181]=mytimeDiff[3],T[182]=mytimeDiff[3]*mytimeDiff[3],T[183]=mytimeDiff[3]*mytimeDiff[3]*mytimeDiff[3],
        T[208]=1,T[232]=1,T[233]=mytimeDiff[4],T[234]=mytimeDiff[4]*mytimeDiff[4],T[235]=mytimeDiff[4]*mytimeDiff[4]*mytimeDiff[4],
        T[260]=1,T[284]=1,T[285]=mytimeDiff[5],T[286]=mytimeDiff[5]*mytimeDiff[5],T[287]=mytimeDiff[5]*mytimeDiff[5]*mytimeDiff[5],
        T[289]=1,T[333]=1,T[334]=2*mytimeDiff[4],T[335]=3*mytimeDiff[4]*mytimeDiff[4],T[337]=1,T[338]=2*mytimeDiff[0],
        T[339]=3*mytimeDiff[0]*mytimeDiff[0],T[341]=-1,T[362]=2,T[363]=6*mytimeDiff[0],T[366]=-2,
        T[389]=1,T[390]=2*mytimeDiff[1],T[391]=3*mytimeDiff[1]*mytimeDiff[1],T[393]=-1,T[414]=2,
        T[415]=6*mytimeDiff[1],T[418]=-2,T[441]=1,T[442]=2*mytimeDiff[2],T[443]=3*mytimeDiff[2]*mytimeDiff[2],
        T[445]=-1,T[466]=2,T[467]=6*mytimeDiff[2],T[470]=-2,T[493]=1,T[494]=2*mytimeDiff[3],T[495]=3*mytimeDiff[3]*mytimeDiff[3],
        T[497]=-1,T[518]=2,T[519]=6*mytimeDiff[3],T[522]=-2,T[545]=1,T[546]=2*mytimeDiff[4],T[547]=3*mytimeDiff[4]*mytimeDiff[4],
        T[549]=-1,T[570]=2,T[571]=6*mytimeDiff[4],T[574]=-2;

        double* invT_mirror=new double[576];
        invT_mirror=LUP_solve_inverse(T,24);
        double invT[24][24]={{0}};
        for(int i=0;i<24;++i){
            for(int j=0;j<24;++j){
                invT[i][j]=invT_mirror[24*i+j];
            }
        }
        delete[] invT_mirror;
        double matFor246[24][6]={{0}};
        for(int i=0;i<12;++i){
            for(int j=0;j<6;++j){
                if(i==0)
                matFor246[i][j]=mymat[0*6+j];
                else if(i==1 || i==2){
                     matFor246[i][j]=mymat[1*6+j];
                }
                else if(i==3 || i==4){
                     matFor246[i][j]=mymat[2*6+j];
                }
                else if(i==5 || i==6){
                    matFor246[i][j]=mymat[3*6+j];
                }
                else if(i==7 || i==8){
                    matFor246[i][j]=mymat[4*6+j];
                }
                else if(i==9 || i==10 ){
                    matFor246[i][j]=mymat[5*6+j];
                }
                else if(i==11){
                    matFor246[i][j]=mymat[6*6+j];
                }
            }
        }


        for(int i=0;i<24;++i){
            for(int j=0;j<6;++j){
                for(int k=0;k<24;++k){
                    coefficient[i][j]+=invT[i][k]*matFor246[k][j];
                }
            }
        }

    }

}

void MyThread::show0(){
    if(mypointnumber==2){  //两个点
        double coefficient[4][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach=mytimeDiff[0]/2000;
        for(int i=0;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[0][j]+coefficient[1][j]*(intervalEach*i)+
                                  coefficient[2][j]*(intervalEach*i)*(intervalEach*i)+
                                  coefficient[3][j]*(intervalEach*i)*(intervalEach*i)*(intervalEach*i);
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
            state.time.push_back(intervalEach*i);
        }
    }
    else if(mypointnumber==3){  //三个点
        double coefficient[8][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/1000;
        for(int i=0;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[0][j]+coefficient[1][j]*(intervalEach1*i)+
                                 coefficient[2][j]*(intervalEach1*i)*(intervalEach1*i)+
                                 coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/1000;
        for(int i=1000;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[4][j]+coefficient[5][j]*(intervalEach2*(i-1000))+
                                  coefficient[6][j]*(intervalEach2*(i-1000))*(intervalEach2*(i-1000))+
                                  coefficient[7][j]*(intervalEach2*(i-1000))*(intervalEach2*(i-1000))*(intervalEach2*(i-1000));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
    }
    else if(mypointnumber==4){
        double coefficient[12][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(18000*sizeof(double));  //3000*6

        double intervalEach1=mytimeDiff[0]/1000;
        for(int i=0;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[0][j]+coefficient[1][j]*(intervalEach1*i)+
                                 coefficient[2][j]*(intervalEach1*i)*(intervalEach1*i)+
                                 coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/1000;
        for(int i=1000;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[4][j]+coefficient[5][j]*(intervalEach2*(i-1000))+
                                  coefficient[6][j]*(intervalEach2*(i-1000))*(intervalEach2*(i-1000))+
                                  coefficient[7][j]*(intervalEach2*(i-1000))*(intervalEach2*(i-1000))*(intervalEach2*(i-1000));
            }
        }
        double intervalEach3=mytimeDiff[2]/1000;
        for(int i=2000;i<3000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[8][j]+coefficient[9][j]*(intervalEach3*(i-2000))+
                                  coefficient[10][j]*(intervalEach3*(i-2000))*(intervalEach3*(i-2000))+
                                  coefficient[11][j]*(intervalEach3*(i-2000))*(intervalEach3*(i-2000))*(intervalEach3*(i-2000));
            }
        }

        for(int i=0;i<3000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
    }
    else if(mypointnumber==5){
        double coefficient[16][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/500;
        for(int i=0;i<500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[0][j]+coefficient[1][j]*(intervalEach1*i)+
                                 coefficient[2][j]*(intervalEach1*i)*(intervalEach1*i)+
                                 coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/500;
        for(int i=500;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[4][j]+coefficient[5][j]*(intervalEach2*(i-500))+
                                  coefficient[6][j]*(intervalEach2*(i-500))*(intervalEach2*(i-500))+
                                  coefficient[7][j]*(intervalEach2*(i-500))*(intervalEach2*(i-500))*(intervalEach2*(i-500));
            }
        }
        double intervalEach3=mytimeDiff[2]/500;
        for(int i=1000;i<1500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[8][j]+coefficient[9][j]*(intervalEach3*(i-1000))+
                                  coefficient[10][j]*(intervalEach3*(i-1000))*(intervalEach3*(i-1000))+
                                  coefficient[11][j]*(intervalEach3*(i-1000))*(intervalEach3*(i-1000))*(intervalEach3*(i-1000));
            }
        }
        double intervalEach4=mytimeDiff[3]/500;
        for(int i=1500;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[12][j]+coefficient[13][j]*(intervalEach4*(i-1500))+
                                  coefficient[14][j]*(intervalEach4*(i-1500))*(intervalEach4*(i-1500))+
                                  coefficient[15][j]*(intervalEach4*(i-1500))*(intervalEach4*(i-1500))*(intervalEach4*(i-1500));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
    }
    else if(mypointnumber==6){
        double coefficient[20][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/400;
        for(int i=0;i<400;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[0][j]+coefficient[1][j]*(intervalEach1*i)+
                                 coefficient[2][j]*(intervalEach1*i)*(intervalEach1*i)+
                                 coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/400;
        for(int i=400;i<800;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[4][j]+coefficient[5][j]*(intervalEach2*(i-400))+
                                  coefficient[6][j]*(intervalEach2*(i-400))*(intervalEach2*(i-400))+
                                  coefficient[7][j]*(intervalEach2*(i-400))*(intervalEach2*(i-400))*(intervalEach2*(i-400));
            }
        }
        double intervalEach3=mytimeDiff[2]/400;
        for(int i=800;i<1200;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[8][j]+coefficient[9][j]*(intervalEach3*(i-800))+
                                  coefficient[10][j]*(intervalEach3*(i-800))*(intervalEach3*(i-800))+
                                  coefficient[11][j]*(intervalEach3*(i-800))*(intervalEach3*(i-800))*(intervalEach3*(i-800));
            }
        }
        double intervalEach4=mytimeDiff[3]/400;
        for(int i=1200;i<1600;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[12][j]+coefficient[13][j]*(intervalEach4*(i-1200))+
                                  coefficient[14][j]*(intervalEach4*(i-1200))*(intervalEach4*(i-1200))+
                                  coefficient[15][j]*(intervalEach4*(i-1200))*(intervalEach4*(i-1200))*(intervalEach4*(i-1200));
            }
        }

        double intervalEach5=mytimeDiff[4]/400;
        for(int i=1600;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[16][j]+coefficient[17][j]*(intervalEach5*(i-1600))+
                                  coefficient[18][j]*(intervalEach5*(i-1600))*(intervalEach5*(i-1600))+
                                  coefficient[19][j]*(intervalEach5*(i-1600))*(intervalEach5*(i-1600))*(intervalEach5*(i-1600));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+intervalEach5*i);
        }
    }
    else if(mypointnumber==7){
        double coefficient[24][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(18000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/500;
        for(int i=0;i<500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[0][j]+coefficient[1][j]*(intervalEach1*i)+
                                 coefficient[2][j]*(intervalEach1*i)*(intervalEach1*i)+
                                 coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/500;
        for(int i=500;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[4][j]+coefficient[5][j]*(intervalEach2*(i-500))+
                                  coefficient[6][j]*(intervalEach2*(i-500))*(intervalEach2*(i-500))+
                                  coefficient[7][j]*(intervalEach2*(i-500))*(intervalEach2*(i-500))*(intervalEach2*(i-500));
            }
        }
        double intervalEach3=mytimeDiff[2]/500;
        for(int i=1000;i<1500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[8][j]+coefficient[9][j]*(intervalEach3*(i-1000))+
                                  coefficient[10][j]*(intervalEach3*(i-1000))*(intervalEach3*(i-1000))+
                                  coefficient[11][j]*(intervalEach3*(i-1000))*(intervalEach3*(i-1000))*(intervalEach3*(i-1000));
            }
        }
        double intervalEach4=mytimeDiff[3]/500;
        for(int i=1500;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[12][j]+coefficient[13][j]*(intervalEach4*(i-1500))+
                                  coefficient[14][j]*(intervalEach4*(i-1500))*(intervalEach4*(i-1500))+
                                  coefficient[15][j]*(intervalEach4*(i-1500))*(intervalEach4*(i-1500))*(intervalEach4*(i-1500));
            }
        }
        double intervalEach5=mytimeDiff[4]/500;
        for(int i=2000;i<2500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[16][j]+coefficient[17][j]*(intervalEach5*(i-2000))+
                                  coefficient[18][j]*(intervalEach5*(i-2000))*(intervalEach5*(i-2000))+
                                  coefficient[19][j]*(intervalEach5*(i-2000))*(intervalEach5*(i-2000))*(intervalEach5*(i-2000));
            }
        }
        double intervalEach6=mytimeDiff[5]/500;
        for(int i=2500;i<3000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[20][j]+coefficient[21][j]*(intervalEach6*(i-2500))+
                                  coefficient[22][j]*(intervalEach6*(i-2500))*(intervalEach6*(i-2500))+
                                  coefficient[23][j]*(intervalEach6*(i-2500))*(intervalEach6*(i-2500))*(intervalEach6*(i-2500));
            }
        }

        for(int i=0;i<3000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+intervalEach5*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+mytimeDiff[4]+intervalEach6*i);
        }
    }

    std::ofstream out_txt_file1;
    //写入状态1
    out_txt_file1.open("coordinate-X", std::ios::out | std::ios::trunc);
    out_txt_file1 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateX.size(); i++)
    {
        out_txt_file1 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateX[i] << std::endl;
    }
    out_txt_file1.close();


    std::ofstream out_txt_file2;
    //写入状态2
    out_txt_file2.open("coordinate-Y", std::ios::out | std::ios::trunc);
    out_txt_file2 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateY.size(); i++)
    {
        out_txt_file2 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateY[i] << std::endl;
    }
    out_txt_file2.close();

    std::ofstream out_txt_file3;
    //写入状态3
    out_txt_file3.open("coordinate-Z", std::ios::out | std::ios::trunc);
    out_txt_file3 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateZ.size(); i++)
    {
       out_txt_file3 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateZ[i] << std::endl;
    }
    out_txt_file3.close();


    std::ofstream out_txt_file4;
    //写入状态4
    out_txt_file4.open("Roll", std::ios::out | std::ios::trunc);
    out_txt_file4 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateR.size(); i++)
    {
        out_txt_file4 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateR[i] << std::endl;
    }
    out_txt_file4.close();

    std::ofstream out_txt_file5;
    //写入状态5
    out_txt_file5.open("Pitch", std::ios::out | std::ios::trunc);
    out_txt_file5 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateP.size(); i++)
    {
        out_txt_file5 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateP[i] << std::endl;
    }
    out_txt_file5.close();

    std::ofstream out_txt_file6;
    //写入状态6
    out_txt_file6.open("Yaw", std::ios::out | std::ios::trunc);
    out_txt_file6 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateGamma.size(); i++)
    {
       out_txt_file6 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateGamma[i] << std::endl;
    }
    out_txt_file6.close();
    state.StateX.clear();
    state.StateY.clear();
    state.StateZ.clear();
    state.StateR.clear();
    state.StateP.clear();
    state.StateGamma.clear();
    state.time.clear();
    FILE* pipe = popen("gnuplot", "w"); //具体改为gnuplot的安装位置
    if (pipe == NULL)
    {
        exit(-1);
    }
    fprintf(pipe, "set terminal wxt size 1500, 800\n");
    fprintf(pipe, "set multiplot layout 3,2\n");
    fprintf(pipe, "plot  'coordinate-X' w l  \n");
    fprintf(pipe, "plot  'coordinate-Y' w l  \n");
    fprintf(pipe, "plot  'coordinate-Z' w l  \n");
    fprintf(pipe, "plot  'Roll' w l  \n");
    fprintf(pipe, "plot  'Pitch' w l  \n");
    fprintf(pipe, "plot  'Yaw' w l  \n");
    fprintf(pipe, "pause mouse\n");
    pclose(pipe);

    delete this;
}

void MyThread::show1(){
    if(mypointnumber==2){  //两个点
        double coefficient[4][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach=mytimeDiff[0]/2000;
        for(int i=0;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[1][j]+2*coefficient[2][j]*(intervalEach*i)+
                                  3*coefficient[3][j]*(intervalEach*i)*(intervalEach*i);
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
            state.time.push_back(intervalEach*i);
        }
    }
    else if(mypointnumber==3){  //三个点
        double coefficient[8][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/1000;
        for(int i=0;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[1][j]+2*coefficient[2][j]*(intervalEach1*i)+
                                 3*coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/1000;
        for(int i=1000;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[5][j]+2*coefficient[6][j]*(intervalEach2*(i-1000))+
                                  3*coefficient[7][j]*(intervalEach2*(i-1000))*(intervalEach2*(i-1000));
            }
        }
        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
    }
    else if(mypointnumber==4){
        double coefficient[12][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(18000*sizeof(double));  //3000*6

        double intervalEach1=mytimeDiff[0]/1000;
        for(int i=0;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[1][j]+2*coefficient[2][j]*(intervalEach1*i)+
                                 3*coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/1000;
        for(int i=1000;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[5][j]+2*coefficient[6][j]*(intervalEach2*(i-1000))+
                                  3*coefficient[7][j]*(intervalEach2*(i-1000))*(intervalEach2*(i-1000));
            }
        }
        double intervalEach3=mytimeDiff[2]/1000;
        for(int i=2000;i<3000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[9][j]+2*coefficient[10][j]*(intervalEach3*(i-2000))+
                                 3*coefficient[11][j]*(intervalEach3*(i-2000))*(intervalEach3*(i-2000));
            }
        }

        for(int i=0;i<3000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
    }
    else if(mypointnumber==5){
        double coefficient[16][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/500;
        for(int i=0;i<500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[1][j]+2*coefficient[2][j]*(intervalEach1*i)+
                                 3*coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/500;
        for(int i=500;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[5][j]+2*coefficient[6][j]*(intervalEach2*(i-500))+
                                  3*coefficient[7][j]*(intervalEach2*(i-500))*(intervalEach2*(i-500));
            }
        }
        double intervalEach3=mytimeDiff[2]/500;
        for(int i=1000;i<1500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[9][j]+2*coefficient[10][j]*(intervalEach3*(i-1000))+
                                  3*coefficient[11][j]*(intervalEach3*(i-1000))*(intervalEach3*(i-1000));
            }
        }
        double intervalEach4=mytimeDiff[3]/500;
        for(int i=1500;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[13][j]+2*coefficient[14][j]*(intervalEach4*(i-1500))+
                                  3*coefficient[15][j]*(intervalEach4*(i-1500))*(intervalEach4*(i-1500));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
    }
    else if(mypointnumber==6){
        double coefficient[20][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/400;
        for(int i=0;i<400;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[1][j]+2*coefficient[2][j]*(intervalEach1*i)+
                                 3*coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/400;
        for(int i=400;i<800;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[5][j]+2*coefficient[6][j]*(intervalEach2*(i-400))+
                                  3*coefficient[7][j]*(intervalEach2*(i-400))*(intervalEach2*(i-400));
            }
        }
        double intervalEach3=mytimeDiff[2]/400;
        for(int i=800;i<1200;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[9][j]+2*coefficient[10][j]*(intervalEach3*(i-800))+
                                  3*coefficient[11][j]*(intervalEach3*(i-800))*(intervalEach3*(i-800));
            }
        }
        double intervalEach4=mytimeDiff[3]/400;
        for(int i=1200;i<1600;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[13][j]+2*coefficient[14][j]*(intervalEach4*(i-1200))+
                                  3*coefficient[15][j]*(intervalEach4*(i-1200))*(intervalEach4*(i-1200));
            }
        }

        double intervalEach5=mytimeDiff[4]/400;
        for(int i=1600;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[17][j]+2*coefficient[18][j]*(intervalEach5*(i-1600))+
                                  3*coefficient[19][j]*(intervalEach5*(i-1600))*(intervalEach5*(i-1600));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+intervalEach5*i);
        }
    }
    else if(mypointnumber==7){
        double coefficient[24][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(18000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/500;
        for(int i=0;i<500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[1][j]+2*coefficient[2][j]*(intervalEach1*i)+
                                 3*coefficient[3][j]*(intervalEach1*i)*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/500;
        for(int i=500;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[5][j]+2*coefficient[6][j]*(intervalEach2*(i-500))+
                                  3*coefficient[7][j]*(intervalEach2*(i-500))*(intervalEach2*(i-500));
            }
        }
        double intervalEach3=mytimeDiff[2]/500;
        for(int i=1000;i<1500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[9][j]+2*coefficient[10][j]*(intervalEach3*(i-1000))+
                                  3*coefficient[11][j]*(intervalEach3*(i-1000))*(intervalEach3*(i-1000));
            }
        }
        double intervalEach4=mytimeDiff[3]/500;
        for(int i=1500;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[13][j]+2*coefficient[14][j]*(intervalEach4*(i-1500))+
                                  3*coefficient[15][j]*(intervalEach4*(i-1500))*(intervalEach4*(i-1500));
            }
        }
        double intervalEach5=mytimeDiff[4]/500;
        for(int i=2000;i<2500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[17][j]+2*coefficient[18][j]*(intervalEach5*(i-2000))+
                                  3*coefficient[19][j]*(intervalEach5*(i-2000))*(intervalEach5*(i-2000));
            }
        }
        double intervalEach6=mytimeDiff[5]/500;
        for(int i=2500;i<3000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=coefficient[21][j]+2*coefficient[22][j]*(intervalEach6*(i-2500))+
                                  3*coefficient[23][j]*(intervalEach6*(i-2500))*(intervalEach6*(i-2500));
            }
        }

        for(int i=0;i<3000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+intervalEach5*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+mytimeDiff[4]+intervalEach6*i);
        }
    }
    std::ofstream out_txt_file1;
    //写入状态1
    out_txt_file1.open("coordinate-X-velocity", std::ios::out | std::ios::trunc);
    out_txt_file1 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateX.size(); i++)
    {
        out_txt_file1 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateX[i] << std::endl;
    }
    out_txt_file1.close();


     std::ofstream out_txt_file2;
     //写入状态2
     out_txt_file2.open("coordinate-Y-velocity", std::ios::out | std::ios::trunc);
     out_txt_file2 << "#" << "X" << " " << " " << "Y" << std::endl;
     for (unsigned int i = 0; i < state.StateY.size(); i++)
     {
         out_txt_file2 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateY[i] << std::endl;
     }
     out_txt_file2.close();

     std::ofstream out_txt_file3;
     //写入状态3
     out_txt_file3.open("coordinate-Z-velocity", std::ios::out | std::ios::trunc);
     out_txt_file3 << "#" << "X" << " " << " " << "Y" << std::endl;
     for (unsigned int i = 0; i < state.StateZ.size(); i++)
     {
         out_txt_file3 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateZ[i] << std::endl;
     }
     out_txt_file3.close();


      std::ofstream out_txt_file4;
      //写入状态4
      out_txt_file4.open("Roll-velocity", std::ios::out | std::ios::trunc);
      out_txt_file4 << "#" << "X" << " " << " " << "Y" << std::endl;
      for (unsigned int i = 0; i < state.StateR.size(); i++)
      {
          out_txt_file4 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateR[i] << std::endl;
      }
      out_txt_file4.close();

      std::ofstream out_txt_file5;
      //写入状态5
      out_txt_file5.open("Pitch-velocity", std::ios::out | std::ios::trunc);
      out_txt_file5 << "#" << "X" << " " << " " << "Y" << std::endl;
      for (unsigned int i = 0; i < state.StateP.size(); i++)
      {
          out_txt_file5 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateP[i] << std::endl;
      }
      out_txt_file5.close();

      std::ofstream out_txt_file6;
      //写入状态6
      out_txt_file6.open("Yaw-velocity", std::ios::out | std::ios::trunc);
      out_txt_file6 << "#" << "X" << " " << " " << "Y" << std::endl;
      for (unsigned int i = 0; i < state.StateGamma.size(); i++)
      {
          out_txt_file6 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateGamma[i] << std::endl;
      }
      out_txt_file6.close();
    state.StateX.clear();
    state.StateY.clear();
    state.StateZ.clear();
    state.StateR.clear();
    state.StateP.clear();
    state.StateGamma.clear();
    state.time.clear();
    FILE* pipe = popen("gnuplot", "w"); //具体改为gnuplot的安装位置
    if (pipe == NULL)
    {
        exit(-1);
    }
    fprintf(pipe, "set terminal wxt size 1500, 800\n");
    fprintf(pipe, "set multiplot layout 3,2\n");
    fprintf(pipe, "plot  'coordinate-X-velocity' w l  \n");
    fprintf(pipe, "plot  'coordinate-Y-velocity' w l  \n");
    fprintf(pipe, "plot  'coordinate-Z-velocity' w l  \n");
    fprintf(pipe, "plot  'Roll-velocity' w l  \n");
    fprintf(pipe, "plot  'Pitch-velocity' w l  \n");
    fprintf(pipe, "plot  'Yaw-velocity' w l  \n");
    fprintf(pipe, "pause mouse\n");
    pclose(pipe);

    delete this;
}

void MyThread::show2(){
    if(mypointnumber==2){  //两个点
        double coefficient[4][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach=mytimeDiff[0]/2000;
        for(int i=0;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[2][j]+6*coefficient[3][j]*(intervalEach*i);
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
            state.time.push_back(intervalEach*i);
        }

    }
    else if(mypointnumber==3){  //三个点
        double coefficient[8][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/1000;
        for(int i=0;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[2][j]+6*coefficient[3][j]*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/1000;
        for(int i=1000;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[6][j]+6*coefficient[7][j]*(intervalEach2*(i-1000));
            }
        }
        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
    }
    else if(mypointnumber==4){
        double coefficient[12][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(18000*sizeof(double));  //3000*6

        double intervalEach1=mytimeDiff[0]/1000;
        for(int i=0;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[2][j]+6*coefficient[3][j]*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/1000;
        for(int i=1000;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[6][j]+6*coefficient[7][j]*(intervalEach2*(i-1000));
            }
        }
        double intervalEach3=mytimeDiff[2]/1000;
        for(int i=2000;i<3000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[10][j]+6*coefficient[11][j]*(intervalEach3*(i-2000));
            }
        }

        for(int i=0;i<3000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<1000;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
    }
    else if(mypointnumber==5){
        double coefficient[16][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/500;
        for(int i=0;i<500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[2][j]+6*coefficient[3][j]*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/500;
        for(int i=500;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[6][j]+6*coefficient[7][j]*(intervalEach2*(i-500));
            }
        }
        double intervalEach3=mytimeDiff[2]/500;
        for(int i=1000;i<1500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[10][j]+6*coefficient[11][j]*(intervalEach3*(i-1000));
            }
        }
        double intervalEach4=mytimeDiff[3]/500;
        for(int i=1500;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[14][j]+6*coefficient[15][j]*(intervalEach4*(i-1500));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
    }
    else if(mypointnumber==6){
        double coefficient[20][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(12000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/400;
        for(int i=0;i<400;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[2][j]+6*coefficient[3][j]*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/400;
        for(int i=400;i<800;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[6][j]+6*coefficient[7][j]*(intervalEach2*(i-400));
            }
        }
        double intervalEach3=mytimeDiff[2]/400;
        for(int i=800;i<1200;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[10][j]+6*coefficient[11][j]*(intervalEach3*(i-800));
            }
        }
        double intervalEach4=mytimeDiff[3]/400;
        for(int i=1200;i<1600;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[14][j]+6*coefficient[15][j]*(intervalEach4*(i-1200));
            }
        }

        double intervalEach5=mytimeDiff[4]/400;
        for(int i=1600;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[18][j]+6*coefficient[19][j]*(intervalEach5*(i-1600));
            }
        }

        for(int i=0;i<2000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
        for(int i=0;i<400;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+intervalEach5*i);
        }
    }
    else if(mypointnumber==7){
        double coefficient[24][100]={{0}};
        calcoefficient(coefficient);
        inter=(double*)malloc(18000*sizeof(double));  //2000*6

        double intervalEach1=mytimeDiff[0]/500;
        for(int i=0;i<500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[2][j]+6*coefficient[3][j]*(intervalEach1*i);
            }
        }
        double intervalEach2=mytimeDiff[1]/500;
        for(int i=500;i<1000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[6][j]+6*coefficient[7][j]*(intervalEach2*(i-500));
            }
        }
        double intervalEach3=mytimeDiff[2]/500;
        for(int i=1000;i<1500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[10][j]+6*coefficient[11][j]*(intervalEach3*(i-1000));
            }
        }
        double intervalEach4=mytimeDiff[3]/500;
        for(int i=1500;i<2000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[14][j]+6*coefficient[15][j]*(intervalEach4*(i-1500));
            }
        }
        double intervalEach5=mytimeDiff[4]/500;
        for(int i=2000;i<2500;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[18][j]+6*coefficient[19][j]*(intervalEach5*(i-2000));
            }
        }
        double intervalEach6=mytimeDiff[5]/500;
        for(int i=2500;i<3000;++i){
            for(int j=0;j<6;++j){
                       inter[i*6+j]=2*coefficient[22][j]+6*coefficient[23][j]*(intervalEach6*(i-2500));
            }
        }

        for(int i=0;i<3000;++i){
            state.StateX.push_back(inter[i*6+0]);
            state.StateY.push_back(inter[i*6+1]);
            state.StateZ.push_back(inter[i*6+2]);
            state.StateR.push_back(inter[i*6+3]);
            state.StateP.push_back(inter[i*6+4]);
            state.StateGamma.push_back(inter[i*6+5]);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(intervalEach1*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+intervalEach2*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+intervalEach3*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+intervalEach4*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+intervalEach5*i);
        }
        for(int i=0;i<500;++i){
            state.time.push_back(mytimeDiff[0]+mytimeDiff[1]+mytimeDiff[2]+mytimeDiff[3]+mytimeDiff[4]+intervalEach6*i);
        }
    }

    std::ofstream out_txt_file1;
    //写入状态1
    out_txt_file1.open("coordinate-X-accelerate", std::ios::out | std::ios::trunc);
    out_txt_file1 << "#" << "X" << " " << " " << "Y" << std::endl;
    for (unsigned int i = 0; i < state.StateX.size(); i++)
    {
        out_txt_file1 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateX[i] << std::endl;
    }
    out_txt_file1.close();


     std::ofstream out_txt_file2;
     //写入状态2
     out_txt_file2.open("coordinate-Y-accelerate", std::ios::out | std::ios::trunc);
     out_txt_file2 << "#" << "X" << " " << " " << "Y" << std::endl;
     for (unsigned int i = 0; i < state.StateY.size(); i++)
     {
         out_txt_file2 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateY[i] << std::endl;
     }
     out_txt_file2.close();

     std::ofstream out_txt_file3;
     //写入状态3
     out_txt_file3.open("coordinate-Z-accelerate", std::ios::out | std::ios::trunc);
     out_txt_file3 << "#" << "X" << " " << " " << "Y" << std::endl;
     for (unsigned int i = 0; i < state.StateZ.size(); i++)
     {
         out_txt_file3 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateZ[i] << std::endl;
     }
     out_txt_file3.close();


      std::ofstream out_txt_file4;
      //写入状态4
      out_txt_file4.open("Roll-accelerate", std::ios::out | std::ios::trunc);
      out_txt_file4 << "#" << "X" << " " << " " << "Y" << std::endl;
      for (unsigned int i = 0; i < state.StateR.size(); i++)
      {
          out_txt_file4 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateR[i] << std::endl;
      }
      out_txt_file4.close();

      std::ofstream out_txt_file5;
      //写入状态5
      out_txt_file5.open("Pitch-accelerate", std::ios::out | std::ios::trunc);
      out_txt_file5 << "#" << "X" << " " << " " << "Y" << std::endl;
      for (unsigned int i = 0; i < state.StateP.size(); i++)
      {
          out_txt_file5 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateP[i] << std::endl;
      }
      out_txt_file5.close();

      std::ofstream out_txt_file6;
      //写入状态6
      out_txt_file6.open("Yaw-accelerate", std::ios::out | std::ios::trunc);
      out_txt_file6 << "#" << "X" << " " << " " << "Y" << std::endl;
      for (unsigned int i = 0; i < state.StateGamma.size(); i++)
      {
          out_txt_file6 << "  " << std::setprecision(4) << state.time[i] << " " << std::setprecision(4) << state.StateGamma[i] << std::endl;
      }
      out_txt_file6.close();

    state.StateX.clear();
    state.StateY.clear();
    state.StateZ.clear();
    state.StateR.clear();
    state.StateP.clear();
    state.StateGamma.clear();
    state.time.clear();
    FILE* pipe = popen("gnuplot", "w"); //具体改为gnuplot的安装位置
    if (pipe == NULL)
    {
        exit(-1);
    }
    fprintf(pipe, "set terminal wxt size 1500, 800\n");
    fprintf(pipe, "set multiplot layout 3,2\n");
    fprintf(pipe, "plot  'coordinate-X-accelerate' w l  \n");
    fprintf(pipe, "plot  'coordinate-Y-accelerate' w l  \n");
    fprintf(pipe, "plot  'coordinate-Z-accelerate' w l  \n");
    fprintf(pipe, "plot  'Roll-accelerate' w l  \n");
    fprintf(pipe, "plot  'Pitch-accelerate' w l  \n");
    fprintf(pipe, "plot  'Yaw-accelerate' w l  \n");
    fprintf(pipe, "pause mouse\n");
    pclose(pipe);
    delete this;
}

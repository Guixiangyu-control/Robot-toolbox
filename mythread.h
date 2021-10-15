#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <iostream>
#include <QThread>
#include <fstream>
#include <QFile>
#include <QApplication>
#include <cstdlib>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();
    void calcoefficient(double coefficient[][100]);
    //线程处理函数
    void show0();
    void show1();
    void show2();
    void setmat(double *mat){
        this->mymat=mat;
    }

    void setmytimeDiff(double* timeDiff){
        this->mytimeDiff=timeDiff;
    }

    void setmypointnumber(int pointnumber){
        this->mypointnumber=pointnumber;
    }

private:
    double* mymat;
    double* mytimeDiff;
    int mypointnumber;
    double* inter;
};

#endif // MYTHREAD_H

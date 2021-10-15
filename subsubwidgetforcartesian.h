#ifndef SUBSUBWIDGETFORCARTESIAN_H
#define SUBSUBWIDGETFORCARTESIAN_H


#include <QWidget>
#include "QDebug"
#include <QLabel>
#include <vector>
#include <QString>
#include "mythread.h"
#include <cstdlib>
#include <malloc.h>
#include <QThread>
#include <QMessageBox>

namespace Ui {
class subsubwidgetforcartesian;
}

class subsubwidgetforcartesian : public QWidget
{
    Q_OBJECT

public:
    explicit subsubwidgetforcartesian(QWidget *parent = nullptr);
    subsubwidgetforcartesian(int howmanypoint , QWidget *parent=nullptr);
    ~subsubwidgetforcartesian();

signals:
    void clicked();
private slots:
    void start();

private:
    Ui::subsubwidgetforcartesian *ui;
    double* point;
    double* timeInterval;
    int pointNumber;
    MyThread* myT;
    QThread* thread;
};


#endif // SUBSUBWIDGETFORCARTESIAN_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QAction>
#include <QMouseEvent>
#include "pinv.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    STLView::init();
    changeQSS2();

    ui->setupUi(this);
    setWindowTitle(tr("robot Project"));


    connect(ui->action_2,&QAction::triggered,this,&MainWindow::open1);
    connect(ui->action_4,&QAction::triggered,this,&MainWindow::open2);
    connect(ui->action,&QAction::triggered,this,&MainWindow::open3);
    connect(ui->action_6,&QAction::triggered,this,&MainWindow::exit);

    connect(set.pushButton1,&QPushButton::clicked,this,&MainWindow::changeQSS1);
    connect(set.pushButton2,&QPushButton::clicked,this,&MainWindow::changeQSS2);
    sub1.resize(1000,680);


    ui->labelFirst->installEventFilter(this);
    ui->labelSecond->installEventFilter(this);
    ui->labelThird->installEventFilter(this);
    ui->labelFourth->installEventFilter(this);
    ui->labelFifth->installEventFilter(this);
}

void MainWindow::changeQSS1(){
    QFile file1("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/mainChinese.qss");
    file1.open(QFile::ReadOnly);
    QTextStream filetext1(&file1);
    QString stylesheet1 = filetext1.readAll();
    this->setStyleSheet(stylesheet1);
    file1.close();

    QFile file2("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/settingChinese.qss");
    file2.open(QFile::ReadOnly);
    QTextStream filetext2(&file2);
    QString stylesheet2 = filetext2.readAll();
    set.setStyleSheet(stylesheet2);
    file2.close();

}

void MainWindow::changeQSS2(){
    QFile file1("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/main.qss");
    file1.open(QFile::ReadOnly);
    QTextStream filetext1(&file1);
    QString stylesheet1 = filetext1.readAll();
    this->setStyleSheet(stylesheet1);
    file1.close();

    QFile file2("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/setting.qss");
    file2.open(QFile::ReadOnly);
    QTextStream filetext2(&file2);
    QString stylesheet2 = filetext2.readAll();
    set.setStyleSheet(stylesheet2);
    file2.close();

    QFile file3("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/subwidgetforik.qss");
    file3.open(QFile::ReadOnly);
    QTextStream filetext3(&file3);
    QString stylesheet3 = filetext3.readAll();
    sub1.setStyleSheet(stylesheet3);
    file3.close();

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    int openwhich=0;
    if(obj==ui->labelSecond)
    {
        openwhich=1;
    }
    else if(obj==ui->labelThird)
    {
        openwhich=2;
    }
    else if(obj==ui->labelFirst)
    {
        openwhich=3;
    }
    else if(obj==ui->labelFourth)
    {
        openwhich=4;
    }
    else if(obj==ui->labelFifth)
    {
        openwhich=5;
    }
    if(openwhich!=0)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
           QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

           if(mouseEvent->button()==Qt::LeftButton)
           {
               if(openwhich==1)
               {
                   open1();
               }
               else if(openwhich==2)
               {
                   open2();
               }
               else if(openwhich==3)
               {
                   open3();
               }
               else if(openwhich==4)
               {
                   open4();
               }
               else if(openwhich==5)
               {
                   open5();
               }
               return true;
           }
           else
           {
               return false;
           }
         }
         else
         {
            return false;
         }
    }
    else
    {
        return QMainWindow::eventFilter(obj,event);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::open1()
{
    sub1.show();
}

void MainWindow::open2()
{
    bool bRet=false;

    int howManyPoint=QInputDialog::getInt(this,tr("Message1"), tr("How many number?(No more than 7) and please click begin plan again after showing the graph"),2,2,7,1,&bRet);

    if(bRet){
       //  subsubwidgetforcartesian* subone1=new subsubwidgetforcartesian(nullptr,howManyPoint);
        subone1=new subsubwidgetforcartesian(howManyPoint);
        subone1->show();
     }
}

void MainWindow::open3()
{
    sub3.show();
}

void MainWindow::open4()
{
    QString inf(" Author:Guixiangyu-control\n\n If you need use Catesian plan tool ,\n First , you should rebegin planning \n after showing a certain graph , Second ,\n you must fill all the empty space you see.\n\n Whether you like this or not, please\n clike star on github");
    char*  ch;
    QByteArray ba = inf.toLatin1(); // must
    ch=ba.data();
    QMessageBox::about(this, tr("you should know"), tr(ch));
}

void MainWindow::open5()
{
    set.show();
}


void MainWindow::exit()
{
    QApplication::exit();
}

#include "subsubwidgetforcartesian.h"
#include "ui_subsubwidgetforcartesian.h"

subsubwidgetforcartesian::subsubwidgetforcartesian(QWidget *parent):
    QWidget(parent),
    ui(new Ui::subsubwidgetforcartesian)
{
    ui->setupUi(this);
}

subsubwidgetforcartesian::subsubwidgetforcartesian(int howManyPoint, QWidget *parent):
    QWidget(parent),
    ui(new Ui::subsubwidgetforcartesian)
{
    ui->setupUi(this);
    setWindowTitle(tr("Please input point information table"));
    pointNumber=howManyPoint;

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(8);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QLabel *label = new QLabel("");
    label->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/point.jpg").scaled(100,50));
    ui->tableWidget->setCellWidget(0,0,label);


    for(int i=7;i>pointNumber;--i){
        for(int j=1;j<=7;++j){
            QLabel *label1 = new QLabel("");
            label1->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/prohibit.jpg").scaled(100,50));
            ui->tableWidget->setCellWidget(i,j,label1);
        }
    }

    QLabel *label2 = new QLabel("");
    label2->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/Interval.jpg").scaled(100,50));
    ui->tableWidget->setCellWidget(0,7,label2);

    QLabel *label3 = new QLabel("");
    label3->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/prohibit.jpg").scaled(100,50));
    ui->tableWidget->setCellWidget(1,7,label3);

    ui->tableWidget->setItem(1,0,new QTableWidgetItem("point1"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("point2"));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem("point3"));
    ui->tableWidget->setItem(4,0,new QTableWidgetItem("point4"));
    ui->tableWidget->setItem(5,0,new QTableWidgetItem("point5"));
    ui->tableWidget->setItem(6,0,new QTableWidgetItem("point6"));
    ui->tableWidget->setItem(7,0,new QTableWidgetItem("point7"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("x"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("y"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("z"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("r"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem("p"));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem("y"));

   connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(start()));
}


subsubwidgetforcartesian::~subsubwidgetforcartesian()
{
    delete ui;
}

void subsubwidgetforcartesian::start(){
    point=(double*)malloc(sizeof(double)*pointNumber*6);
    for(int i=0;i<pointNumber;++i){
        for(int j=0;j<6;++j){
            point[i*6+j]=(ui->tableWidget->item(i+1,j+1)->text()).toDouble();
        }
    }

    timeInterval=(double*)malloc(sizeof(double)*(pointNumber-1)*6);
    for(int i=0;i<pointNumber-1;++i){
         timeInterval[i]=(ui->tableWidget->item(i+2,7)->text()).toDouble();
    }

    //不能指定父对象
    myT =new MyThread;
    thread =new QThread(this);
    //把自定义的线程加入到子线程中
    myT->moveToThread(thread);
    myT->setmat(point);
    myT->setmytimeDiff(timeInterval);
    myT->setmypointnumber(pointNumber);
    thread->start();

    connect(ui->pushButton_2,&QPushButton::clicked,myT,&MyThread::show0);
    connect(ui->pushButton_3,&QPushButton::clicked,myT,&MyThread::show1);
    connect(ui->pushButton_4,&QPushButton::clicked,myT,&MyThread::show2);
}

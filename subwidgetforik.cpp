#include "subwidgetforik.h"
#include "ui_subwidgetforik.h"


#include <QIcon>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include "pinv.h"

#define ZERO_THRESH 0.00000001
#define SIGN(x) ( ( (x) > 0 ) - ( (x) < 0 ) )
#define IKPI  ((IkReal)3.14159265358979)
#define d1  0.089159
#define a2 -0.42500
#define a3 -0.39225
#define d4  0.10915
#define d5  0.09465
#define d6  0.0823
#define PI 3.1415926
typedef double IkReal;
const IkReal ARC_TO_DEG = 57.29577951308238;    //弧度转角度
const IkReal DEG_TO_ARC = 0.0174532925199433;       //角度转弧度

using namespace std;

subwidgetforIk::subwidgetforIk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subwidgetforIk)
{
    ui->setupUi(this);
    setWindowTitle(tr("inverse kinematics solver"));
    ui->tabWidget->clear();
    ui->tabWidget->addTab(ui->tab,tr("UR5 analytic solve(Default)"));
    ui->tabWidget->addTab(ui->tab_6,tr("UR5 analytic solve(Improved)"));
    ui->tabWidget->addTab(ui->tab_2,tr("Numerical"));
    ui->tabWidget->addTab(ui->tab_3,tr("ANN"));
    ui->tabWidget->setMovable(true);


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(9);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QLabel *label = new QLabel("");
    label->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget->setCellWidget(0,0,label);
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Solution1"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Solution2"));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem("Solution3"));
    ui->tableWidget->setItem(4,0,new QTableWidgetItem("Solution4"));
    ui->tableWidget->setItem(5,0,new QTableWidgetItem("Solution5"));
    ui->tableWidget->setItem(6,0,new QTableWidgetItem("Solution6"));
    ui->tableWidget->setItem(7,0,new QTableWidgetItem("Solution7"));
    ui->tableWidget->setItem(8,0,new QTableWidgetItem("Solution8"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem("Theta6"));


    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setColumnCount(7);
    ui->tableWidget_2->setRowCount(9);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setVisible(false);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QLabel *label1 = new QLabel("");
    label1->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget_2->setCellWidget(0,0,label1);
    ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("Solution1"));
    ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("Solution2"));
    ui->tableWidget_2->setItem(3,0,new QTableWidgetItem("Solution3"));
    ui->tableWidget_2->setItem(4,0,new QTableWidgetItem("Solution4"));
    ui->tableWidget_2->setItem(5,0,new QTableWidgetItem("Solution5"));
    ui->tableWidget_2->setItem(6,0,new QTableWidgetItem("Solution6"));
    ui->tableWidget_2->setItem(7,0,new QTableWidgetItem("Solution7"));
    ui->tableWidget_2->setItem(8,0,new QTableWidgetItem("Solution8"));
    ui->tableWidget_2->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget_2->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget_2->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget_2->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget_2->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget_2->setItem(0,6,new QTableWidgetItem("Theta6"));


    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setColumnCount(7);
    ui->tableWidget_3->setRowCount(2);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setVisible(false);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QLabel *label2 = new QLabel("");
    label2->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget_3->setCellWidget(0,0,label2);
    ui->tableWidget_3->setItem(1,0,new QTableWidgetItem("Solution"));
    ui->tableWidget_3->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget_3->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget_3->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget_3->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget_3->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget_3->setItem(0,6,new QTableWidgetItem("Theta6"));



    ui->tableWidget_4->setColumnCount(7);
    ui->tableWidget_4->setRowCount(2);
    ui->tableWidget_4->verticalHeader()->setVisible(false);
    ui->tableWidget_4->horizontalHeader()->setVisible(false);
    ui->tableWidget_4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->label_7->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/arrow.jpg"));
    QLabel *label3 = new QLabel("");
    label3->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget_4->setCellWidget(0,0,label3);
    ui->tableWidget_4->setItem(1,0,new QTableWidgetItem("Initial"));
    ui->tableWidget_4->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget_4->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget_4->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget_4->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget_4->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget_4->setItem(0,6,new QTableWidgetItem("Theta6"));
    ui->tableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_5->setColumnCount(7);
    ui->tableWidget_5->setRowCount(2);
    ui->tableWidget_5->verticalHeader()->setVisible(false);
    ui->tableWidget_5->horizontalHeader()->setVisible(false);
    ui->tableWidget_5->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QLabel *label4 = new QLabel("");
    label4->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget_5->setCellWidget(0,0,label4);
    ui->tableWidget_5->setItem(1,0,new QTableWidgetItem("Solution"));
    ui->tableWidget_5->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget_5->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget_5->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget_5->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget_5->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget_5->setItem(0,6,new QTableWidgetItem("Theta6"));




    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onExecuate()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(onEmpty()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(onEmptyAll()));
    connect(ui->comboBox,SIGNAL(activated(int)),this,SLOT(checkActiveSignal()));
}


subwidgetforIk::~subwidgetforIk()
{
    delete ui;
}

void subwidgetforIk::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void subwidgetforIk::checkActiveSignal(){
    switch (ui->comboBox->currentIndex()) {
         case 0:
              ui->tabWidget->setCurrentIndex(0);
              break;
         case 1:
              ui->tabWidget->setCurrentIndex(1);
              break;
         case 2:
              ui->tabWidget->setCurrentIndex(2);
              break;
         case 3:
              ui->tabWidget->setCurrentIndex(3);
              break;
         default:
              break;
    }
}


void subwidgetforIk::onEmpty(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    ui->textEdit_5->clear();
    ui->textEdit_6->clear();
}

void subwidgetforIk::onEmptyAll(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    ui->textEdit_5->clear();
    ui->textEdit_6->clear();

    ui->tableWidget->clear();
    QLabel *label = new QLabel("");
    label->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget->setCellWidget(0,0,label);
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Solution1"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Solution2"));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem("Solution3"));
    ui->tableWidget->setItem(4,0,new QTableWidgetItem("Solution4"));
    ui->tableWidget->setItem(5,0,new QTableWidgetItem("Solution5"));
    ui->tableWidget->setItem(6,0,new QTableWidgetItem("Solution6"));
    ui->tableWidget->setItem(7,0,new QTableWidgetItem("Solution7"));
    ui->tableWidget->setItem(8,0,new QTableWidgetItem("Solution8"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem("Theta6"));

    ui->tableWidget_2->clear();
    QLabel *label1 = new QLabel("");
    label1->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget_2->setCellWidget(0,0,label1);
    ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("Solution1"));
    ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("Solution2"));
    ui->tableWidget_2->setItem(3,0,new QTableWidgetItem("Solution3"));
    ui->tableWidget_2->setItem(4,0,new QTableWidgetItem("Solution4"));
    ui->tableWidget_2->setItem(5,0,new QTableWidgetItem("Solution5"));
    ui->tableWidget_2->setItem(6,0,new QTableWidgetItem("Solution6"));
    ui->tableWidget_2->setItem(7,0,new QTableWidgetItem("Solution7"));
    ui->tableWidget_2->setItem(8,0,new QTableWidgetItem("Solution8"));
    ui->tableWidget_2->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget_2->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget_2->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget_2->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget_2->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget_2->setItem(0,6,new QTableWidgetItem("Theta6"));

    ui->tableWidget_3->clear();
    QLabel *label2 = new QLabel("");
    label2->setPixmap(QPixmap("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/solution.jpg").scaled(94,61));
    ui->tableWidget_3->setCellWidget(0,0,label2);
    ui->tableWidget_3->setItem(1,0,new QTableWidgetItem("Solution"));
    ui->tableWidget_3->setItem(0,1,new QTableWidgetItem("Theta1"));
    ui->tableWidget_3->setItem(0,2,new QTableWidgetItem("Theta2"));
    ui->tableWidget_3->setItem(0,3,new QTableWidgetItem("Theta3"));
    ui->tableWidget_3->setItem(0,4,new QTableWidgetItem("Theta4"));
    ui->tableWidget_3->setItem(0,5,new QTableWidgetItem("Theta5"));
    ui->tableWidget_3->setItem(0,6,new QTableWidgetItem("Theta6"));

}

void subwidgetforIk::onExecuate(){
    if(ui->tabWidget->currentIndex()==0){
        x=ui->textEdit->toPlainText();
        y=ui->textEdit_2->toPlainText();
        z=ui->textEdit_3->toPlainText();
        r=ui->textEdit_4->toPlainText();
        p=ui->textEdit_5->toPlainText();
        gamma=ui->textEdit_6->toPlainText();

        IkReal xValue=x.toDouble();
        IkReal yValue=y.toDouble();
        IkReal zValue=z.toDouble();
        IkReal rValue=r.toDouble();
        IkReal pValue=p.toDouble();
        IkReal gammaValue=gamma.toDouble();

        IkReal eetrans[3], eerot[9] , euler[6]={ xValue,yValue,zValue,rValue,pValue,gammaValue },thetaRes[8][6] = {{0}};
        euler2matrix(euler,eetrans,eerot);
        ComputeIk(eetrans, eerot, thetaRes);
        QString textAt_00=QString::number(thetaRes[0][0],'d',4);
        ui->tableWidget->setItem(1,1,new QTableWidgetItem(textAt_00));
        QString textAt_01=QString::number(thetaRes[0][1],'d',4);
        ui->tableWidget->setItem(1,2,new QTableWidgetItem(textAt_01));
        QString textAt_02=QString::number(thetaRes[0][2],'d',4);
        ui->tableWidget->setItem(1,3,new QTableWidgetItem(textAt_02));
        QString textAt_03=QString::number(thetaRes[0][3],'d',4);
        ui->tableWidget->setItem(1,4,new QTableWidgetItem(textAt_03));
        QString textAt_04=QString::number(thetaRes[0][4],'d',4);
        ui->tableWidget->setItem(1,5,new QTableWidgetItem(textAt_04));
        QString textAt_05=QString::number(thetaRes[0][5],'d',4);
        ui->tableWidget->setItem(1,6,new QTableWidgetItem(textAt_05));
        QString textAt_10=QString::number(thetaRes[1][0],'d',4);
        ui->tableWidget->setItem(2,1,new QTableWidgetItem(textAt_10));
        QString textAt_11=QString::number(thetaRes[1][1],'d',4);
        ui->tableWidget->setItem(2,2,new QTableWidgetItem(textAt_11));
        QString textAt_12=QString::number(thetaRes[1][2],'d',4);
        ui->tableWidget->setItem(2,3,new QTableWidgetItem(textAt_12));
        QString textAt_13=QString::number(thetaRes[1][3],'d',4);
        ui->tableWidget->setItem(2,4,new QTableWidgetItem(textAt_13));
        QString textAt_14=QString::number(thetaRes[1][4],'d',4);
        ui->tableWidget->setItem(2,5,new QTableWidgetItem(textAt_14));
        QString textAt_15=QString::number(thetaRes[1][5],'d',4);
        ui->tableWidget->setItem(2,6,new QTableWidgetItem(textAt_15));
        QString textAt_20=QString::number(thetaRes[2][0],'d',4);
        ui->tableWidget->setItem(3,1,new QTableWidgetItem(textAt_20));
        QString textAt_21=QString::number(thetaRes[2][1],'d',4);
        ui->tableWidget->setItem(3,2,new QTableWidgetItem(textAt_21));
        QString textAt_22=QString::number(thetaRes[2][2],'d',4);
        ui->tableWidget->setItem(3,3,new QTableWidgetItem(textAt_22));
        QString textAt_23=QString::number(thetaRes[2][3],'d',4);
        ui->tableWidget->setItem(3,4,new QTableWidgetItem(textAt_23));
        QString textAt_24=QString::number(thetaRes[2][4],'d',4);
        ui->tableWidget->setItem(3,5,new QTableWidgetItem(textAt_24));
        QString textAt_25=QString::number(thetaRes[2][5],'d',4);
        ui->tableWidget->setItem(3,6,new QTableWidgetItem(textAt_25));
        QString textAt_30=QString::number(thetaRes[3][0],'d',4);
        ui->tableWidget->setItem(4,1,new QTableWidgetItem(textAt_30));
        QString textAt_31=QString::number(thetaRes[3][1],'d',4);
        ui->tableWidget->setItem(4,2,new QTableWidgetItem(textAt_31));
        QString textAt_32=QString::number(thetaRes[3][2],'d',4);
        ui->tableWidget->setItem(4,3,new QTableWidgetItem(textAt_32));
        QString textAt_33=QString::number(thetaRes[3][3],'d',4);
        ui->tableWidget->setItem(4,4,new QTableWidgetItem(textAt_33));
        QString textAt_34=QString::number(thetaRes[3][4],'d',4);
        ui->tableWidget->setItem(4,5,new QTableWidgetItem(textAt_34));
        QString textAt_35=QString::number(thetaRes[3][5],'d',4);
        ui->tableWidget->setItem(4,6,new QTableWidgetItem(textAt_35));
        QString textAt_40=QString::number(thetaRes[4][0],'d',4);
        ui->tableWidget->setItem(5,1,new QTableWidgetItem(textAt_40));
        QString textAt_41=QString::number(thetaRes[4][1],'d',4);
        ui->tableWidget->setItem(5,2,new QTableWidgetItem(textAt_41));
        QString textAt_42=QString::number(thetaRes[4][2],'d',4);
        ui->tableWidget->setItem(5,3,new QTableWidgetItem(textAt_42));
        QString textAt_43=QString::number(thetaRes[4][3],'d',4);
        ui->tableWidget->setItem(5,4,new QTableWidgetItem(textAt_43));
        QString textAt_44=QString::number(thetaRes[4][4],'d',4);
        ui->tableWidget->setItem(5,5,new QTableWidgetItem(textAt_44));
        QString textAt_45=QString::number(thetaRes[4][5],'d',4);
        ui->tableWidget->setItem(5,6,new QTableWidgetItem(textAt_45));
        QString textAt_50=QString::number(thetaRes[5][0],'d',4);
        ui->tableWidget->setItem(6,1,new QTableWidgetItem(textAt_50));
        QString textAt_51=QString::number(thetaRes[5][1],'d',4);
        ui->tableWidget->setItem(6,2,new QTableWidgetItem(textAt_51));
        QString textAt_52=QString::number(thetaRes[5][2],'d',4);
        ui->tableWidget->setItem(6,3,new QTableWidgetItem(textAt_52));
        QString textAt_53=QString::number(thetaRes[5][3],'d',4);
        ui->tableWidget->setItem(6,4,new QTableWidgetItem(textAt_53));
        QString textAt_54=QString::number(thetaRes[5][4],'d',4);
        ui->tableWidget->setItem(6,5,new QTableWidgetItem(textAt_54));
        QString textAt_55=QString::number(thetaRes[5][5],'d',4);
        ui->tableWidget->setItem(6,6,new QTableWidgetItem(textAt_55));
        QString textAt_60=QString::number(thetaRes[6][0],'d',4);
        ui->tableWidget->setItem(7,1,new QTableWidgetItem(textAt_60));
        QString textAt_61=QString::number(thetaRes[6][1],'d',4);
        ui->tableWidget->setItem(7,2,new QTableWidgetItem(textAt_61));
        QString textAt_62=QString::number(thetaRes[6][2],'d',4);
        ui->tableWidget->setItem(7,3,new QTableWidgetItem(textAt_62));
        QString textAt_63=QString::number(thetaRes[6][3],'d',4);
        ui->tableWidget->setItem(7,4,new QTableWidgetItem(textAt_63));
        QString textAt_64=QString::number(thetaRes[6][4],'d',4);
        ui->tableWidget->setItem(7,5,new QTableWidgetItem(textAt_64));
        QString textAt_65=QString::number(thetaRes[6][5],'d',4);
        ui->tableWidget->setItem(7,6,new QTableWidgetItem(textAt_65));
        QString textAt_70=QString::number(thetaRes[7][0],'d',4);
        ui->tableWidget->setItem(8,1,new QTableWidgetItem(textAt_70));
        QString textAt_71=QString::number(thetaRes[7][1],'d',4);
        ui->tableWidget->setItem(8,2,new QTableWidgetItem(textAt_71));
        QString textAt_72=QString::number(thetaRes[7][2],'d',4);
        ui->tableWidget->setItem(8,3,new QTableWidgetItem(textAt_72));
        QString textAt_73=QString::number(thetaRes[7][3],'d',4);
        ui->tableWidget->setItem(8,4,new QTableWidgetItem(textAt_73));
        QString textAt_74=QString::number(thetaRes[7][4],'d',4);
        ui->tableWidget->setItem(8,5,new QTableWidgetItem(textAt_74));
        QString textAt_75=QString::number(thetaRes[7][5],'d',4);
        ui->tableWidget->setItem(8,6,new QTableWidgetItem(textAt_75));
     }else if(ui->tabWidget->currentIndex()==1){
        x=ui->textEdit->toPlainText();
        y=ui->textEdit_2->toPlainText();
        z=ui->textEdit_3->toPlainText();
        r=ui->textEdit_4->toPlainText();
        p=ui->textEdit_5->toPlainText();
        gamma=ui->textEdit_6->toPlainText();

        IkReal xValue=x.toDouble();
        IkReal yValue=y.toDouble();
        IkReal zValue=z.toDouble();
        IkReal rValue=r.toDouble();
        IkReal pValue=p.toDouble();
        IkReal gammaValue=gamma.toDouble();

        IkReal eetrans[3], eerot[9] , euler[6]={ xValue,yValue,zValue,rValue,pValue,gammaValue };
        euler2matrix(euler,eetrans,eerot);
        IkReal T[12]={eerot[2],eerot[0],eerot[1],eetrans[0],eerot[5],eerot[3],eerot[4],eetrans[1],eerot[8],eerot[6],eerot[7],eetrans[2]};
        IkReal q_sols[8*6]={0};
        int num_sols;
        num_sols = inverse(T, q_sols,NULL);

        QString textAt_00=num_sols>=1?QString::number(q_sols[0],'d',4):"NULL";
        ui->tableWidget_2->setItem(1,1,new QTableWidgetItem(textAt_00));
        QString textAt_01=num_sols>=1?QString::number(q_sols[1],'d',4):"NULL";
        ui->tableWidget_2->setItem(1,2,new QTableWidgetItem(textAt_01));
        QString textAt_02=num_sols>=1?QString::number(q_sols[2],'d',4):"NULL";
        ui->tableWidget_2->setItem(1,3,new QTableWidgetItem(textAt_02));
        QString textAt_03=num_sols>=1?QString::number(q_sols[3],'d',4):"NULL";
        ui->tableWidget_2->setItem(1,4,new QTableWidgetItem(textAt_03));
        QString textAt_04=num_sols>=1?QString::number(q_sols[4],'d',4):"NULL";
        ui->tableWidget_2->setItem(1,5,new QTableWidgetItem(textAt_04));
        QString textAt_05=num_sols>=1?QString::number(q_sols[5],'d',4):"NULL";
        ui->tableWidget_2->setItem(1,6,new QTableWidgetItem(textAt_05));
        QString textAt_10=num_sols>=2?QString::number(q_sols[6],'d',4):"NULL";
        ui->tableWidget_2->setItem(2,1,new QTableWidgetItem(textAt_10));
        QString textAt_11=num_sols>=2?QString::number(q_sols[7],'d',4):"NULL";
        ui->tableWidget_2->setItem(2,2,new QTableWidgetItem(textAt_11));
        QString textAt_12=num_sols>=2?QString::number(q_sols[8],'d',4):"NULL";
        ui->tableWidget_2->setItem(2,3,new QTableWidgetItem(textAt_12));
        QString textAt_13=num_sols>=2?QString::number(q_sols[9],'d',4):"NULL";
        ui->tableWidget_2->setItem(2,4,new QTableWidgetItem(textAt_13));
        QString textAt_14=num_sols>=2?QString::number(q_sols[10],'d',4):"NULL";
        ui->tableWidget_2->setItem(2,5,new QTableWidgetItem(textAt_14));
        QString textAt_15=num_sols>=2?QString::number(q_sols[11],'d',4):"NULL";
        ui->tableWidget_2->setItem(2,6,new QTableWidgetItem(textAt_15));
        QString textAt_20=num_sols>=3?QString::number(q_sols[12],'d',4):"NULL";
        ui->tableWidget_2->setItem(3,1,new QTableWidgetItem(textAt_20));
        QString textAt_21=num_sols>=3?QString::number(q_sols[13],'d',4):"NULL";
        ui->tableWidget_2->setItem(3,2,new QTableWidgetItem(textAt_21));
        QString textAt_22=num_sols>=3?QString::number(q_sols[14],'d',4):"NULL";
        ui->tableWidget_2->setItem(3,3,new QTableWidgetItem(textAt_22));
        QString textAt_23=num_sols>=3?QString::number(q_sols[15],'d',4):"NULL";
        ui->tableWidget_2->setItem(3,4,new QTableWidgetItem(textAt_23));
        QString textAt_24=num_sols>=3?QString::number(q_sols[16],'d',4):"NULL";
        ui->tableWidget_2->setItem(3,5,new QTableWidgetItem(textAt_24));
        QString textAt_25=num_sols>=3?QString::number(q_sols[17],'d',4):"NULL";
        ui->tableWidget_2->setItem(3,6,new QTableWidgetItem(textAt_25));
        QString textAt_30=num_sols>=4?QString::number(q_sols[18],'d',4):"NULL";
        ui->tableWidget_2->setItem(4,1,new QTableWidgetItem(textAt_30));
        QString textAt_31=num_sols>=4?QString::number(q_sols[19],'d',4):"NULL";
        ui->tableWidget_2->setItem(4,2,new QTableWidgetItem(textAt_31));
        QString textAt_32=num_sols>=4?QString::number(q_sols[20],'d',4):"NULL";
        ui->tableWidget_2->setItem(4,3,new QTableWidgetItem(textAt_32));
        QString textAt_33=num_sols>=4?QString::number(q_sols[21],'d',4):"NULL";
        ui->tableWidget_2->setItem(4,4,new QTableWidgetItem(textAt_33));
        QString textAt_34=num_sols>=4?QString::number(q_sols[22],'d',4):"NULL";
        ui->tableWidget_2->setItem(4,5,new QTableWidgetItem(textAt_34));
        QString textAt_35=num_sols>=4?QString::number(q_sols[23],'d',4):"NULL";
        ui->tableWidget_2->setItem(4,6,new QTableWidgetItem(textAt_35));
        QString textAt_40=num_sols>=5?QString::number(q_sols[24],'d',4):"NULL";
        ui->tableWidget_2->setItem(5,1,new QTableWidgetItem(textAt_40));
        QString textAt_41=num_sols>=5?QString::number(q_sols[25],'d',4):"NULL";
        ui->tableWidget_2->setItem(5,2,new QTableWidgetItem(textAt_41));
        QString textAt_42=num_sols>=5?QString::number(q_sols[26],'d',4):"NULL";
        ui->tableWidget_2->setItem(5,3,new QTableWidgetItem(textAt_42));
        QString textAt_43=num_sols>=5?QString::number(q_sols[27],'d',4):"NULL";
        ui->tableWidget_2->setItem(5,4,new QTableWidgetItem(textAt_43));
        QString textAt_44=num_sols>=5?QString::number(q_sols[28],'d',4):"NULL";
        ui->tableWidget_2->setItem(5,5,new QTableWidgetItem(textAt_44));
        QString textAt_45=num_sols>=5?QString::number(q_sols[29],'d',4):"NULL";
        ui->tableWidget_2->setItem(5,6,new QTableWidgetItem(textAt_45));
        QString textAt_50=num_sols>=6?QString::number(q_sols[30],'d',4):"NULL";
        ui->tableWidget_2->setItem(6,1,new QTableWidgetItem(textAt_50));
        QString textAt_51=num_sols>=6?QString::number(q_sols[31],'d',4):"NULL";
        ui->tableWidget_2->setItem(6,2,new QTableWidgetItem(textAt_51));
        QString textAt_52=num_sols>=6?QString::number(q_sols[32],'d',4):"NULL";
        ui->tableWidget_2->setItem(6,3,new QTableWidgetItem(textAt_52));
        QString textAt_53=num_sols>=6?QString::number(q_sols[33],'d',4):"NULL";
        ui->tableWidget_2->setItem(6,4,new QTableWidgetItem(textAt_53));
        QString textAt_54=num_sols>=6?QString::number(q_sols[34],'d',4):"NULL";
        ui->tableWidget_2->setItem(6,5,new QTableWidgetItem(textAt_54));
        QString textAt_55=num_sols>=6?QString::number(q_sols[35],'d',4):"NULL";
        ui->tableWidget_2->setItem(6,6,new QTableWidgetItem(textAt_55));
        QString textAt_60=num_sols>=7?QString::number(q_sols[36],'d',4):"NULL";
        ui->tableWidget_2->setItem(7,1,new QTableWidgetItem(textAt_60));
        QString textAt_61=num_sols>=7?QString::number(q_sols[37],'d',4):"NULL";
        ui->tableWidget_2->setItem(7,2,new QTableWidgetItem(textAt_61));
        QString textAt_62=num_sols>=7?QString::number(q_sols[38],'d',4):"NULL";
        ui->tableWidget_2->setItem(7,3,new QTableWidgetItem(textAt_62));
        QString textAt_63=num_sols>=7?QString::number(q_sols[39],'d',4):"NULL";
        ui->tableWidget_2->setItem(7,4,new QTableWidgetItem(textAt_63));
        QString textAt_64=num_sols>=7?QString::number(q_sols[40],'d',4):"NULL";
        ui->tableWidget_2->setItem(7,5,new QTableWidgetItem(textAt_64));
        QString textAt_65=num_sols>=7?QString::number(q_sols[41],'d',4):"NULL";
        ui->tableWidget_2->setItem(7,6,new QTableWidgetItem(textAt_65));
        QString textAt_70=num_sols>=8?QString::number(q_sols[42],'d',4):"NULL";
        ui->tableWidget_2->setItem(8,1,new QTableWidgetItem(textAt_70));
        QString textAt_71=num_sols>=8?QString::number(q_sols[43],'d',4):"NULL";
        ui->tableWidget_2->setItem(8,2,new QTableWidgetItem(textAt_71));
        QString textAt_72=num_sols>=8?QString::number(q_sols[44],'d',4):"NULL";
        ui->tableWidget_2->setItem(8,3,new QTableWidgetItem(textAt_72));
        QString textAt_73=num_sols>=8?QString::number(q_sols[45],'d',4):"NULL";
        ui->tableWidget_2->setItem(8,4,new QTableWidgetItem(textAt_73));
        QString textAt_74=num_sols>=8?QString::number(q_sols[46],'d',4):"NULL";
        ui->tableWidget_2->setItem(8,5,new QTableWidgetItem(textAt_74));
        QString textAt_75=num_sols>=8?QString::number(q_sols[47],'d',4):"NULL";
        ui->tableWidget_2->setItem(8,6,new QTableWidgetItem(textAt_75));

     }else if(ui->tabWidget->currentIndex()==2){
        x=ui->textEdit->toPlainText();
        y=ui->textEdit_2->toPlainText();
        z=ui->textEdit_3->toPlainText();
        r=ui->textEdit_4->toPlainText();
        p=ui->textEdit_5->toPlainText();
        gamma=ui->textEdit_6->toPlainText();

        IkReal xValue=x.toDouble();
        IkReal yValue=y.toDouble();
        IkReal zValue=z.toDouble();
        IkReal rValue=r.toDouble();
        IkReal pValue=p.toDouble();
        IkReal gammaValue=gamma.toDouble();

        IkReal euler[6]={ xValue,yValue,zValue,rValue,pValue,gammaValue };
        vector<double> q_ready(6,0);
        q_ready[0]=ui->tableWidget_4->item(1,1)->text().toDouble();//取出字符串
        q_ready[1]=ui->tableWidget_4->item(1,2)->text().toDouble();
        q_ready[2]=ui->tableWidget_4->item(1,3)->text().toDouble();
        q_ready[3]=ui->tableWidget_4->item(1,4)->text().toDouble();//取出字符串
        q_ready[4]=ui->tableWidget_4->item(1,5)->text().toDouble();
        q_ready[5]=ui->tableWidget_4->item(1,6)->text().toDouble();
        //iterate_ikine(q_ready,euler);
    }
}

void subwidgetforIk::ComputeFk(const IkReal* j, IkReal* eetrans, IkReal* eerot) {   //正运动学
    IkReal x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20,x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47;
    x0 = cos(j[0]);
    x1 = cos(j[1]);
    x2 = cos(j[2]);
    x3 = sin(j[1]);
    x4 = sin(j[2]);
    x5 = cos(j[3]);
    x6 = sin(j[3]);
    x7 = cos(j[5]);
    x8 = sin(j[5]);
    x9 = cos(j[4]);
    x10 = sin(j[0]);
    x11 = sin(j[4]);
    x12 = ((0.39225)*x0);
    x13 = ((0.09465)*x0);
    x14 = ((1.0)*x6);
    x15 = ((1.0)*x10);
    x16 = ((0.09465)*x10);
    x17 = ((0.0823)*x6);
    x18 = ((1.0)*x0);
    x19 = ((0.39225)*x4);
    x20 = ((0.425)*x1);
    x21 = ((0.0823)*x5);
    x22 = ((1.0)*x9);
    x23 = ((1.0)*x5);    //DH参数
    x24 = (x1*x2);
    x25 = (x10*x9);
    x26 = (x1*x4);
    x27 = (x2*x3);
    x28 = (x3*x4);
    x29 = (x18*x28);
    x30 = (x15*x28);
    x31 = (x26 + x27);
    x32 = ((((-1.0)*x28)) + (((1.0)*x24)));
    x33 = (x31*x5);
    x34 = (x32*x6);
    x35 = (((x0*x24)) + (((-1.0)*x29)));
    x36 = ((((-1.0)*x30)) + ((x10*x24)));
    x37 = (x18*(((((-1.0)*x26)) + (((-1.0)*x27)))));
    x38 = (x15*(((((-1.0)*x26)) + (((-1.0)*x27)))));
    x39 = (x35*x5);
    x40 = (x36*x5);
    x41 = (x37*x6);
    x42 = (((x32*x5)) + ((x6*(((((-1.0)*x26)) + (((-1.0)*x27)))))));
    x43 = (x39 + x41);
    x44 = (x40 + ((x38*x6)));
    x45 = (((x37*x5)) + ((x6*(((((-1.0)*x18*x24)) + x29)))));
    x46 = (((x6*(((((-1.0)*x15*x24)) + x30)))) + ((x38*x5)));
    x47 = (x43*x9);
    eerot[0] = (((x7*((x47 + ((x10*x11)))))) + ((x45*x8)));
    eerot[1] = (((x8*(((((-1.0)*x11*x15)) + (((-1.0)*x22*x43)))))) + ((x45*x7)));
    eerot[2] = (((x11*(((((-1.0)*x14*x37)) + (((-1.0)*x23*x35)))))) + x25);
    eetrans[0] = (((x5*((((x13*x27)) + ((x13*x26)))))) + (((0.10915)*x10)) + ((x6*(((((-1.0)*x13*x28)) + ((x13*x24)))))) + (((-1.0)*x0*x20)) + (((-1.0)*x12*x24)) + ((x12*x28)) + (((0.0823)*x25)) + ((x11*(((((-1.0)*x17*x37)) + (((-1.0)*x21*x35)))))));
    eerot[3] = (((x46*x8)) + ((x7*(((((-1.0)*x0*x11)) + ((x44*x9)))))));
    eerot[4] = (((x46*x7)) + ((x8*(((((-1.0)*x22*x44)) + ((x11*x18)))))));
    eerot[5] = ((((-1.0)*x18*x9)) + ((x11*(((((-1.0)*x14*x38)) + (((-1.0)*x23*x36)))))));
    eetrans[1] = ((((-0.0823)*x0*x9)) + (((-0.39225)*x10*x24)) + ((x5*((((x16*x26)) + ((x16*x27)))))) + (((-0.10915)*x0)) + (((-1.0)*x10*x20)) + ((x6*(((((-1.0)*x16*x28)) + ((x16*x24)))))) + ((x10*x19*x3)) + ((x11*(((((-1.0)*x17*x38)) + (((-1.0)*x21*x36)))))));
    eerot[6] = (((x7*x9*((x33 + x34)))) + ((x42*x8)));
    eerot[7] = (((x8*x9*(((((-1.0)*x34)) + (((-1.0)*x33)))))) + ((x42*x7)));
    eerot[8] = (x11*(((((-1.0)*x14*x32)) + (((-1.0)*x23*x31)))));
    eetrans[2] = ((0.089159) + (((-1.0)*x1*x19)) + ((x6*(((((0.09465)*x26)) + (((0.09465)*x27)))))) + (((-0.425)*x3)) + ((x11*(((((-1.0)*x17*x32)) + (((-1.0)*x21*x31)))))) + ((x5*(((((-0.09465)*x24)) + (((0.09465)*x28)))))) + (((-0.39225)*x27)));
}

int subwidgetforIk::inverse(const IkReal* T, IkReal* q_sols, IkReal q6_des) {
    int num_sols = 0;
    IkReal T02 =  *T; T++; IkReal T00 =  *T; T++; IkReal T01 =  *T; T++; IkReal T03 =  *T; T++;
    IkReal T12 =  *T; T++; IkReal T10 =  *T; T++; IkReal T11 =  *T; T++; IkReal T13 =  *T; T++;
    IkReal T22 =  *T; T++; IkReal T20 =  *T; T++; IkReal T21 =  *T; T++; IkReal T23 =  *T;

    ////////////////////////////// shoulder rotate joint (q1) //////////////////////////////
    IkReal q1[2];
    {
      IkReal A = d6*T12 - T13;
      IkReal B = d6*T02 - T03;
      IkReal R = A*A + B*B;
      if(fabs(A) < ZERO_THRESH) {
        IkReal div;
        if(fabs(fabs(d4) - fabs(B)) < ZERO_THRESH)
          div = -SIGN(d4)*SIGN(B);
        else
          div = -d4/B;
        IkReal arcsin = asin(div);
        if(fabs(arcsin) < ZERO_THRESH)
          arcsin = 0.0;
        if(arcsin < 0.0)
          q1[0] = arcsin + 2.0*IKPI;
        else
          q1[0] = arcsin;
        q1[1] = IKPI - arcsin;
      }
      else if(fabs(B) < ZERO_THRESH) {
        IkReal div;
        if(fabs(fabs(d4) - fabs(A)) < ZERO_THRESH)
          div = SIGN(d4)*SIGN(A);
        else
          div = d4/A;
        IkReal arccos = acos(div);
        q1[0] = arccos;
        q1[1] = 2.0*IKPI - arccos;
      }
      else if(d4*d4 > R) {
        return num_sols;
      }
      else {
        IkReal arccos = acos(d4 / sqrt(R)) ;
        IkReal arctan = atan2(-B, A);
        IkReal pos = arccos + arctan;
        IkReal neg = -arccos + arctan;
        if(fabs(pos) < ZERO_THRESH)
          pos = 0.0;
        if(fabs(neg) < ZERO_THRESH)
          neg = 0.0;
        if(pos >= 0.0)
          q1[0] = pos;
        else
          q1[0] = 2.0*IKPI + pos;
        if(neg >= 0.0)
          q1[1] = neg;
        else
          q1[1] = 2.0*IKPI + neg;
      }
    }
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////// wrist 2 joint (q5) //////////////////////////////
    IkReal q5[2][2];
    {
      for(int i=0;i<2;i++) {
        IkReal numer = (T03*sin(q1[i]) - T13*cos(q1[i])-d4);
        IkReal div;
        if(fabs(fabs(numer) - fabs(d6)) < ZERO_THRESH)
          div = SIGN(numer) * SIGN(d6);
        else
          div = numer / d6;
        IkReal arccos = acos(div);
        q5[i][0] = arccos;
        q5[i][1] = 2.0*IKPI - arccos;
      }
    }
    ////////////////////////////////////////////////////////////////////////////////

    {
      for(int i=0;i<2;i++) {
        for(int j=0;j<2;j++) {
          IkReal c1 = cos(q1[i]), s1 = sin(q1[i]);
          IkReal c5 = cos(q5[i][j]), s5 = sin(q5[i][j]);
          IkReal q6;
          ////////////////////////////// wrist 3 joint (q6) //////////////////////////////
          if(fabs(s5) < ZERO_THRESH)
            q6 = q6_des;
          else {
            q6 = atan2(SIGN(s5)*-(T01*s1 - T11*c1),
                       SIGN(s5)*(T00*s1 - T10*c1));
            if(fabs(q6) < ZERO_THRESH)
              q6 = 0.0;
            if(q6 < 0.0)
              q6 += 2.0*IKPI;
          }
          ////////////////////////////////////////////////////////////////////////////////

          IkReal q2[2], q3[2], q4[2];
          ///////////////////////////// RRR joints (q2,q3,q4) ////////////////////////////
          IkReal c6 = cos(q6), s6 = sin(q6);
          IkReal x04x = -s5*(T02*c1 + T12*s1) - c5*(s6*(T01*c1 + T11*s1) - c6*(T00*c1 + T10*s1));
          IkReal x04y = c5*(T20*c6 - T21*s6) - T22*s5;
          IkReal p13x = d5*(s6*(T00*c1 + T10*s1) + c6*(T01*c1 + T11*s1)) - d6*(T02*c1 + T12*s1) +
                        T03*c1 + T13*s1;
          IkReal p13y = T23 - d1 - d6*T22 + d5*(T21*c6 + T20*s6);

          IkReal c3 = (p13x*p13x + p13y*p13y - a2*a2 - a3*a3) / (2.0*a2*a3);
          if(fabs(fabs(c3) - 1.0) < ZERO_THRESH)
            c3 = SIGN(c3);
          else if(fabs(c3) > 1.0) {
            // TODO NO SOLUTION
            continue;
          }
          IkReal arccos = acos(c3);
          q3[0] = arccos;
          q3[1] = 2.0*IKPI - arccos;
          IkReal denom = a2*a2 + a3*a3 + 2*a2*a3*c3;
          IkReal s3 = sin(arccos);
          IkReal A = (a2 + a3*c3), B = a3*s3;
          q2[0] = atan2((A*p13y - B*p13x) / denom, (A*p13x + B*p13y) / denom);
          q2[1] = atan2((A*p13y + B*p13x) / denom, (A*p13x - B*p13y) / denom);
          IkReal c23_0 = cos(q2[0]+q3[0]);
          IkReal s23_0 = sin(q2[0]+q3[0]);
          IkReal c23_1 = cos(q2[1]+q3[1]);
          IkReal s23_1 = sin(q2[1]+q3[1]);
          q4[0] = atan2(c23_0*x04y - s23_0*x04x, x04x*c23_0 + x04y*s23_0);
          q4[1] = atan2(c23_1*x04y - s23_1*x04x, x04x*c23_1 + x04y*s23_1);
          ////////////////////////////////////////////////////////////////////////////////
          for(int k=0;k<2;k++) {
            if(fabs(q2[k]) < ZERO_THRESH)
              q2[k] = 0.0;
            else if(q2[k] < 0.0) q2[k] += 2.0*IKPI;
            if(fabs(q4[k]) < ZERO_THRESH)
              q4[k] = 0.0;
            else if(q4[k] < 0.0) q4[k] += 2.0*IKPI;
            q_sols[num_sols*6+0] = q1[i];    q_sols[num_sols*6+1] = q2[k];
            q_sols[num_sols*6+2] = q3[k];    q_sols[num_sols*6+3] = q4[k];
            q_sols[num_sols*6+4] = q5[i][j]; q_sols[num_sols*6+5] = q6;
            num_sols++;
          }

        }
      }
    }

    for(int i=0;i<num_sols;++i){
        for(int j=0;j<6;++j){
            q_sols[j+i*6]*=ARC_TO_DEG;
            q_sols[j+i*6]= (q_sols[j+i*6] > 180 )? (q_sols[j+i*6] - 360) : q_sols[j+i*6];
            q_sols[j+i*6]= (q_sols[j+i*6] < -180) ? (q_sols[j+i*6] + 360) : q_sols[j+i*6];
        }
    }
    return num_sols;
}

void subwidgetforIk::ComputeIk(IkReal* eetrans, IkReal* eerot, IkReal(*thetaRes)[6]) {    //逆运动学

    IkReal d[6] = { 0.089459, 0,0 ,0.10915,0.09465,0.0823 };
    IkReal a[6] = { 0, -0.4250, -0.39225, 0 ,0 ,0 };
    IkReal alpha[6] = { 1.5708, 0, 0, 1.5708 ,-1.5708,0 };
    IkReal theta[6] = { 0,0,0,0,0,0 };

    IkReal nx = eerot[0];
    IkReal ny = eerot[3];
    IkReal nz = eerot[6];

    IkReal ox = eerot[1];
    IkReal oy = eerot[4];
    IkReal oz = eerot[7];

    IkReal ax = eerot[2];
    IkReal ay = eerot[5];
    IkReal az = eerot[8];

    IkReal px = eetrans[0];
    IkReal py = eetrans[1];
    IkReal pz = eetrans[2];


    IkReal m = d[5] * ay - py;
    IkReal n = px - d[5] * ax;

    IkReal theta11 = acos(d[3] / sqrt(m * m + n * n)) + atan2(n, m);
    IkReal theta12 = -acos(d[3] / sqrt(m * m + n * n)) + atan2(n, m);
    IkReal theta1[2] = { theta11, theta12 };


    IkReal theta51 = acos(ax*sin(theta1[0]) - ay * cos(theta1[0]));
    IkReal theta52 = acos(ax*sin(theta1[1]) - ay * cos(theta1[1]));
    IkReal theta53 = -acos(ax*sin(theta1[0]) - ay * cos(theta1[0]));
    IkReal theta54 = -acos(ax*sin(theta1[1]) - ay * cos(theta1[1]));
    IkReal theta5[2][2];
    theta5[0][0] = theta51, theta5[0][1] = theta52, theta5[1][0] = theta53, theta5[1][1] = theta54;


    IkReal mm1 = nx * sin(theta1[0]) - ny * cos(theta1[0]);
    IkReal mm2 = nx * sin(theta1[1]) - ny * cos(theta1[1]);
    IkReal mm[2] = { mm1,mm2 };

    IkReal nn1 = ox * sin(theta1[0]) - oy * cos(theta1[0]);
    IkReal nn2 = ox * sin(theta1[1]) - oy * cos(theta1[1]);
    IkReal nn[2] = { nn1,nn2 };


    IkReal theta61 = atan2(mm[0], nn[0]) - atan2(sin(theta5[0][0]), 0);
    IkReal theta62 = atan2(mm[1], nn[1]) - atan2(sin(theta5[0][1]), 0);
    IkReal theta63 = atan2(mm[0], nn[0]) - atan2(sin(theta5[1][0]), 0);
    IkReal theta64 = atan2(mm[1], nn[1]) - atan2(sin(theta5[1][1]), 0);
    IkReal theta6[2][2];
    theta6[0][0] = theta61, theta6[0][1] = theta62, theta6[1][0] = theta63, theta6[1][1] = theta64;


    IkReal mmm[2][2];
    mmm[0][0]= d[4]*(sin(theta6[0][0])*(nx*cos(theta1[0]) + ny * sin(theta1[0])) + cos(theta6[0][0])*(ox*cos(theta1[0]) + oy * sin(theta1[0])))
        - d[5]*(ax*cos(theta1[0]) + ay * sin(theta1[0])) + px * cos(theta1[0]) + py * sin(theta1[0]);
    mmm[0][1] = d[4]*(sin(theta6[0][1])*(nx*cos(theta1[1]) + ny * sin(theta1[1])) + cos(theta6[0][1])*(ox*cos(theta1[1]) + oy * sin(theta1[1])))
        - d[5] * (ax*cos(theta1[1]) + ay * sin(theta1[1])) + px * cos(theta1[1]) + py * sin(theta1[1]);

    IkReal nnn[2][2];
    nnn[0][0] = pz - d[0] - az * d[5] + d[4] * (  oz*cos(theta6[0][0]) + nz * sin(theta6[0][0]) );
    nnn[0][1] = pz - d[0] - az * d[5] + d[4] * (  oz*cos(theta6[0][1]) + nz * sin(theta6[0][1]) );

    mmm[1][0] = d[4] * (sin(theta6[1][0])*(nx*cos(theta1[0]) + ny * sin(theta1[0])) + cos(theta6[1][0])*(ox*cos(theta1[0]) + oy * sin(theta1[0])))
        - d[5] * (ax*cos(theta1[0]) + ay * sin(theta1[0])) + px * cos(theta1[0]) + py * sin(theta1[0]);
    mmm[1][1] = d[4] * (sin(theta6[1][1])*(nx*cos(theta1[1]) + ny * sin(theta1[1])) + cos(theta6[1][1])*(ox*cos(theta1[1]) + oy * sin(theta1[1])))
        - d[5] * (ax*cos(theta1[1]) + ay * sin(theta1[1])) + px * cos(theta1[1]) + py * sin(theta1[1]);

    nnn[1][0] = pz - d[0] - az * d[5] + d[4] * ( oz*cos(theta6[1][0]) + nz * sin(theta6[1][0]) );
    nnn[1][1] = pz - d[0] - az * d[5] + d[4] * ( oz*cos(theta6[1][1]) + nz * sin(theta6[1][1]) );



    IkReal theta3[4][2];
    theta3[0][0] = acos( (mmm[0][0]*mmm[0][0] + nnn[0][0]*nnn[0][0] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[0][1] = acos( (mmm[0][1]*mmm[0][1] + nnn[0][1]*nnn[0][1] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[1][0] = acos( (mmm[1][0]*mmm[1][0] + nnn[1][0]*nnn[1][0] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[1][1] = acos( (mmm[1][1]*mmm[1][1] + nnn[1][1]*nnn[1][1] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[2][0] = -acos( (mmm[0][0]*mmm[0][0] + nnn[0][0]*nnn[0][0] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[2][1] = -acos( (mmm[0][1]*mmm[0][1] + nnn[0][1]*nnn[0][1] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[3][0] = -acos( (mmm[1][0]*mmm[1][0] + nnn[1][0]*nnn[1][0] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );
    theta3[3][1] = -acos( (mmm[1][1]*mmm[1][1] + nnn[1][1]*nnn[1][1] - a[1]*a[1] - a[2]*a[2]) / (2*a[1]*a[2]) );


    IkReal theta2[4][2];


    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            theta2[i][j] = atan2(nnn[(i>= 2)?i-2:i][j]*(a[1]+a[2]*cos(theta3[i][j]))-mmm[(i>= 2)?i-2:i][j]*a[2]*sin(theta3[i][j]),
                                mmm[(i>= 2)?i-2:i][j]*(a[1]+a[2]*cos(theta3[i][j]))+nnn[(i>= 2)?i-2:i][j]*a[2]*sin(theta3[i][j]));}
    }


    for (int i = 0; i < 8; ++i) {
        thetaRes[i][0] = theta1[i<4?0:1];
    }

    thetaRes[0][1] = theta2[0][0];
    thetaRes[1][1] = theta2[2][0];
    thetaRes[2][1] = theta2[1][0];
    thetaRes[3][1] = theta2[3][0];
    thetaRes[4][1] = theta2[0][1];
    thetaRes[5][1] = theta2[2][1];
    thetaRes[6][1] = theta2[1][1];
    thetaRes[7][1] = theta2[3][1];

    thetaRes[0][2] = theta3[0][0];
    thetaRes[1][2] = theta3[2][0];
    thetaRes[2][2] = theta3[1][0];
    thetaRes[3][2] = theta3[3][0];
    thetaRes[4][2] = theta3[0][1];
    thetaRes[5][2] = theta3[2][1];
    thetaRes[6][2] = theta3[1][1];
    thetaRes[7][2] = theta3[3][1];

    thetaRes[0][4] = theta5[0][0];
    thetaRes[1][4] = theta5[0][0];
    thetaRes[2][4] = theta5[1][0];
    thetaRes[3][4] = theta5[1][0];
    thetaRes[4][4] = theta5[0][1];
    thetaRes[5][4] = theta5[0][1];
    thetaRes[6][4] = theta5[1][1];
    thetaRes[7][4] = theta5[1][1];

    thetaRes[0][5] = theta6[0][0];
    thetaRes[1][5] = theta6[0][0];
    thetaRes[2][5] = theta6[1][0];
    thetaRes[3][5] = theta6[1][0];
    thetaRes[4][5] = theta6[0][1];
    thetaRes[5][5] = theta6[0][1];
    thetaRes[6][5] = theta6[1][1];
    thetaRes[7][5] = theta6[1][1];

    for (int i = 0; i < 8; ++i) {
        thetaRes[i][3] = atan2( -sin(thetaRes[i][5])*(nx*cos(thetaRes[i][0]) + ny * sin(thetaRes[i][0] )) - cos(thetaRes[i][5] )*
            (ox*cos(thetaRes[i][0]) + oy * sin(thetaRes[i][0])), oz*cos(thetaRes[i][5] ) + nz * sin(thetaRes[i][5] )) - thetaRes[i][1] - thetaRes[i][2];
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 6; ++j) {
            thetaRes[i][j] = thetaRes[i][j] * ARC_TO_DEG;
            thetaRes[i][j]= (thetaRes[i][j] > 180 )? (thetaRes[i][j] - 360) : thetaRes[i][j];
            thetaRes[i][j]= (thetaRes[i][j] < -180) ? (thetaRes[i][j] + 360) : thetaRes[i][j];
        }
    }
}

void subwidgetforIk::matrix2euler(IkReal*eetrans, IkReal* eerot, IkReal* euler) {  //旋转矩阵转欧拉角
    euler[0] = eetrans[0], euler[1] = eetrans[1], euler[2] = eetrans[2];
    euler[3] = atan2(-eerot[1], eerot[0]);
    euler[4] = atan2(eerot[2], sqrt(eerot[5] * eerot[5] + eerot[8] * eerot[8]));
    euler[5] = atan2(-eerot[5], eerot[8]);

    euler[3] = euler[3] * ARC_TO_DEG;
    euler[4] = euler[4] * ARC_TO_DEG;
    euler[5] = euler[5] * ARC_TO_DEG;
}



void subwidgetforIk::euler2matrix(IkReal* euler, IkReal*eetrans, IkReal* eerot) {   //欧拉角转旋转矩阵
    IkReal x = euler[0] , y = euler[1] , z = euler[2];
    IkReal r = euler[3] * DEG_TO_ARC , p = euler[4] * DEG_TO_ARC , gamma = euler[5] * DEG_TO_ARC;
    IkReal rotX[3][3] = { {1,0,0},{0,cos(gamma),-sin(gamma)},{0,sin(gamma),cos(gamma)} };
    IkReal rotY[3][3] = { {cos(p),0,sin(p)},{0,1,0},{-sin(p),0,cos(p)} };
    IkReal rotZ[3][3] = { {cos(r),-sin(r),0},{sin(r),cos(r),0},{0,0,1} };
    eetrans[0] = x, eetrans[1] = y, eetrans[2] = z;

    IkReal temp[3][3] = {{0}};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                temp[i][j] += rotX[i][k] * rotY[k][j];
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            eerot[i*3+j] = 0;
            for (int k = 0; k < 3; ++k) {
                eerot[i*3+j] += temp[i][k] * rotZ[k][j];
            }
        }
    }
}

void subwidgetforIk::trans(double theta,double alpha,double a,double d,vector<vector<double>>& T){
    T[0][0]=cos(theta);T[0][1]=-sin(theta)*cos(alpha);T[0][2]=sin(theta)*sin(alpha);T[0][3]=a*cos(theta);
    T[1][0]=sin(theta);T[1][1]=cos(theta)*cos(alpha);T[1][2]=-cos(theta)*sin(alpha);T[1][3]=a*sin(theta);
    T[2][0]=0;T[2][1]=sin(alpha);T[2][2]=cos(alpha);T[2][3]=d;
    T[3][0]=0;T[3][1]=0;T[3][2]=0;T[3][3]=1;
}

void subwidgetforIk::crossproduct(vector<double> a,vector<double> b){
    vector<double> result(3,0);
    result[0]=a[1]*b[2]-a[2]*b[1];
    result[1]=a[2]*b[0]-a[0]*b[2];
    result[2]=a[0]*b[1]-a[1]*b[0];
}

/*
void subwidgetforIk::iterate_ikine(vector<double> q_ready,double* euler,double efs,double i_max){
    vector<vector<double>> T0e(4,vector<double>(4,0));
    double *eetrans,*eerot;
    euler2matrix(euler,eetrans,eerot);
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            T0e[i][j]=eerot[3*i+j];
        }
        T0e[i][3]=eetrans[i];
    }

    vector<vector<double>> DH_0={{0,IKPI /2,0,0.0892},
                                 {0,0,-0.425,0},
                                 {0,0,-0.392,0},
                                 {0,IKPI/2,0,0.1093},
                                 {0,-IKPI/2,0,0.09475},
                                 {0,0,0,0.825}};
    vector<double> q_r(6,0),alpha(6,0),a(6,0),d(6,0);
    for(int i=0;i<6;++i){
        q_r[i]=q_ready[i]+DH_0[i][0];
        alpha[i]=DH_0[i][1];
        a[i]=DH_0[i][2];
        d[i]=DH_0[i][3];
    }
    int n=q_r.size();
    double deltaQ=1;
    int tmp_count=0;

    //while(deltaQ>efs){

    vector<vector<double>> An{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    vector< vector < vector<double> > > T(4);
    for(int i=0;i<4;++i){
        T[i].resize(4);
    }
    for(int j=0;j<4;++j){
        for (int k = 0; k < 4; k++)
        {
             T[j][k].resize(6);
        }//之后才能对三维数组设定大小，否则内存出错
    }

   for(int i=0;i<6;++i){
      vector<vector<double>> tmp{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
      trans(q_r[0],alpha[0],a[0],d[0],tmp);
      for(int j=0;j<4;++j){
         for(int k=0;k<4;++k){
               T[j][k][i]=tmp[j][k];
         }
      }
   }


        /*
        IkReal j[6]={q_r[0],q_r[1],q_r[2],q_r[3],q_r[4],q_r[5]};
        ComputeFk(j, eetrans, eerot);
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                An[i][j]=eerot[3*i+j];
            }
            An[i][3]=eetrans[i];
        }

        vector<double> dA(6,0);
        dA[0]=T0e[0][3]-An[0][3];
        dA[1]=T0e[1][3]-An[1][3];
        dA[2]=T0e[2][3]-An[2][3];
        dA[3]=0.5*(crossproduct(vector<double> {An[0][0],An[1][0],An[2][0]},vector<double> {T0e[0][0],T0e[1][0],T0e[2][0]})[0]
                +crossproduct(vector<double> {An[0][1],An[1][1],An[2][1]},vector<double> {T0e[0][1],T0e[1][1],T0e[2][1]})[0]
                +crossproduct(vector<double> {An[0][2],An[1][2],An[2][2]},vector<double> {T0e[0][2],T0e[1][2],T0e[2][2]})[0]);
        dA[4]=0.5*(crossproduct(vector<double> {An[0][0],An[1][0],An[2][0]},vector<double> {T0e[0][0],T0e[1][0],T0e[2][0]})[1]
                +crossproduct(vector<double> {An[0][1],An[1][1],An[2][1]},vector<double> {T0e[0][1],T0e[1][1],T0e[2][1]})[1]
                +crossproduct(vector<double> {An[0][2],An[1][2],An[2][2]},vector<double> {T0e[0][2],T0e[1][2],T0e[2][2]})[1]);
        dA[5]=0.5*(crossproduct(vector<double> {An[0][0],An[1][0],An[2][0]},vector<double> {T0e[0][0],T0e[1][0],T0e[2][0]})[2]
                +crossproduct(vector<double> {An[0][1],An[1][1],An[2][1]},vector<double> {T0e[0][1],T0e[1][1],T0e[2][1]})[2]
                +crossproduct(vector<double> {An[0][2],An[1][2],An[2][2]},vector<double> {T0e[0][2],T0e[1][2],T0e[2][2]})[2]);
        qDebug()<<dA[0];

    //}
}
*/

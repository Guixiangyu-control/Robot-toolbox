#ifndef SUBWIDGETFORIK_H
#define SUBWIDGETFORIK_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <vector>
#include <cmath>
#include <ccomplex>
#include <QFile>
#include <QPainter>
#include <vector>
using namespace std;
//const QString STYLE_SHEET1 = "border-image:url(%1)";
//const QString FIRST_IMAGE_PATH1 = "C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/arrow-right-filling.png";
typedef double IkReal;
namespace Ui {

class subwidgetforIk;
}

class subwidgetforIk : public QWidget
{
    Q_OBJECT


public:
    explicit subwidgetforIk(QWidget *parent = nullptr);
    ~subwidgetforIk();


    QString x;
    QString y;
    QString z;
    QString r;
    QString p;
    QString gamma;

    void euler2matrix(IkReal* euler, IkReal*eetrans, IkReal* eerot);
    void matrix2euler(IkReal*eetrans, IkReal* eerot, IkReal* euler);
    void ComputeIk(IkReal* eetrans, IkReal* eerot, IkReal(*thetaRes)[6]);
    void ComputeFk(const IkReal* j, IkReal* eetrans, IkReal* eerot);
    int inverse(const IkReal* T, IkReal* q_sols, IkReal q6_des);
    void trans(double theta,double alpha,double a,double d,vector<vector<double>>& T);
    void iterate_ikine(vector<double> q_ready,double* euler,double efs=pow(10, -12),double i_max=10000);
    void crossproduct(vector<double> a,vector<double> b);
    void paintEvent(QPaintEvent *);

signals:
    void clicked();
    void currentIndexChanged(int);

private slots:
    void onExecuate();
    void onEmpty();
    void onEmptyAll();
    void checkActiveSignal();

private:
    Ui::subwidgetforIk *ui;


};

#endif // SUBWIDGETFORIK_H

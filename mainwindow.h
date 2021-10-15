#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QLabel>
#include <QMainWindow>
#include "subsubwidgetforcartesian.h"
#include "subwidgetforik.h"
#include "setting.h"
#include "visual.h"
#include <QButtonGroup>
#include <QInputDialog>
#include "stlview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString STYLE_SHEET = "border-image:url(%1)";
const QString FIRST_IMAGE_PATH = "C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/visual.jpg";
const QString SECOND_IMAGE_PATH = "C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/inverseKinematics.jpg";
const QString THIRD_IMAGE_PATH = "C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/cartesianSpace.jpg";

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void open1();
    void open2();
    void open3();
    void open4();
    void open5();
    void exit();
    void changeQSS1();
    void changeQSS2();

protected:
    bool eventFilter(QObject *obj,QEvent *event);

private:
    Ui::MainWindow *ui;

    subwidgetforIk sub1;
    subsubwidgetforcartesian* subone1=nullptr;
    visual sub3;
    setting set;


};
#endif // MAINWINDOW_H

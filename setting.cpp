#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    setWindowTitle(tr("Interface setting"));

    pushButton1=new QPushButton("简体中文");
    pushButton2=new QPushButton("English");
    pushButton1->setParent(this);
    pushButton2->setParent(this);
    pushButton1->move(120,40);
    pushButton2->move(230,40);
}

setting::~setting()
{
    delete ui;
}

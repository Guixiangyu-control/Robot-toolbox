#include "visual.h"
#include "ui_visual.h"

visual::visual(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visual)
{
    ui->setupUi(this);

    //initializeOpenGLFunctions();
    //glClearColor(1,1,1,1);
}

visual::~visual()
{
    delete ui;
}

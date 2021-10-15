#include "robotopenglwidget.h"
#include <QColor>

//设置光照参数 使其更加立体
GLfloat lightAmbient[4] = {0.0,0.0,0.0,1.0};  //环境光
GLfloat lightDiffuse[4] = {1.0,1.0,1.0,1.0};  //漫射光
GLfloat lightPosition[4] = {1.5,1.5,2,2.0};   //光的位置
GLfloat lightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat matAmbient[4] = {0.0,0.0,0.0,1.0f};
GLfloat matDiffuse[4] = {0.0,0.0,0.0,1.0f};
GLfloat matSpecular[4] = {0.0,0.0,0.0,1.0f};
GLfloat matEmission[4] = {0.0,0.0,0.0,1.0f};
GLfloat matShininess = 50.0f;

robotOpenGLWidget::robotOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    STLView::init();

}

void robotOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(220.0/255.0, 220.0/255.0, 220.0/255.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel( GL_SMOOTH );
}

void robotOpenGLWidget::resizeGL(int w, int h)
{

}

void robotOpenGLWidget::paintGL()
{


}


#ifndef ROBOTOPENGLWIDGET_H
#define ROBOTOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_1>
#include <stlview.h>

class robotOpenGLWidget : public QOpenGLWidget,public QOpenGLFunctions_2_1
{
    Q_OBJECT
public:
    explicit robotOpenGLWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

signals:

};

#endif // ROBOTOPENGLWIDGET_H

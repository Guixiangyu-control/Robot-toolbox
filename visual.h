#ifndef VISUAL_H
#define VISUAL_H

#include <QWidget>
#include <QtOpenGL/QGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


namespace Ui {
class visual;
}

class visual : public QWidget
{
    Q_OBJECT

public:
    explicit visual(QWidget *parent = nullptr);
    ~visual();

private:
    Ui::visual *ui;
};

#endif // VISUAL_H

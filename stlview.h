#ifndef STLVIEW_H
#define STLVIEW_H
#include<QString>
#include<QVector>

class Mypoint{
public:
    double x,y,z;
};

class MyTriangle{
public:
    Mypoint normal,vertex1,vertex2,vertex3;
};

class STLView
{
public:
    static STLView* ur5View;
    static void init();
    bool readSTL(const QString &frame);
    int splitString(const QString &str, char split, QVector<QString>& strArray);
    QVector<MyTriangle> triangleVector;
};



#endif // STLVIEW_H

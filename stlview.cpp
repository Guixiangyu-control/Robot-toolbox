#include "stlview.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

STLView* STLView::ur5View = NULL;

bool STLView::readSTL(const QString &fname){
    QFile file(fname);
    if ( file.open(QFile::ReadOnly | QFile::Text))  //仅读和文字
        {
                QTextStream in( &file );
                MyTriangle triangle;
                QString line;
                int trianglePartNums = 0;

                while ( !in.atEnd() )
                {
                    line = in.readLine();
                    QVector<QString> words;

                    //分割一行，生成words字符串数组返回字符个数
                    int num = splitString(line,' ',words);

                    //解析一行
                    for(int i = 0; i < num; i++)
                    {
                        //集齐4个参数,添加一个三角片
                        if(trianglePartNums == 4)
                        {
                            triangleVector.push_back(triangle);
                            trianglePartNums = 0;
                        }
                        if(words[i] == "normal")
                        {
                            triangle.normal.x = words[i+1].toDouble();
                            triangle.normal.y = words[i+2].toDouble();
                            triangle.normal.z = words[i+3].toDouble();
                            trianglePartNums++;
                            break;
                        }
                        if(words[i] == "vertex")
                        {
                            if(trianglePartNums == 1)
                            {
                            triangle.vertex1.x = words[i+1].toDouble();
                            triangle.vertex1.y = words[i+2].toDouble();
                            triangle.vertex1.z = words[i+3].toDouble();
                            }
                            if(trianglePartNums == 2)
                            {
                            triangle.vertex2.x = words[i+1].toDouble();
                            triangle.vertex2.y = words[i+2].toDouble();
                            triangle.vertex2.z = words[i+3].toDouble();

                            }
                            if(trianglePartNums == 3)
                            {
                            triangle.vertex3.x = words[i+1].toDouble();
                            triangle.vertex3.y = words[i+2].toDouble();
                            triangle.vertex3.z = words[i+3].toDouble();
                            }
                            trianglePartNums++;
                            break;
                        }
                    }
                }
                file.close();
                //qDebug()<<"successful";
                return true;
        }
        else
        {
            qDebug() << fname << ": STL 文件打开失败";
            return false;
        }
}

int STLView::splitString(const QString &str, char split, QVector<QString>& strArray)
{
    strArray.clear();
    QString strTemp = str; //此赋值不能少
    int nIndex = 0;
    while( 1 ){
        nIndex = strTemp.indexOf(split); //QString 采用  x.indexOf(y)获取字符在字符中的位置;strTemp.Find( split )改.indexOf(split);
        if(nIndex==0){//合并分割符
            if(strTemp.length()<1)
                break;
            strTemp=strTemp.right(strTemp.length()-1);
        }
        else if( nIndex > 0 ) {
            strArray.push_back( strTemp.left( nIndex ) );
            strTemp = strTemp.right( strTemp.length() - nIndex - 1 );
        }
        else break;
    }

    //必须加判断
    if(strTemp.length() > 0)
        strArray.push_back(strTemp);//add 改pushback 好像改append也可以
    return strArray.size();
}

void STLView::init(){
    ur5View = new STLView[7];
    for(int i = 0; i < 7;i++)
    {
         ur5View[i].readSTL(QString("C:/Users/guixiangyu/Desktop/QT_CODE/robotProject/stl/%1.STL").arg(i+1));
    }

}

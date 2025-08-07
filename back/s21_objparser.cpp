#include "s21_objparser.h"

#include <QDebug>

namespace s21{
    ObjParser::ObjParser(QString fileName){
        // qDebug() << fileName;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            // qDebug() << line;

            if (!line.indexOf("v "))
                {
                    // qDebug() << line;
                    QStringList list = line.split(' ');
                    V_.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
                }
            else if (!line.indexOf("vn "))
                {
                    // qDebug() << line;
                    QStringList list = line.split(' ');
                    VN_.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
                }
            else if (!line.indexOf("vt "))
                {
                    // qDebug() << line;
                    QStringList list = line.split(' ');
                    VT_.append(QVector2D(list[1].toFloat(), list[2].toFloat()));
                }
            else if (!line.indexOf("f "))
                {
                    // qDebug() << line;

                    QVector<int> f_temp{};
                    QStringList list_temp = line.split(' ');
                    for (int i=1; i<list_temp.size(); i++)
                    {
                        // qDebug() <<"elem=" <<list_temp[i];
                        QStringList list = list_temp[i].split('/');
                        // qDebug() << "elem res = " << list[0];

                        f_temp.append(list[0].toInt()-1);
                    }
                    F_.append(f_temp);
                }
        }

    };

} /// end namespace

#ifndef S21_OBJPARSER_H
#define S21_OBJPARSER_H


#include <QString>
// #include <vector>

#include <QVector3D>
#include <QVector2D>
#include <QVector>

#include <QFile>


namespace s21{
    class ObjParser
    {
    private:
        /// https://ru.wikipedia.org/wiki/Obj
        QVector<QVector3D> V_; /// вершины
        QVector<QVector3D> VN_; /// нормали
        QVector<QVector2D> VT_; /// текстурные координаты
        QVector<QVector<int>> F_; /// грани

    public:
        ObjParser(QString fileName);
        ~ObjParser()=default;


        QVector<QVector3D> getV_(){return V_;};
        QVector<QVector3D> getVN_(){return VN_;};
        QVector<QVector2D> getVT_(){return VT_;};
        QVector<QVector<int>> getF_(){return F_;};
    };
} /// end namespace

#endif // S21_OBJPARSER_H

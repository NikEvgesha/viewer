#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <cmath>
#include <QVector3D>
#include <QVector>
#include <QMatrix4x4>

#include <QDebug>
#include <QString>

namespace s21{

    class Model
    {
    private:
        QVector<QVector3D> V_; /// вершины
        QVector<QVector<int>> F_; /// грани
        QVector<QVector3D> MovedV_;
        QVector<QVector3D> V_start; /// вершины
        QVector<QVector<int>> F_start; /// грани


        QString fileName{""};
        int scale=1; /// масштаб модели

    public:
        Model(): V_{0}, F_{0} {};

        void setVertexes(QVector<QVector3D> Vertexes){V_=Vertexes;};
        void setFace(QVector<QVector<int>> Face){F_=Face;};
        void setVertexesStart(QVector<QVector3D> Vertexes){V_start=Vertexes;};
        void setFaceStart(QVector<QVector<int>> Face){F_start=Face;};

        QVector<QVector3D> getVertexes(){return V_;};
        QVector<QVector<int>> getFace(){return F_;};

        QVector<QVector3D> getVertexesStart(){return V_start;};
        QVector<QVector<int>> getFaceStart(){return F_start;};

        void move(double x_move, double y_move, double z_move, double x_turn, double y_turn, double z_turn, int zoom);

        QString getfileName(){return fileName;}
        void setFileName(QString fileName_){fileName=fileName_;};

        void setScaleModel(float scale_);
        int getScaleModel(){return scale;};
        void setScaleToView(int viwer_height, int viewer_wight);

        void resetModel();
    };

}

#endif // S21_MODEL_H

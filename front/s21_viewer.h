#ifndef S21_VIEWER_H
#define S21_VIEWER_H

// #include <QtOpenGLWidgets/QOpenGLWidget>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
// #include <QKeyEvent> /// для кнопок

// #include "objparser.h" /// парсер моделей в формате obj
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <QLayout>

#include <QSize> /// для определения размера виджета view
#include <QLabel>

#include <QFont>

#include <QDir>

#define VIEWER_WIGHT 1550
#define VIEWER_HEIGHT 1000

enum type_top
{
    none,
    elipse,
    square
};

namespace s21{
class Viewer : public QGraphicsView{
private:
    // float scale=1;
    int center_x=VIEWER_WIGHT/2;
    int center_y=VIEWER_HEIGHT/2;

    QGraphicsScene * view;

    QPen Pen{Qt::white};
    QPen Top{Qt::white};

    struct {
        int top_w{1};
        int top_h{1};
        type_top typeTop{elipse};
    }TopData;

    int projection=1; /// 1 - паралельная 2 - центральная
    float projectionK=1.0;

public:
    Viewer(QWidget *widget);
    void drawCoordsLine(float scale);

    void centr_move(QVector<QVector3D> V_, int sc);
    void paint(QVector<QVector3D> V_, QVector<QVector<int>> F_, double sc=1);

    void setPen(QPen Pen_){Pen=Pen_;};
    QPen getPen(){return Pen;};

    void setTop(QPen Top_){Top=Top_;};
    QPen getTop(){return Top;};
    int getTopType(){
        int res(0);
        if (TopData.typeTop == elipse)
            res=1;
        else if (TopData.typeTop == square)
            res = 2;
        else if (TopData.typeTop == none)
            res = 3;
        return res;
    };
    int getTop_w(){return TopData.top_w;};
    void setTop_w_h(int w){
        TopData.top_w=w;
        TopData.top_h=w;
    };

    void setTopData(int top_w_=1, int top_h_=1, type_top typeTop_=elipse){
        TopData.top_h=top_h_;
        TopData.top_w=top_w_;
        TopData.typeTop=typeTop_;
    };
    int getTopData_w(){return TopData.top_w;};
    int getTopData_h(){return TopData.top_h;};
    type_top getTopData_typeTop(){return TopData.typeTop;};

    // float getscale(){return scale;};
    // void setscale(float scale_){scale=scale_;};

    void setProjection(int pr){projection = pr;};
    int getProjection(){return projection;};

    void setprotectionK(float k_) {projectionK=k_;};
    float getprotectionK() {return projectionK;};

    };
} /// end namespace

#endif // S21_VIEWER_H

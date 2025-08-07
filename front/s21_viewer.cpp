#include "s21_viewer.h"

namespace s21{
    Viewer::Viewer(QWidget *widget) {
        view = new QGraphicsScene(widget);

        view->setSceneRect(0,0,VIEWER_WIGHT*1.05,VIEWER_HEIGHT);

        // view->addRect(0,0,VIEWER_WIGHT,VIEWER_HEIGHT, QPen(Qt::white));

        setScene(view);

        // устанавливаем настройки с прошлого раза (если файл есть)
        QString fileSettingsName = QDir::homePath()+"/AppSettings.txt";
        QFile fileSettings(fileSettingsName);
        if (!fileSettings.exists())
        {
            view->setBackgroundBrush(QBrush(Qt::black));
        }
        else
        {
            fileSettings.open(QIODevice::ReadOnly);
            QString bkgrndFileName = {""};
            QStringList PenFromFile = {""}, TopFromFile = {""}, ProtectionFromFile={""};

            while(!fileSettings.atEnd())
            {
                QString line = fileSettings.readLine();
                if (!line.indexOf("BackgroundView "))
                {
                    bkgrndFileName = line.split(' ')[1];
                    if (bkgrndFileName[bkgrndFileName.size() -1]=='\n')
                        bkgrndFileName.resize(bkgrndFileName.size() -1); /// удаляем перенос строки \n
                }
                else if (!line.indexOf("Pen "))
                {
                    PenFromFile = line.split(" ");

                    QString &lastElem = PenFromFile[PenFromFile.size() - 1];
                    if (lastElem[lastElem.size()-1]=='\n')
                    {
                        lastElem.resize(lastElem.size() -1); /// удаляем перенос строки \n
                    }

                    Pen.setStyle(PenFromFile[1]=="1"? Qt::SolidLine : Qt::DashLine);
                    Pen.setColor(QColor(PenFromFile[3].toInt(), PenFromFile[4].toInt(), PenFromFile[5].toInt(), PenFromFile[2].toInt()));
                    Pen.setWidth(PenFromFile[6].toInt());
                }
                else if (!line.indexOf("Top "))
                {

                    TopFromFile = line.split(" ");

                    QString &lastElem = TopFromFile[TopFromFile.size() - 1];
                    if (lastElem[lastElem.size()-1]=='\n')
                    {
                        lastElem.resize(lastElem.size() -1); /// удаляем перенос строки \n
                    }

                    if (TopFromFile[1]=="1")
                        TopData.typeTop=elipse;
                    else if (TopFromFile[1]=="2")
                        TopData.typeTop=square;
                    else if (TopFromFile[1]=="3")
                        TopData.typeTop=none;

                    Top.setColor(QColor(TopFromFile[3].toInt(), TopFromFile[4].toInt(), TopFromFile[5].toInt(), TopFromFile[2].toInt()));
                    TopData.top_h=TopFromFile[6].toInt();
                    TopData.top_w=TopFromFile[6].toInt();

                }
                else if (!line.indexOf("Projection "))
                {
                    ProtectionFromFile = line.split(" ");

                    QString &lastElem = ProtectionFromFile[ProtectionFromFile.size() - 1];
                    if (lastElem[lastElem.size()-1]=='\n')
                    {
                        lastElem.resize(lastElem.size() -1); /// удаляем перенос строки \n
                    }

                    projection= ProtectionFromFile[1]=="1"? 1:2;
                    if (projection==2)
                        projectionK=ProtectionFromFile[2].toFloat();
                }
            }
            fileSettings.close();
            view->setBackgroundBrush(QImage(bkgrndFileName));
        }

        drawCoordsLine(1);
    }

    void Viewer::drawCoordsLine(float scale){
        view->addRect(5,5,10,10, Pen);
        view->addLine(5,5,100,5, Pen);
        view->addLine(5,5,5,100, Pen);
        QGraphicsTextItem * W_ = view->addText(QString::number(VIEWER_WIGHT/scale, 'f', 0));
        QGraphicsTextItem * H_ = view->addText(QString::number(VIEWER_HEIGHT/scale, 'f', 0));
        W_->setPos(60,5);
        H_->setPos(5,100);
        H_->setRotation(270);
    };


    void  Viewer::centr_move(QVector<QVector3D> V_, int sc){

        float x_max(V_[0].x()), y_max(V_[0].y()), z_max(V_[0].z()), x_min(V_[0].x()), y_min(V_[0].y()), z_min(V_[0].z());
            for (QVector3D top : V_) {
                if (top.x()>x_max)
                    x_max=top.x();
                if (top.y()>y_max)
                    y_max=top.y();
                if (top.z()>z_max)
                    z_max=top.z();

            if (top.x()<x_min)
                x_min=top.x();
            if (top.y()<y_min)
                y_min=top.y();
            if (top.z()<z_min)
                z_min=top.z();
        }


        center_x=VIEWER_WIGHT/2 + (x_max+x_min)*sc/2;
        center_y=VIEWER_HEIGHT/2 + (y_max+y_min)*sc/2; /// центр экрана viewer + центруем фигуру
    };

    void Viewer::paint(QVector<QVector3D> V_, QVector<QVector<int>> F_, double scale){
        // qDebug() << "projection = " << projection;

        if (projection==1)
        {
            /// По умолчанию всегда будет паралельный тип проекции
            view->clear();

            QBrush br = Top.color();

            for (QVector3D top : V_) {
                if (TopData.typeTop==elipse)
                    view->addEllipse(center_x-TopData.top_w/2 - top.x() * scale, center_y- TopData.top_w/2 - top.y() * scale, TopData.top_w, TopData.top_h, Top, br);
                else if (TopData.typeTop==square)
                    view->addRect(center_x - TopData.top_w/2 - top.x() * scale, center_y -TopData.top_w/2 - top.y() * scale, TopData.top_w, TopData.top_h, Top, br);
                else if (TopData.typeTop==none)
                    continue;
            }

            for (auto face : F_) {
                for (auto i = 0; i < face.size(); ++i) {
                    int v1 = face[i];
                    int v2 = face[(i+1) % face.size()];
                    view->addLine(center_x - V_[v1].x() * scale, center_y - V_[v1].y() * scale, center_x - V_[v2].x() * scale, center_y - V_[v2].y() * scale, Pen);
                }
            }
        }
        else
        {
            view->clear();

            QVector<QVector3D> new_V_;

            for (QVector3D top : V_) {
                float x_ = top.x() * projectionK / (top.z() + projectionK);
                float y_ = top.y() * projectionK / (top.z() + projectionK);

                new_V_.append(QVector3D(x_, y_, top.z())); /// вот про то, что должна быть новый вектор подсказал мне жпт


                if (TopData.typeTop==elipse)
                    view->addEllipse(center_x - x_ * scale, center_y - y_ * scale, TopData.top_w, TopData.top_h, Top);
                else if (TopData.typeTop==square)
                    view->addRect(center_x - x_ * scale, center_y - y_ * scale, TopData.top_w, TopData.top_h, Top);
                else if (TopData.typeTop==none)
                    continue;
            }

            for (auto face : F_) {
                for (auto i = 0; i < face.size(); ++i) {
                    int v1 = face[i];
                    int v2 = face[(i+1) % face.size()];
                    view->addLine(center_x - new_V_[v1].x() * scale, center_y - new_V_[v1].y() * scale, center_x - new_V_[v2].x() * scale, center_y - new_V_[v2].y() * scale, Pen);
                }
            }
        }
        drawCoordsLine(scale);
    };


} /// end namespace

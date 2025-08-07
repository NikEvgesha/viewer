#include "s21_panelinformation.h"

namespace s21{
    panelInformation::panelInformation() {

        infoF = new QLabel(this);
        layout = new QHBoxLayout(this);

        layout->addWidget(infoF);

        this->setMinimumSize(INFO_WIGHT,INFO_HEIGHT);
        this->setMaximumHeight(INFO_HEIGHT*2);
        this->setStyleSheet("background-color: black; color: white;");

        this->setLayout(layout);
    }

    void panelInformation::drawInformation(QString fileName, QVector<QVector3D> V_, QVector<QVector<int>> F_, double scale){
        // qDebug() << "Scale = " << scale;

        QFile file(fileName);
        QString infoFile = "Имя файла - " +fileName + "\nКоличество вершин в модели = "
                           + QString::number(V_.size()) + "\nКоличество граней в модели = " + QString::number(F_.size())
                           + "\nРазмер файла - " + QString::number(file.size()) + " Байт\n"
                           + "Масштаб модель - визуализация: " + QString::number(scale);

        // qDebug() << "ScaleInfo = " << infoFile;

        infoF->setText(infoFile);
    };

}

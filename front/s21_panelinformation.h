#ifndef S21_PANELINFORMATION_H
#define S21_PANELINFORMATION_H

#include <QString>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#define INFO_WIGHT 1550
#define INFO_HEIGHT 95

namespace s21{
    class panelInformation: public QWidget
    {
    private:
        QLabel *infoF=nullptr;
        QHBoxLayout * layout = nullptr;
        panelInformation * infoPanel=nullptr;
    public:
        panelInformation();
        void drawInformation(QString fileName, QVector<QVector3D> V_, QVector<QVector<int>> F_, double scale);
    };
}

#endif // S21_PANELINFORMATION_H

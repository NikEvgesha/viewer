#ifndef S21_TOOLBAR_H
#define S21_TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QToolBar>
#include <QString>

#include <QFileDialog>

#include <back/s21_objparser.h>
#include <back/s21_model.h>
#include <s21_viewer.h>
#include <s21_panelinformation.h>
#include <s21_transformation.h>

#include <QMessageBox>

#include <QTimer>
#include "3rdParty/gifimage/qgifimage.h"

#include <QApplication>
#include <QPushButton>
#include <QColor>

#include <QInputDialog>

namespace s21{

class Viewer;

    class toolBar: public QWidget
    {
    private:
        Viewer *view=nullptr;
        Model* model=nullptr;
        panelInformation * infoPanel=nullptr;

        bool fileIsLoaded{false};

        QGifImage *gif=nullptr; /// итоговая гифка
        QTimer *timerForGif=nullptr; /// таймер для отсчета 100 мсек
    public:
        toolBar(Viewer *view_, Model* model_, panelInformation * infoPanel_, QWidget* desktop_);
        QAction * createButtonToolBar(QString helpText, QString iconDir, QToolBar &MenuToolbar);
        QToolBar * createSpacerToolBar(QString helpText, QSizePolicy h, int width=0);

        void openFile();
        bool checkFileType(QString fileName);
        void centAndScale();
        void centrView();
        void startPosModel();
        void changeProjection();
        void saveAs();
        void gifStartrecording();
        void saveAsGif();

        void changeBackGroundApp(QWidget * desktop_);
        void applychangeBackgroundApp(QString fileName, QWidget * widget);
        void saveInFileSettings(QString string1, QString string2);
        void changeBackGroundView();
        void PenSettings();
        void setTypePen();
        void applyTypePen(QString text_, QWidget * setTypePenW);
        void setColorPen();
        void applyColorPenW(QColor color, QWidget * setColorPenW);
        void setWightPen();
        void TopSettings();
        void setTypeTop();
        void applyTopType(type_top typeTop_, QWidget * setTypeTopW);
        void setColorTop();
        void applyColorTop(QColor color_, QWidget * setColorTopW);
        void SetWightTop();

    };
}

#endif // S21_TOOLBAR_H

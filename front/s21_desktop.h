#ifndef S21_DESKTOP_H
#define S21_DESKTOP_H

#include <QWidget>

#include <QPalette> /// для установки фона
#include <QPixmap> /// для установки фона

#include <QMenu>
#include <QMenuBar>
#include <QAction> /// для менюБара и ТулБара

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>

#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QMessageBox>

#include <QGraphicsScene>

// #include <back/s21_objparser.h>
#include <s21_viewer.h>
#include <s21_transformation.h>
#include <s21_panelinformation.h>
#include <s21_toolbar.h>
#include <back/s21_model.h>

#include <QToolBar>
// #include <QItem>

#include <QInputDialog>

// #include <QTimer>

// #include "3rdParty/gifimage/qgifimage.h"

#define VIEWER_WIGHT 1550
#define VIEWER_HEIGHT 1000

namespace s21{

// class Viewer;  ///< объявил тут, чтобы можно было работать с ним в десктопе сразу

class desktop : public QWidget
{
public:
    desktop(const desktop&) = delete;
    ~desktop() {instance = nullptr;};

    static desktop& getInstance();

    void setAppStyle(); /// установка стиля приложения
    void createMenuBar(); /// установка менюБар
    void AboutIt(); /// окно о программе

private:
    desktop();

    static desktop * instance;

    Viewer *view=nullptr;
    Model* model=nullptr;
    transformation * transformationMenu=nullptr;
    panelInformation * infoPanel=nullptr;
    toolBar * toolBarMenu = nullptr;

    bool fileIsLoaded{false};
};

} /// end namespace

#endif // S21_DESKTOP_H

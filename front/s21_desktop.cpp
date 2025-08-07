#include "s21_desktop.h"


#define APP_WIGHT 2000
#define APP_HEIGHT 1220


namespace s21{
    desktop::desktop() {
        setAppStyle();
        createMenuBar();

        view = new Viewer(this);
        model = new Model();
        transformationMenu = new transformation(model, view);
        infoPanel = new panelInformation();
        toolBarMenu = new toolBar(view, model, infoPanel, this);


        QVBoxLayout *layout = new QVBoxLayout(this); /// создали вертикальный слой
        QHBoxLayout *layoutVieAndTrandformation = new QHBoxLayout(); /// создали вертикальный слой

        layoutVieAndTrandformation->addWidget(transformationMenu);
        layoutVieAndTrandformation->addWidget(view);


        layout->addWidget(toolBarMenu);
        layout->addLayout(layoutVieAndTrandformation);
        layout->addWidget(infoPanel);

        setLayout(layout);
    }

    void desktop::setAppStyle(){
        this->setWindowTitle("3DViewer_v2.0");
        this->resize(APP_WIGHT, APP_HEIGHT); /// устанавливаем размеры приложения

        /// устанавливаем минимальные и максималные размеры приложения
        this->setMinimumHeight(APP_HEIGHT/5);
        this->setMinimumWidth(APP_WIGHT/5);
        this->setMaximumHeight(APP_HEIGHT*5);
        this->setMaximumWidth(APP_WIGHT*5);

        /// устанока фона приложения по умолчанию (https://stackoverflow.com/questions/19939938/how-do-i-add-a-background-image-to-the-qmainwindow)
        QString fileSettingsName = QDir::homePath()+"/AppSettings.txt";

        QFile fileSettings(fileSettingsName);
        if (!fileSettings.exists())
        {
            QPixmap bkgrnd(this->size());
            bkgrnd.fill(Qt::white); /// по умолчанию - белый

            // bkgrnd.scaled(this->size());
            QPalette palette;
            palette.setBrush(QPalette::Window, bkgrnd);
            this->setPalette(palette);
        }
        else
        {
            // qDebug()<<"устанавливаем фон";
            fileSettings.open(QIODevice::ReadOnly);
            QString bkgrndFileName = {""};

            while(!fileSettings.atEnd())
            {
                QString line = fileSettings.readLine();
                if (!line.indexOf("BackgroundApp "))
                {
                    bkgrndFileName = line.split(' ')[1];
                    if (bkgrndFileName[bkgrndFileName.size() -1]=='\n')
                        bkgrndFileName.resize(bkgrndFileName.size() -1); /// удаляем перенос строки \n
                }
            }
            fileSettings.close();
            // qDebug()<<"файл фона = " << bkgrndFileName;
            // applychangeBackgroundApp(bkgrndFileName, this);
            if (!QFile::exists(bkgrndFileName))
            {
                // qDebug()<<"файл фона не найден";
                return;
            }
            QPixmap bkgrnd(bkgrndFileName);
            QPalette palette;
            palette.setBrush(QPalette::Window, bkgrnd);
            this->setPalette(palette);
        }

    }

    void desktop::createMenuBar(){
        /// На линуксе не красиво выглядит большой менюБар. все сократил.
        /// читал тут https://www.opennet.ru/docs/RUS/qt3_prog/x1389.html

        /// создали менюБар
        QMenuBar * menuBar = new QMenuBar(this);

        /// создали подменю
        QMenu *menuAboutIt = new QMenu(tr("Справка"),this);

        /// добавили кнопки в подменю
        QAction * Quit = new QAction(tr("Выход"),this);

        QAction * AboutApp = new QAction(tr("О программе"),this);
        menuAboutIt->addAction(AboutApp);
        menuAboutIt->addAction(Quit);

        /// добавили подменю в менюБар
        menuBar->addMenu(menuAboutIt);

        connect(AboutApp, &QAction::triggered, this, &desktop::AboutIt);
        connect(Quit, &QAction::triggered, this, &desktop::close);
    }

    void desktop::AboutIt(){
        /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Внимание!");
        msgBox->setText("Даный проект сделан командрой \"Тяп-ляп Production\". \n\nСтиль выполнения так-сяк. \nОценку максимальную, пожалуйста. \n\n\n\nп.с. Спасибо, что заглянули сюда.");
        msgBox->setIcon(QMessageBox::Information);
        msgBox->exec();
        fileIsLoaded=false;
    }


    desktop& desktop::getInstance() {
        if (!instance) {
            instance = new desktop();
        }

        return *instance;
    }



} /// end namespace

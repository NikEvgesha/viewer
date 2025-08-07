#include "s21_toolbar.h"

namespace s21{
    toolBar::toolBar(Viewer *view_, Model* model_, panelInformation * infoPanel_, QWidget* desktop_) {
        view=view_;
        model=model_;
        infoPanel=infoPanel_;
        /// создали горизонтальный слой для меню ТулБар
        QHBoxLayout *HorizLayout = new QHBoxLayout();

        /// создали менюТул File
        QToolBar * MenuToolbar = new QToolBar(tr("File"), this);
        HorizLayout->addWidget(MenuToolbar); /// добавили в горизонтальный слой
        QAction * OpenFile = createButtonToolBar("Открыть файл", ":/icons/resources/Icons/free-icon-open-folder-5082610.png", *MenuToolbar);
        QAction * centrAndScale = createButtonToolBar("Центрирование и масштабирование модели на экран", ":/icons/resources/Icons/free-icon-expand-square-interface-button-of-two-arrows-54269.png", *MenuToolbar);
        QAction * centrView = createButtonToolBar("Центрирование модели на экран", ":/icons/resources/Icons/free-icon-scan-11450605.png", *MenuToolbar);
        QAction * startPosModel = createButtonToolBar("Вернуть изначальное состояние модели", ":/icons/resources/Icons/free-icon-route-1023368.png", *MenuToolbar);
        QAction * setProjection = createButtonToolBar("Выбор типа проекции", ":/icons/resources/Icons/free-icon-projection-10433829.png", *MenuToolbar);
        QAction * SaveAs = createButtonToolBar("Сделать скриншот экрана", ":/icons/resources/Icons/free-icon-capture-8428668.png", *MenuToolbar);
        QAction * GifStartrecording = createButtonToolBar("Сделать gif-анимацию", ":/icons/resources/Icons/free-icon-gif-2441627.png", *MenuToolbar);
        QAction * Exit = createButtonToolBar("Та самая дверь", ":/icons/resources/Icons/free-icon-person-9924325.png", *MenuToolbar);
        QToolBar * MenuToolbarSpacer = createSpacerToolBar("Spacer", QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred), 50);
        MenuToolbar->addWidget(MenuToolbarSpacer);

        QToolBar * MenuToolbar2 = new QToolBar(tr("setColor"), this);
        HorizLayout->addWidget(MenuToolbar2); /// добавили в горизонтальный слой
        QAction * changeBackGroundApp = createButtonToolBar("Изменить фон приложения", ":/icons/resources/Icons/free-icon-mountain-range-on-black-background-61103.png", *MenuToolbar2);
        QAction * changeBackGroundView = createButtonToolBar("Изменить фон рабочего стола", ":/icons/resources/Icons/free-icon-background-10134012.png", *MenuToolbar2);
        QAction * PenSettings = createButtonToolBar("Изменить настройки линий", ":/icons/resources/Icons/free-icon-pencil-1166723.png", *MenuToolbar2);
        QAction * TopSettings = createButtonToolBar("Изменить настройки вершин", ":/icons/resources/Icons/free-icon-map-point-5817230.png", *MenuToolbar2);

        /// создали менюТул ПУстой
        QToolBar * MenuToolbarSpacer2 = new QToolBar(tr("Spacer"), this);
        MenuToolbarSpacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        HorizLayout->addWidget(MenuToolbarSpacer2); /// добавили в горизонтальный слой

        /// Делаем прозрачный фон у меню ТулБар
        MenuToolbar->setStyleSheet("border: none;");
        MenuToolbar2->setStyleSheet("border: none;");
        MenuToolbarSpacer2->setStyleSheet("border: none;");

        this->setLayout(HorizLayout);

        connect(OpenFile, &QAction::triggered, this, &toolBar::openFile);
        connect(centrAndScale, &QAction::triggered, this, &toolBar::centAndScale);
        connect(centrView, &QAction::triggered, this, &toolBar::centrView);
        connect(startPosModel, &QAction::triggered, this, &toolBar::startPosModel);
        connect(setProjection, &QAction::triggered, this, &toolBar::changeProjection);
        connect(SaveAs, &QAction::triggered, this, &toolBar::saveAs);
        connect(GifStartrecording, &QAction::triggered, this, &toolBar::gifStartrecording);
        connect(Exit, &QAction::triggered, qApp, &QApplication::quit);

        connect(changeBackGroundApp, &QAction::triggered, this, [this, desktop_](){this->changeBackGroundApp(desktop_);});
        connect(changeBackGroundView, &QAction::triggered, this, &toolBar::changeBackGroundView);
        connect(PenSettings, &QAction::triggered, this, &toolBar::PenSettings);
        connect(TopSettings, &QAction::triggered, this, &toolBar::TopSettings);
    }

    QAction * toolBar::createButtonToolBar(QString helpText, QString iconDir, QToolBar &MenuToolbar){
        QAction * button = new QAction(helpText);
        button->setIcon(QIcon(iconDir));
        MenuToolbar.addAction(button);

        return button;

    }

    QToolBar * toolBar::createSpacerToolBar(QString helpText, QSizePolicy h, int width){
        QToolBar * Spacer = new QToolBar(helpText, this);
        Spacer->setFixedWidth(width);
        if (width)
            Spacer->setSizePolicy(h);

        return Spacer;
    }


    void toolBar::openFile(){
        QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath());
            if (checkFileType(fileName)){
                ObjParser * obj = new ObjParser(fileName);
                QString newName = "3DViewer_v2.0   ";
                newName.append(fileName);
                this->setWindowTitle(newName);

                model->setFileName(fileName);

                QVector<QVector<int>> Face=obj->getF_();
                QVector<QVector3D> Vertexes = obj->getV_();
                model->setVertexes(Vertexes);
                model->setFace(Face);

                model->setVertexesStart(Vertexes);
                model->setFaceStart(Face);

                view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
                infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
                fileIsLoaded=true;
            }
            else
            {
                /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
                QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setWindowTitle("Внимание!");
                msgBox->setText("Выбран файл некоррректного формата.\nбудьте любезны только формат .obj");
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->exec();
                fileIsLoaded=false;
            }
    }

    bool toolBar::checkFileType(QString fileName){
        bool res = true;
        QList<QString> listName = fileName.split('.');
        if (listName[listName.size()-1].toLower()!="obj")
            res = false;
        return res;
    };

    void toolBar::centAndScale(){
        if(fileIsLoaded)
        {
            model->setScaleToView(VIEWER_HEIGHT, VIEWER_WIGHT);
            view->centr_move(model->getVertexes(), model->getScaleModel());
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
        }
    }

    void toolBar::centrView(){
    if(fileIsLoaded)
        {
            view->centr_move(model->getVertexes(), model->getScaleModel());
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
        }
    }

    void toolBar::startPosModel()
    {
        model->resetModel();
        centrView();
        view->paint(model->getVertexesStart(), model->getFaceStart(), 1);
        infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
    }

    void toolBar::changeProjection(){
        // qDebug() <<"projection";
        QWidget * changePr = new QWidget();
        changePr->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        changePr->setWindowTitle("Изменение типа проекции");
        QVBoxLayout *changePrLayout = new QVBoxLayout(changePr);

        QPushButton *button1 = new QPushButton("Паралельная (привычная нам)");
        button1->setFixedHeight(60);
        button1->setStyleSheet("color: black");

        QPushButton *button2 = new QPushButton("Центральная (мутотень)");
        button2->setFixedHeight(60);
        button2->setStyleSheet("color: black");

        changePrLayout->addWidget(button1);
        changePrLayout->addWidget(button2);

        connect(button1, &QPushButton::clicked, this, [this](){
            view->setProjection(1);
            saveInFileSettings("Projection ", "1");
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
        });
        connect(button2, &QPushButton::clicked, this, [this](){
            view->setProjection(2);

            bool ok{};
            QString text = QInputDialog::getText(this, tr("Ввод расстояния до фигуры"),
                                                 tr("   Укажите трасстояние до фигуры,\n целое или вещественное число:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                if (!text.toFloat())
                {
                    /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
                    QMessageBox *msgBox = new QMessageBox(this);
                    msgBox->setWindowTitle("Внимание!");
                    msgBox->setText("Введены некорректные данные.\nБудьте любезны только целое или вещественное число");
                    msgBox->setIcon(QMessageBox::Warning);
                    msgBox->exec();
                }
                else
                {
                    saveInFileSettings("Projection ", "2 " + text);
                    view->setprotectionK(text.toFloat());
                    view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
                    infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
                }
            }

        });

        changePr->show();
    }

    void toolBar::saveAs(){
        QPixmap screenshot = view->grab();
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как ..."), "", tr("Картинка (*.jpg *.bmp);;All Files (*)"));
        QList<QString> list = fileName.split('.');
        // qDebug() << "разрешение файла = "<<list[list.size()-1];
        // qDebug() << "Имя файла" << fileName;

        if (fileName.isEmpty())
        {
            /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Внимание!");
            msgBox->setText("Нужно указать имя файла");
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->exec();
        }
        else if (list[list.size()-1] != "bmp" && list[list.size()-1] != "jpg")
        {
            /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Внимание!");
            msgBox->setText("Формат файла должен быть bmp или jpg");
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->exec();
        }
        else
            screenshot.save(fileName);
    }

    void toolBar::gifStartrecording(){
        /// https://stackoverflow.com/questions/10713691/i-am-trying-to-save-qimage-with-gif-format
        /// https://github.com/dbzhang800/QtGifImage - делал по второму пути немного помучившись
        /// https://github.com/dbzhang800/QtGifImage/blob/master/examples/gifimage/extractFrames/main.cpp - делал по этому примеру из той же библиотеки

        gif = new QGifImage();

        QVector<QRgb> ctable;
        ctable << qRgb(255, 255, 255)
               << qRgb(0, 0, 0)
               << qRgb(255, 0, 0)
               << qRgb(0, 255, 0)
               << qRgb(0, 0, 255)
               << qRgb(255, 255, 0)
               << qRgb(0, 255, 255)
               << qRgb(255, 0, 255);

        gif->setFrameDelay(640, 480);
        gif->setGlobalColorTable(ctable, Qt::black);
        gif->setDefaultTransparentColor(Qt::black);
        gif->setDefaultDelay(100); /// 100 мс между кадрами = 10 кадров в секунду = 10фпс

        timerForGif = new QTimer(this);
        /// делаем кога таймер кончится
        connect(timerForGif, &QTimer::timeout, this, [this](){
            QImage image = view->grab().toImage();
            gif->addFrame(image);
        });
        timerForGif->start(100);

        /// делаем когда таймер набере 5секун (5000 мс)
        QTimer::singleShot(5000, this, &toolBar::saveAsGif);

    }

    void toolBar::saveAsGif(){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить gif как ..."), "", tr("Gif-анимация (*.gif);;All Files (*)"));
        QList<QString> list = fileName.split('.');
        if (fileName.isEmpty())
        {
            /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Внимание!");
            msgBox->setText("Нужно указать имя файла");
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->exec();
        }
        else if (list[list.size()-1] != "gif")
        {
            /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Внимание!");
            msgBox->setText("Формат файла должен быть gif");
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->exec();
        }
        else
            gif->save(fileName);

    }

    void toolBar::changeBackGroundApp(QWidget * desktop_){


        QWidget * changeBackground = new QWidget();
        changeBackground->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        changeBackground->setWindowTitle("Изменение фона приложения");

        QPushButton *button = new QPushButton("Выберите файл с изображением");
        button->setFixedHeight(60);
        button->setStyleSheet("color: black");

        /// Создаем слой для размещения кнопки
        QVBoxLayout *changeBackGroundAppLayout = new QVBoxLayout(changeBackground);

        changeBackGroundAppLayout->addWidget(button);

        connect(button, &QPushButton::clicked, this, [this, changeBackground, desktop_](){
            /// тут посмотрел https://www.youtube.com/watch?v=JX3j-JycMVE
            QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath());

            applychangeBackgroundApp(fileName, desktop_);

            saveInFileSettings("BackgroundApp ", fileName);

            changeBackground->close();
        });

        changeBackground->show();

    };

    void toolBar::applychangeBackgroundApp(QString fileName, QWidget * widget){
        // qDebug()<<"файл фона = " << fileName;
        if (!QFile::exists(fileName))
        {
            // qDebug()<<"файл фона не найден";
            return;
        }
        QPixmap bkgrnd(fileName);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgrnd);
        widget->setPalette(palette);
    }

    void toolBar::saveInFileSettings(QString string1, QString string2){
        /// ничего лучше не придумал. прочитали, сохранили в лист нужное, удалил файл, записали файл с сохраненным и новой строкой фона приложения
        QString fileSettingsName = QDir::homePath()+"/AppSettings.txt";

        QFile fileSettings(fileSettingsName);
        if (!fileSettings.exists())
        {
            /// https://www.cyberforum.ru/qt/thread933858.html
            /// https://ru.stackoverflow.com/questions/834850/Запись-текста-в-qfile
            fileSettings.open(QIODevice::WriteOnly | QIODevice::Append);
            QString resText = string1 + string2 + "\n";

            QTextStream out(&fileSettings);
            out << resText;

            fileSettings.close();
        }
        else
        {
            fileSettings.open(QIODevice::ReadOnly);

            QStringList resTextList={""};
            while(!fileSettings.atEnd())
            {
                QString line = fileSettings.readLine();

                if (line.indexOf(string1))
                {
                    resTextList.append(line);
                    if (line[line.size()-1]!='\n')
                        resTextList.append("\n");
                }
            }
            fileSettings.remove();
            fileSettings.close();

            fileSettings.open(QIODevice::WriteOnly | QIODevice::Append);

            for (QString line:resTextList)
            {
                QTextStream out(&fileSettings);
                out << line;
            }

            QString bkgndText = string1 + string2 + "\n";
            QTextStream out(&fileSettings);
            out << bkgndText;

            fileSettings.close();
        }
    }

    void toolBar::changeBackGroundView(){

        QWidget * changeBackground = new QWidget();
        changeBackground->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки


        changeBackground->setWindowTitle("Изменение фона рабочего стола");

        QPushButton *button = new QPushButton("Выберите файл с изображением");
        button->setFixedHeight(60);
        button->setStyleSheet("color: black");


        /// Создаем слой для размещения кнопки
        QVBoxLayout *changeBackGroundAppLayout = new QVBoxLayout(changeBackground);
        changeBackGroundAppLayout->addWidget(button);

        connect(button, &QPushButton::clicked, this, [this, changeBackground](){
            /// тут посмотрел https://www.youtube.com/watch?v=JX3j-JycMVE
            QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath());
            view->setBackgroundBrush(QImage(fileName));

            saveInFileSettings("BackgroundView ", fileName);
            changeBackground->close();
        });

        changeBackground->show();
    };

    void toolBar::PenSettings(){
        QWidget * PenSettings = new QWidget();
        PenSettings->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        PenSettings->setWindowTitle("Изменение параментов линий");
        QVBoxLayout *PenSettingsLayout = new QVBoxLayout(PenSettings);

        QPushButton *button1 = new QPushButton("Выберите тип линий (сплошная, пунктирная)");
        button1->setFixedHeight(60);
        button1->setStyleSheet("color: black");

        QPushButton *button2 = new QPushButton("Выберите цвет линии");
        button2->setFixedHeight(60);
        button2->setStyleSheet("color: black");

        QPushButton *button3 = new QPushButton("Выберите толщину линии");
        button3->setFixedHeight(60);
        button3->setStyleSheet("color: black");


        PenSettingsLayout->addWidget(button1);
        PenSettingsLayout->addWidget(button2);
        PenSettingsLayout->addWidget(button3);

        connect(button1, &QPushButton::clicked, this, &toolBar::setTypePen);
        connect(button2, &QPushButton::clicked, this, &toolBar::setColorPen);
        connect(button3, &QPushButton::clicked, this, &toolBar::setWightPen);

        PenSettings->show();
    }

    void toolBar::setTypePen(){
        QWidget * setTypePenW = new QWidget();
        setTypePenW->setMinimumWidth(350);
        setTypePenW->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        setTypePenW->setWindowTitle("Выберите тип линии");

        QHBoxLayout *setTypePenPanel = new QHBoxLayout(setTypePenW);

        QPushButton *type1 = new QPushButton();
        type1->setFixedSize(150,60);
        type1->setText("Сплошная линия");

        QPushButton *type2 = new QPushButton();
        type2->setFixedSize(150,60);
        type2->setText("Пунктирная линия");

        setTypePenPanel->addWidget(type1);
        setTypePenPanel->addWidget(type2);

        connect(type1, &QPushButton::clicked, this, [this, setTypePenW](){applyTypePen("1 ", setTypePenW );});
        connect(type2, &QPushButton::clicked, this, [this, setTypePenW](){applyTypePen("2 ", setTypePenW );});

        setTypePenW->show();

    }

    void toolBar::applyTypePen(QString text_, QWidget * setTypePenW)
    {
        QPen tempPen = view->getPen();
        if (text_=="1 ")
            tempPen.setStyle(Qt::SolidLine);
        else if (text_=="2 ")
            tempPen.setStyle(Qt::DashLine);
        view->setPen(tempPen);

        /// 1 - solidLind (2 - DashLline)
        /// 1 2 3 4 - цвет
        /// 1 - толщина
        /// ничего лучше не придумал
        QString text = text_ + QString::number(tempPen.color().alpha()) + " " + QString::number(tempPen.color().red()) +
                       " " + QString::number(tempPen.color().green()) + " " + QString::number(tempPen.color().blue()) +
                       " " + QString::number(tempPen.width());

        saveInFileSettings("Pen ", text);
        if (fileIsLoaded)
        {
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
            fileIsLoaded=true;
        }
        setTypePenW->close();
    }

    void toolBar::setColorPen(){
        QWidget * setColorPenW = new QWidget();
        setColorPenW->setMinimumWidth(350);
        setColorPenW->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        setColorPenW->setWindowTitle("Выберите цвет линии");

        QHBoxLayout *setColorPenPanel = new QHBoxLayout(setColorPenW);

        QVBoxLayout *setColorPenLEFT = new QVBoxLayout();

        QPushButton *color1 = new QPushButton();
        color1->setFixedSize(40,40);
        color1->setStyleSheet("background-color: black; border: 1 px solid black;");

        QPushButton *color2 = new QPushButton();
        color2->setFixedSize(40,40);
        color2->setStyleSheet("background-color: red; border: 1 px solid black");

        QPushButton *color3 = new QPushButton();
        color3->setFixedSize(40,40);
        color3->setStyleSheet("background-color: yellow; border: 1 px solid black;");

        setColorPenLEFT->addWidget(color1);
        setColorPenLEFT->addWidget(color2);
        setColorPenLEFT->addWidget(color3);

        QVBoxLayout *setColorPenRIGHT = new QVBoxLayout();

        QPushButton *color4 = new QPushButton();
        color4->setFixedSize(40,40);
        color4->setStyleSheet("background-color: green; border: 1 px solid black");

        QPushButton *color5 = new QPushButton();
        color5->setFixedSize(40,40);
        color5->setStyleSheet("background-color: white; border: 1 px solid black");

        QPushButton *color6 = new QPushButton();
        color6->setFixedSize(40,40);
        color6->setStyleSheet("background-color: blue; border: 1 px solid black");

        setColorPenRIGHT->addWidget(color4);
        setColorPenRIGHT->addWidget(color5);
        setColorPenRIGHT->addWidget(color6);

        setColorPenPanel->addLayout(setColorPenLEFT);
        setColorPenPanel->addLayout(setColorPenRIGHT);

        connect(color1, &QPushButton::clicked, this, [this, setColorPenW](){applyColorPenW(Qt::black, setColorPenW);});
        connect(color2, &QPushButton::clicked, this, [this, setColorPenW](){applyColorPenW(Qt::red, setColorPenW);});
        connect(color3, &QPushButton::clicked, this, [this, setColorPenW](){applyColorPenW(Qt::yellow, setColorPenW);});
        connect(color4, &QPushButton::clicked, this, [this, setColorPenW](){applyColorPenW(Qt::green, setColorPenW);});
        connect(color5, &QPushButton::clicked, this, [this, setColorPenW](){applyColorPenW(Qt::white, setColorPenW);});
        connect(color6, &QPushButton::clicked, this, [this, setColorPenW](){applyColorPenW(Qt::blue, setColorPenW);});

        setColorPenW->show();
    }

    void toolBar::applyColorPenW(QColor color, QWidget * setColorPenW){
        QPen tempPen = view->getPen();
        // tempPen.setColor(Qt::black);
        tempPen.setColor(color);
        view->setPen(tempPen);

        /// 1 - solidLind (2 - DashLline)
        /// 1 2 3 4 - цвет
        /// 1 - толщина
        /// ничего лучше не придумал
        QString stylePen = tempPen.style() == Qt::SolidLine? "1 ":"2 ";
        QString text = stylePen + QString::number(tempPen.color().alpha()) + " " + QString::number(tempPen.color().red()) +
                       " " + QString::number(tempPen.color().green()) + " " + QString::number(tempPen.color().blue()) +
                       " " + QString::number(tempPen.width());
        saveInFileSettings("Pen ", text);
        if (fileIsLoaded)
        {
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
            fileIsLoaded=true;
            setColorPenW->close();
        }
    }

    void toolBar::setWightPen(){
        /// https://doc.qt.io/qt-6/qinputdialog.html
        bool ok{};
        QString text = QInputDialog::getText(this, tr("Ввод толщины линии"),
                                             tr("   Укажите толщину линии,\nположительное целое число:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty())
        {
            if (!text.toUInt())
            {
                /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
                QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setWindowTitle("Внимание!");
                msgBox->setText("Введены некорректные данные.\nБудьте любезны только положительное целое число");
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->exec();
            }
            else
            {
                QPen tempPen = view->getPen();
                tempPen.setWidth(text.toUInt());

                /// 1 - solidLind (2 - DashLline)
                /// 1 2 3 4 - цвет
                /// 1 - толщина
                /// ничего лучше не придумал
                QString stylePen = tempPen.style() == Qt::SolidLine? "1 ":"2 ";
                QString text = stylePen + QString::number(tempPen.color().alpha()) + " " + QString::number(tempPen.color().red()) +
                               " " + QString::number(tempPen.color().green()) + " " + QString::number(tempPen.color().blue()) +
                               " " + QString::number(tempPen.width());
                saveInFileSettings("Pen ", text);
                view->setPen(tempPen);
                if (fileIsLoaded)
                {
                    view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
                    infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
                    fileIsLoaded=true;
                }
            }
        }
    }

    void toolBar::TopSettings(){
        QWidget * TopSettings = new QWidget();
        TopSettings->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        TopSettings->setWindowTitle("Изменение параментов вершин");
        QVBoxLayout *TopSettingsLayout = new QVBoxLayout(TopSettings);

        QPushButton *button4 = new QPushButton("Выберите тип вершин (нет, круг, квадрат)");
        button4->setFixedHeight(60);
        button4->setStyleSheet("color: black");

        QPushButton *button5 = new QPushButton("Выберите цвет вершин");
        button5->setFixedHeight(60);
        button5->setStyleSheet("color: black");

        QPushButton *button6 = new QPushButton("Выберите размер вершин");
        button6->setFixedHeight(60);
        button6->setStyleSheet("color: black");


        TopSettingsLayout->addWidget(button4);
        TopSettingsLayout->addWidget(button5);
        TopSettingsLayout->addWidget(button6);

        connect(button4, &QPushButton::clicked, this, &toolBar::setTypeTop);
        connect(button5, &QPushButton::clicked, this, &toolBar::setColorTop);
        connect(button6, &QPushButton::clicked, this, &toolBar::SetWightTop);

        TopSettings->show();
    }

    void toolBar::setTypeTop(){
        QWidget * setTypeTopW = new QWidget();
        setTypeTopW->setMinimumWidth(350);
        setTypeTopW->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        setTypeTopW->setWindowTitle("Выберите тип вершины");

        QVBoxLayout *setTypeTopPanel = new QVBoxLayout(setTypeTopW);

        QPushButton *type1 = new QPushButton("Вершины в виде элипса");
        type1->setFixedHeight(60);
        type1->setStyleSheet("color: black");

        QPushButton *type2 = new QPushButton("Вершины в виде квадрата");
        type2->setFixedHeight(60);
        type2->setStyleSheet("color: black");

        QPushButton *type3 = new QPushButton("Нет вершин (пустота)");
        type3->setFixedHeight(60);
        type3->setStyleSheet("color: black");

        setTypeTopPanel->addWidget(type1);
        setTypeTopPanel->addWidget(type2);
        setTypeTopPanel->addWidget(type3);


        connect(type1, &QPushButton::clicked, this, [this, setTypeTopW](){applyTopType(type_top::elipse, setTypeTopW);});
        connect(type2, &QPushButton::clicked, this, [this, setTypeTopW](){applyTopType(type_top::square, setTypeTopW);});
        connect(type3, &QPushButton::clicked, this, [this, setTypeTopW](){applyTopType(type_top::none, setTypeTopW);});

        setTypeTopW->show();
    }

    void toolBar::applyTopType(type_top typeTop_, QWidget * setTypeTopW)
    {
        int TopData_w=view->getTopData_w();
        int TopData_h = view->getTopData_h();
        type_top TopData_typeTop = typeTop_;
        view->setTopData(TopData_w, TopData_h, TopData_typeTop);

        /// 1 - elipse (2 - square) (3 - none)
        /// 4 5 6 7 - цвет
        /// 8 - толщина
        /// ничего лучше не придумал
        QString temptext = "";
        if (typeTop_ == elipse)
            temptext="1";
        else if (typeTop_ == square)
            temptext="2";
        else if (typeTop_ == none)
            temptext="3";

        QPen tempTop = view->getTop();
        QString text = temptext + " " + QString::number(tempTop.color().alpha()) + " " + QString::number(tempTop.color().red()) +
                       " " + QString::number(tempTop.color().green()) + " " + QString::number(tempTop.color().blue()) +
                       " " + QString::number(view->getTop_w());
        saveInFileSettings("Top ", text);

        if (fileIsLoaded)
        {
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
            fileIsLoaded=true;
            setTypeTopW->close();
        }
    }

    void toolBar::setColorTop(){
        QWidget * setColorTopW = new QWidget();
        setColorTopW->setMinimumWidth(350);
        setColorTopW->setAttribute(Qt::WA_DeleteOnClose); /// удалится, когда будет закрыт виджет - не должно быть утечки

        setColorTopW->setWindowTitle("Выберите цвет вершин");

        QHBoxLayout *setColorTopPanel = new QHBoxLayout(setColorTopW);

        QVBoxLayout *setColorTopLEFT = new QVBoxLayout();

        QPushButton *color1 = new QPushButton();
        color1->setFixedSize(40,40);
        color1->setStyleSheet("background-color: black; border: 1 px solid black;");

        QPushButton *color2 = new QPushButton();
        color2->setFixedSize(40,40);
        color2->setStyleSheet("background-color: red; border: 1 px solid black");

        QPushButton *color3 = new QPushButton();
        color3->setFixedSize(40,40);
        color3->setStyleSheet("background-color: yellow; border: 1 px solid black;");

        setColorTopLEFT->addWidget(color1);
        setColorTopLEFT->addWidget(color2);
        setColorTopLEFT->addWidget(color3);

        QVBoxLayout *setColorTopRIGHT = new QVBoxLayout();

        QPushButton *color4 = new QPushButton();
        color4->setFixedSize(40,40);
        color4->setStyleSheet("background-color: green; border: 1 px solid black");

        QPushButton *color5 = new QPushButton();
        color5->setFixedSize(40,40);
        color5->setStyleSheet("background-color: white; border: 1 px solid black");

        QPushButton *color6 = new QPushButton();
        color6->setFixedSize(40,40);
        color6->setStyleSheet("background-color: blue; border: 1 px solid black");

        setColorTopRIGHT->addWidget(color4);
        setColorTopRIGHT->addWidget(color5);
        setColorTopRIGHT->addWidget(color6);

        setColorTopPanel->addLayout(setColorTopLEFT);
        setColorTopPanel->addLayout(setColorTopRIGHT);

        connect(color1, &QPushButton::clicked, this, [this, setColorTopW](){applyColorTop(Qt::black, setColorTopW);});
        connect(color2, &QPushButton::clicked, this, [this, setColorTopW](){applyColorTop(Qt::red, setColorTopW);});
        connect(color3, &QPushButton::clicked, this, [this, setColorTopW](){applyColorTop(Qt::yellow, setColorTopW);});
        connect(color4, &QPushButton::clicked, this, [this, setColorTopW](){applyColorTop(Qt::green, setColorTopW);});
        connect(color5, &QPushButton::clicked, this, [this, setColorTopW](){applyColorTop(Qt::white, setColorTopW);});
        connect(color6, &QPushButton::clicked, this, [this, setColorTopW](){applyColorTop(Qt::blue, setColorTopW);});

        setColorTopW->show();
    }

    void toolBar::applyColorTop(QColor color_, QWidget * setColorTopW){
        QPen tempTop = view->getTop();
        tempTop.setColor(color_);
        view->setTop(tempTop);

        QString text = QString::number(view->getTopType()) + " " + QString::number(tempTop.color().alpha()) + " " + QString::number(tempTop.color().red()) +
                       " " + QString::number(tempTop.color().green()) + " " + QString::number(tempTop.color().blue()) +
                       " " + QString::number(view->getTop_w());
        saveInFileSettings("Top ", text);

        if (fileIsLoaded)
        {
            view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
            infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
            fileIsLoaded=true;
            setColorTopW->close();
        }
    }

    void toolBar::SetWightTop(){
        /// https://doc.qt.io/qt-6/qinputdialog.html
        bool ok{};
        QString text = QInputDialog::getText(this, tr("Ввод толщины вершины"),
                                             tr("   Укажите толщину вершин,\nположительное целое число:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty())
        {
            if (!text.toUInt())
            {
                /// https://www.itmathrepetitor.ru/qt5-kak-vyvesti-okno-s-soobshheniem/
                QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setWindowTitle("Внимание!");
                msgBox->setText("Введены некорректные данные.\nБудьте любезны только положительное целое число");
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->exec();
            }
            else
            {
                int TopData_w=text.toUInt();
                int TopData_h = text.toUInt();
                type_top TopData_typeTop = view->getTopData_typeTop();
                view->setTopData(TopData_w, TopData_h, TopData_typeTop);

                QPen tempTop = view->getTop();
                QString temptext = {};
                QString text_ = QString::number(view->getTopType()) + " " + QString::number(tempTop.color().alpha()) + " " + QString::number(tempTop.color().red()) +
                                " " + QString::number(tempTop.color().green()) + " " + QString::number(tempTop.color().blue()) +
                                " " + text;
                saveInFileSettings("Top ", text_);

                // qDebug() << tempTop;

                if (fileIsLoaded)
                {
                    view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
                    infoPanel->drawInformation(model->getfileName(), model->getVertexes(), model->getFace(), model->getScaleModel());
                    fileIsLoaded=true;
                }
            }
        }
    }




    }

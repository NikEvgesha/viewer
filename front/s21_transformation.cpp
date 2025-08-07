#include "s21_transformation.h"


namespace s21{
    transformation::transformation(Model* model_, Viewer *view_) {
        /// https://doc.qt.io/qt-6.5/qtwidgets-widgets-groupbox-example.html
        /// https://doc.qt.io/qt-6/qtwidgets-widgets-spinboxes-example.html
        grid = new QGridLayout();
        model=model_;
        view=view_;
        setLayout(grid);

        this->setStyleSheet("background-color: black");
        this->setMinimumWidth(300);

        QLabel * textBlock1 = new QLabel("Перемещение модели");
        textBlock1->setStyleSheet("border: 2px solid grey; background-color: LightGrey; color: black;");
        QDoubleSpinBox * x_move_spinBox=new QDoubleSpinBox();
        QDoubleSpinBox * y_move_spinBox=new QDoubleSpinBox();
        QDoubleSpinBox * z_move_spinBox=new QDoubleSpinBox();

        QWidget * x_move = setSpinBox("x в пределах от -100 до 100", -100.0, 100.0, 1.0, x_move_spinBox);
        QWidget * y_move = setSpinBox("y в пределах от -100 до 100", -100.0, 1000.0, 1.0, y_move_spinBox);
        QWidget * z_move = setSpinBox("z в пределах от -100 до 100", -100.0, 100.0, 1.0, z_move_spinBox);

        QLabel * textBlock2 = new QLabel("Поворот модели");
        textBlock2->setStyleSheet("border: 2px solid grey; background-color: LightGrey; color: black;");
        QDoubleSpinBox * x_turn_spinBox=new QDoubleSpinBox();
        QDoubleSpinBox * y_turn_spinBox=new QDoubleSpinBox();
        QDoubleSpinBox * z_turn_spinBox=new QDoubleSpinBox();
        QWidget * x_turn = setSpinBox("x в пределах от -180 до 180", -180.0, 1800.0, 1.0, x_turn_spinBox);
        QWidget * y_turn = setSpinBox("y в пределах от -180 до 180", -180.0, 1800.0, 1.0, y_turn_spinBox);
        QWidget * z_turn = setSpinBox("z в пределах от -180 до 180", -180.0, 1800.0, 1.0, z_turn_spinBox);



        QLabel * textBlock4 = new QLabel("Установить масштаб");
        textBlock4->setStyleSheet("border: 2px solid grey; background-color: LightGrey; color: black;");
        ///https://doc.qt.io/qt-6/qtwidgets-widgets-sliders-example.html
        QSlider * zoom_slider = new QSlider();
        QWidget * slider = setSlider(-10, 10, 1, zoom_slider);
        // QWidget * zoom_move = setSpinBox("увеличить(+)   уменьшить(-)  ", -1000.0, 1000.0, 1.0, zoom);

        QPushButton * applyButton = new QPushButton("Применить");
        applyButton->setStyleSheet("background-color: grey;");

        QSpacerItem * spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

        /// добавляем всеэлементы в grid
        /// addWidget(QWidget *widget, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment())

        grid->addWidget(textBlock1,2,0);
        grid->addWidget(x_move,3,0);
        grid->addWidget(y_move,4,0);
        grid->addWidget(z_move,5,0);

        grid->addWidget(textBlock2,7,0);
        grid->addWidget(x_turn,8,0);
        grid->addWidget(y_turn,9,0);
        grid->addWidget(z_turn,10,0);

        grid->addWidget(textBlock4,15,0);
        grid->addWidget(slider,16,0);

        grid->addWidget(applyButton,24,0);
        grid->addItem(spacer, 25,0);

        connect(applyButton, &QPushButton::clicked, this, [this, x_move_spinBox, y_move_spinBox, z_move_spinBox, x_turn_spinBox, y_turn_spinBox, z_turn_spinBox, zoom_slider](){drawNewView(x_move_spinBox, y_move_spinBox, z_move_spinBox, x_turn_spinBox, y_turn_spinBox, z_turn_spinBox, zoom_slider);});
    }

    QWidget * transformation::setSpinBox(QString text, double min, double max, double step, QDoubleSpinBox * &move_, double startLevel)
    {
        QWidget * box = new QWidget();
        QHBoxLayout * layout = new QHBoxLayout();

        QLabel * textLabel = new QLabel(text);
        QDoubleSpinBox * move = new QDoubleSpinBox();
        move->setRange(min, max);
        move->setSingleStep(step);
        move->setValue(startLevel);

        layout->addWidget(textLabel);
        layout->addWidget(move);

        box->setLayout(layout);

        move_=move;

        return box;
    };

    QWidget * transformation::setSlider(int min, int max, int step, QSlider * &zoom_slider)
    {
        QWidget * box = new QWidget();
        QHBoxLayout * layout = new QHBoxLayout();

        QSlider * zoom = new QSlider(Qt::Horizontal);
        zoom->setRange(min, max);
        zoom->setSingleStep(step);
        zoom->setValue(1);

        QLabel * textLabel = new QLabel(QString::number(zoom->value()));

        layout->addWidget(textLabel);
        layout->addWidget(zoom);

        box->setLayout(layout);

        connect(zoom, &QSlider::valueChanged, [textLabel, zoom](){
            if (zoom->value()==0)
                zoom->setValue(1);
            textLabel->setText(QString::number(zoom->value()));
        });

        zoom_slider = zoom;

        return box;
    };

    void transformation::drawNewView(QDoubleSpinBox * x_move_spinBox, QDoubleSpinBox * y_move_spinBox, QDoubleSpinBox * z_move_spinBox, QDoubleSpinBox * x_turn_spinBox, QDoubleSpinBox * y_turn_spinBox, QDoubleSpinBox * z_turn_spinBox, QSlider * zoom_slider){
        double x_move_res=x_move_spinBox->value();
        double y_move_res=y_move_spinBox->value();
        double z_move_res=z_move_spinBox->value();
        double x_tern_res=x_turn_spinBox->value();
        double y_turn_res=y_turn_spinBox->value();
        double z_turn_res=z_turn_spinBox->value();

        int zoom = zoom_slider->value();

        model->move(x_move_res, y_move_res, z_move_res, x_tern_res, y_turn_res, z_turn_res, zoom);
        view->paint(model->getVertexes(), model->getFace(), model->getScaleModel());
    }
}

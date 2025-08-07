#ifndef S21_TRANSFORMATION_H
#define S21_TRANSFORMATION_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QSizePolicy> /// для растягивания спейсера
#include <QCheckBox>
#include <QComboBox> /// всплывающий список
#include <QSlider> /// выбор масштаба

#include <back/s21_model.h>
#include <s21_viewer.h>


namespace s21{
    class transformation : public QWidget
    {
    private:
        QGridLayout *grid =nullptr;
        Model* model=nullptr;
        Viewer *view=nullptr;


    public:
        transformation(Model* model_, Viewer *view_);
        QWidget * setSpinBox(QString text, double min, double max, double ste, QDoubleSpinBox * &move_, double startLevel=0);
        // QDoubleSpinBox * createAndAddGridSpinBox(QString text, double min, double max, double step);
        QWidget * setSlider(int min, int max, int step, QSlider * &zoom_slider);
        void drawNewView(QDoubleSpinBox * x_move_spinBox, QDoubleSpinBox * y_move_spinBox, QDoubleSpinBox * z_move_spinBox, QDoubleSpinBox * x_turn_spinBox, QDoubleSpinBox * y_turn_spinBox, QDoubleSpinBox * z_turn_spinBox, QSlider * zoom_slider);

    };
}

#endif // S21_TRANSFORMATION_H

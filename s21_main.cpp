// #include <iostream>
#include <QApplication>
#include <s21_desktop.h>

using namespace std;

s21::desktop* s21::desktop::instance = nullptr;

int main(int argc, char ** argv)
{
    // cout << "Hello World!" << endl;

    setlocale(LC_NUMERIC, "C");

    QApplication app(argc, argv);


    s21::desktop& viewer = s21::desktop::getInstance();

    viewer.show();

    return app.exec(); /// возвращает результат исполнениея
}

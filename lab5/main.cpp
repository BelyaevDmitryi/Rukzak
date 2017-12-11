#include "mainwindow.h"
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
    SetConsoleCP( 1251 ); // настраиваем кодировку консоли (ввод)
    SetConsoleOutputCP(1251); // (вывод)

    // настраиваем внутренние механизмы на эту кодировку
    setlocale(LC_ALL,".1251");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

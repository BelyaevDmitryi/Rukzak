#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>
#include "ruksak.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void StateButtonChange();

    void Add();
    void Delete();
    void CurrentChange();
    void CollectBackpack();
    void SetMaxWeight();

    void TotalCost();
    void TotalWeigth();
    void Save();
    void Exit();
private:
    Ui::MainWindow *ui;
    int rows;
    int WEIGHT_TOTAL_MAX;//максимальный вес рюкзака
    int ITEMS_SIZE;
};

#endif // MAINWINDOW_H

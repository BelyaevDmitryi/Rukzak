#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setWindowTitle("Классические алгоритмы сортировки");//Название программы
    rows=0;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<"Вес"<<"Стоимость"<<"Количество");
    ui->tableWidget->setEditTriggers(0);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabWidget->setTabText(0,"Настройки задачи о рюкзаке");
    ui->tabWidget->setTabText(1,"Ответ");

    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setRowCount(rows);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<"Вес"<<"Стоимость"<<"Количество");
    ui->tableWidget_2->setEditTriggers(0);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->lineEdit->setPlaceholderText("Введите макс. вес и нажмите на кнопку -> ");

    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(Add()));
    connect(ui->del,SIGNAL(clicked(bool)),this,SLOT(Delete()));
    connect(ui->change,SIGNAL(clicked(bool)),this,SLOT(CurrentChange()));
    connect(ui->collected,SIGNAL(clicked(bool)),this,SLOT(CollectBackpack()));
    connect(ui->set_max_weigth,SIGNAL(clicked(bool)),this,SLOT(SetMaxWeight()));

    connect(ui->total_cost,SIGNAL(clicked(bool)),this,SLOT(TotalCost()));
    connect(ui->total_w,SIGNAL(clicked(bool)),this,SLOT(TotalWeigth()));
    connect(ui->exit,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    connect(ui->save,SIGNAL(clicked(bool)),this,SLOT(Save()));

    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(StateButtonChange()));
    connect(ui->del,SIGNAL(clicked(bool)),this,SLOT(StateButtonChange()));

    StateButtonChange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StateButtonChange()
{
    if(ui->tableWidget->rowCount()==0)
    {
        ui->del->setDisabled(true);
        ui->change->setDisabled(true);
        ui->collected->setDisabled(true);
    }
    else
    {
        ui->del->setDisabled(false);
        ui->change->setDisabled(false);
        ui->collected->setDisabled(false);
    }
}

void MainWindow::Add()
{
    bool buttonOk;
    bool buttonOk1;
    bool buttonOk2;
    bool buttonOk3;
    QString Name=QInputDialog::getText(this,"Наименование предмета","Введите название предмета..",QLineEdit::Normal,"",&buttonOk);
    if(!buttonOk)//кнопка не нажата
        return;
    else//нажата
    {
        QString Weigth = QString::number(QInputDialog::getInt(this,"Вес предмета","Введите вес предмета..",1,1,100,1,&buttonOk1));
        if(!buttonOk1)
            return;
        else
        {
            QString Cost = QString::number(QInputDialog::getInt(this,"Стоимость предмета","Введите стоимость предмета..",1,1,100,1,&buttonOk2));
            if(!buttonOk2)
                return;
            else
            {
                QString Count = QString::number(QInputDialog::getInt(this,"Количество предмета","Введите количество предмета..",1,1,100,1,&buttonOk3));
                if(!buttonOk3)
                    return;
                else
                {
                    rows++;
                    ui->tableWidget->setRowCount(rows);
                    QStringList valuelist;
                    valuelist<<Name<<Weigth<<Cost<<Count;
                    for(int i=0;i<valuelist.size();i++)
                    {
                        QTableWidgetItem* item = new QTableWidgetItem(valuelist.at(i));
                        ui->tableWidget->setItem(rows-1,i,item);
                    }
                }
            }
        }
    }
}

void MainWindow::Delete()
{
    ui->tableWidget->removeRow(rows-1);
    if(rows>0)
        rows--;
}

void MainWindow::CurrentChange()
{
    int i=ui->tableWidget->currentRow(); //строка
    if(ui->tableWidget->selectedItems().isEmpty())
        return;
    bool buttonOk;
    bool buttonOk1;
    bool buttonOk2;
    bool buttonOk3;
    QString Name=QInputDialog::getText(this,"Наименование предмета","Введите название предмета..",QLineEdit::Normal,ui->tableWidget->item(i,0)->text(),&buttonOk);
    if(!buttonOk)//кнопка не нажата
        return;
    else//нажата
    {
        QString Weigth = QString::number(QInputDialog::getInt(this,"Вес предмета","Введите вес предмета..",ui->tableWidget->item(i,1)->text().toInt(),1,100,1,&buttonOk1));
        if(!buttonOk1)
            return;
        else
        {
            QString Cost = QString::number(QInputDialog::getInt(this,"Стоимость предмета","Введите стоимость предмета..",ui->tableWidget->item(i,2)->text().toInt(),1,100,1,&buttonOk2));
            if(!buttonOk2)
                return;
            else
            {
                QString Count = QString::number(QInputDialog::getInt(this,"Стоимость предмета","Введите стоимость предмета..",ui->tableWidget->item(i,3)->text().toInt(),1,100,1,&buttonOk3));
                if(!buttonOk3)
                    return;
                else
                {
                    QStringList valuelist;
                    valuelist<<Name<<Weigth<<Cost<<Count;
                    for(int j=0;j<valuelist.size();j++)
                    {
                        QTableWidgetItem* item = new QTableWidgetItem(valuelist.at(j));
                        ui->tableWidget->setItem(i,j,item);
                    }
                }
            }
        }
    }
}

void MainWindow::CollectBackpack()
{
    if(ui->tableWidget->rowCount()!=0)
    {
        int size=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
            size=size+ui->tableWidget->item(i,3)->text().toInt();
        ITEMS_SIZE=size;//количество элементов
        T_rucksack rucksack(WEIGHT_TOTAL_MAX);
        QStringList NameList;
        QStringList Cyrcle;
        int* w = new int[ITEMS_SIZE];
        int* c = new int[ITEMS_SIZE];
        for(int i=0;i<ITEMS_SIZE;i++)
        {
            w[i]=0;
            c[i]=0;
        }
        for(int i=0;i<ui->tableWidget->rowCount();i++)
            Cyrcle.append(ui->tableWidget->item(i,3)->text());
        for(int i=0;i<ITEMS_SIZE;)
        {
            for(int j=0;j<ui->tableWidget->rowCount();j++)
            {
                for(int k=0;k<Cyrcle.at(j).toInt();k++)
                {
                    NameList.append(ui->tableWidget->item(j,0)->text());
                    w[i]=ui->tableWidget->item(j,1)->text().toInt();
                    c[i]=ui->tableWidget->item(j,2)->text().toInt();
                    i++;
                }
            }
        }
        auto items=rucksack.get_items(NameList,w,c,ITEMS_SIZE);
        rucksack.print_cont(items);
        rucksack.fill_with_max_cost(items);
        QStringList arg = rucksack.print();
        QString value;
        for(int i=0;i<arg.size();i++)
            value+=arg.at(i)+" ";
        value.chop(1);
        value.replace(QRegExp("([(]|[)])"),"");
        arg = value.split(" ",QString::SkipEmptyParts);
        int* s = new int[arg.size()];
        for(int i=0;i<arg.size();i++)
            s[i]=0;
        QMap <QString,int> map;
        QStringList::const_iterator i;
        for(i=arg.constBegin();i!=arg.constEnd();)
        {
            for(int j=0;j<arg.size();j++)
            {
                s[j]=std::count(arg.begin(),arg.end(),arg.at(j));
                map.insert(arg.at(j),s[j]);
                i++;
            }
        }
        QStringList keys = map.keys();
        QStringList values;
        for(int i=0;i<keys.size();i++)
            values.append(QString::number(map.value(keys.at(i))));
        ui->tableWidget_2->setRowCount(map.size());
        for(int i=0;i<map.size();i++)
        {
            QString res = keys.at(i);
            QStringList tmp = res.split(",",QString::SkipEmptyParts);
            for(int j=0;j<tmp.size();j++)
            {
                QTableWidgetItem* item = new QTableWidgetItem(tmp.at(j));
                ui->tableWidget_2->setItem(i,j,item);
                ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(values.at(i)));
            }
        }
    }
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::SetMaxWeight()
{
    WEIGHT_TOTAL_MAX=ui->lineEdit->text().toInt();
}

void MainWindow::TotalCost()
{
    int summary=0;
    if(ui->tableWidget_2->rowCount()!=0)
    {
        int *c = new int[ui->tableWidget_2->rowCount()];
        for(int i=0;i<ui->tableWidget_2->rowCount();i++)
            c[i]=ui->tableWidget_2->item(i,2)->text().toInt()*ui->tableWidget_2->item(i,3)->text().toInt();
        for(int i=0;i<ui->tableWidget_2->rowCount();i++)
            summary+=c[i];
    }
    QMessageBox::information(this,"Общая стоимость","Стоимость предметов находящихся в рюкзаке = "+QString::number(summary));
}

void MainWindow::TotalWeigth()
{
    int summary=0;
    if(ui->tableWidget_2->rowCount()!=0)
    {
        int *w = new int[ui->tableWidget_2->rowCount()];
        for(int i=0;i<ui->tableWidget_2->rowCount();i++)
            w[i]=ui->tableWidget_2->item(i,1)->text().toInt()*ui->tableWidget_2->item(i,3)->text().toInt();
        for(int i=0;i<ui->tableWidget_2->rowCount();i++)
            summary+=w[i];
    }
    QMessageBox::information(this,"Общий вес","Вес предметов находящихся в рюкзаке = "+QString::number(summary));
}

void MainWindow::Save()
{

}

void MainWindow::Exit()
{
    QApplication::exit(0);
}

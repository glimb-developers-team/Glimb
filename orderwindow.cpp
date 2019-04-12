#include "orderwindow.h"
#include "ui_orderwindow.h"

OrderWindow::OrderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Артикул"<<"Наименование"<<"Цена"<<"Количество");


    ui->tableWidget->setItem(0,0, new QTableWidgetItem("jfnkjnnksnkjs"));

}

OrderWindow::~OrderWindow()
{
    delete ui;
}

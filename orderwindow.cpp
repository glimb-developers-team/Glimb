#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "RequestFormer.h"
#include <queue>
#include <iostream>

OrderWindow::OrderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<"Единицы измерения"<<"Цена");

    std::queue<Material> q = RequestFormer::to_get_materials();
    Material mat;
    char buffer[16];

    for (int i = 0; !q.empty(); i++) {
            mat = q.front();
            LogPrinter::print("Getted material");
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(mat.title.c_str()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(mat.unions.c_str()));
            snprintf(buffer, 16, "%.2lf", mat.price);
            std::cout << buffer << " : " << mat.price << std::endl;
            LogPrinter::print(buffer);
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(buffer));
            q.pop();
    }
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

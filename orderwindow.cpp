#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "RequestFormer.h"
#include <queue>

OrderWindow::OrderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<"Цена"<<"Количество");

    std::queue<Material> q = RequestFormer::to_get_materials();
    Material mat;
    char price_buf[8];

    for (int i = 0; !q.empty(); i++) {
            mat = q.front();
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(mat.title.c_str()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(mat.unions.c_str()));
            sprintf(price_buf, "%f", mat.price);
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(price_buf));
            q.pop();
    }
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

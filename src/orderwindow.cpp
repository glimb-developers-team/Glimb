#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "RequestFormer.h"
#include <queue>
#include <iostream>
#include <queue>
#include <QMessageBox>
using namespace std;

OrderWindow::OrderWindow(QWidget *parent, std::queue<std::string> clients_numbers) :
    QWidget(parent),
    ui(new Ui::OrderWindow),
    clients_numbers(clients_numbers)
{
    try {
        ui->setupUi(this);
        ui->tableWidget->setRowCount(10);
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<"Единицы измерения"<<"Цена"<<"Кол-во");

        std::queue<Material> q = RequestFormer::to_get_materials();
        Material mat;
        char buffer[16];

        for (int i = 0; !q.empty(); i++) {
                mat = q.front();
                LogPrinter::print("Getted material");
                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(mat.title.c_str()));
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(mat.unions.c_str()));
                snprintf(buffer, 16, "%.2lf", mat.price);
                ui->tableWidget->setItem(i, 2, new QTableWidgetItem(buffer));
                q.pop();
        }
    }
    catch (const char *error) {
        QMessageBox::critical(this, "Внимание!", error);
    }

    while (!clients_numbers.empty()) {
        ui->comboBox->addItem(clients_numbers.front().c_str());
        clients_numbers.pop();
    }
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

void OrderWindow::on_searchButton_clicked()
{
    int k[10];
    memset(k,0,10*sizeof(int));
    QString search = ui->searchLine->text();
    string srch = search.toUtf8().constData();
    char charSearch[30];
    strcpy(charSearch,srch.c_str());
    int h = 0;
    for (int i = 0; i < 10; i++)
    {
        if (ui->tableWidget->item(i,0)!=0)
        {

            int a = ui->tableWidget->item(i,0)->text().length();
            QString searchWord= ui->tableWidget->item(i,0)->text();
            string srchWord = searchWord.toUtf8().constData();
            char charSearchWord[30];
            strcpy(charSearchWord,srchWord.c_str());
            for(int j = 0; j < a; j++ )
            {
                if (charSearchWord[j] == charSearch[h])
                {
                    k [i]++ ;
                    h++;
                }
                else
                {
                   h = 0;
                }

            }
        }
    }
    int max = 0;
    int maxindex = 0;
    for (int i = 0; i < 10; i++)
    {
        if (max < k[i])
        {
            max = k[i];
            maxindex = i;
        }
    }
    if (max > 2)
    {
        ui->tableWidget->selectRow(maxindex);
    }

}

void OrderWindow::on_orderButton_clicked()
{
    queue <Purchase> orderList;

    for (int i = 0; i < ui->tableWidget->rowCount();i++)
        if (ui->tableWidget->item(i,3) != 0)
        {
            Purchase row;
            row.title = ui->tableWidget->item(i,0)->text().toUtf8().constData();
            row.quantity = ui->tableWidget->item(i,3)->text().toInt();
            orderList.push(row);
            LogPrinter::print(row.title);
        }

    RequestFormer::to_send_purchase("89165205824",ui->comboBox->currentText().toUtf8().constData(),orderList);
}

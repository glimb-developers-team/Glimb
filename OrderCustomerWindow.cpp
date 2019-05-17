#include "OrderCustomerWindow.h"
#include "ui_OrderCustomerWindow.h"
#include <string>

OrderCustomerWindow::OrderCustomerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderCustomerWindow)

{
    ui->setupUi(this);
    for (int g = 0; g < 5; g++)
    {
        QTreeWidgetItem *i = new QTreeWidgetItem(ui->treeWidget);
            ui->treeWidget->addTopLevelItem(i);
            i->setText(0,QString::fromStdString(std::string("Закупка")+std::to_string(g)));
        for(int k = 0; k < 5; k++)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(i);
            item->setText(0,QString::fromStdString(std::string("Материалы")+std::to_string(k)));
        }
    }

}

OrderCustomerWindow::~OrderCustomerWindow()
{
    delete ui;
}

#include "CustomerWindow.h"
#include "ui_CustomerWindow.h"


CustomerWindow::CustomerWindow(QWidget *parent, std::string name, std::string last_name, std::string middle_name) :
    ui(new Ui::CustomerWindow),
    QWidget(parent),
    name(name),
    last_name(last_name),
    middle_name(middle_name)
{
    ui->setupUi(this);

}

CustomerWindow::~CustomerWindow()
{
    delete ui;
}

void CustomerWindow::on_pushButton_clicked()
{
    WindowOrder = new OrderCustomerWindow();
    WindowOrder->setModal(true);
    WindowOrder->exec();
}

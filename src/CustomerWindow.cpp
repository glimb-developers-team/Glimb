#include "CustomerWindow.h"
#include "ui_CustomerWindow.h"


CustomerWindow::CustomerWindow(QWidget *parent, std::string name,
                               std::string last_name, std::string middle_name, std::string foreman_number) :
    QWidget(parent),
    ui(new Ui::CustomerWindow),
    name(name),
    last_name(last_name),
    middle_name(middle_name),
    foreman_number(foreman_number)

{
    ui->setupUi(this);
    ui->labelFIO->setText(QString::fromStdString("Здравствуйте, "+name));
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

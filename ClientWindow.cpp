#include "ClientWindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent, std::string name, std::string last_name, std::string middle_name) :
    ui(new Ui::ClientWindow),
    QWidget(parent),
    name(name),
    last_name(last_name),
    middle_name(middle_name)

{

    ui->setupUi(this);
    std::string FIO = name;
    last_name + middle_name;
    ui->label_FIO->setText(FIO.c_str());
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_but_clicked()
{
    oWindow = new OrderWindow();
    oWindow->show();
    this->close();
}

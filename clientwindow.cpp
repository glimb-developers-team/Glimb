#include "ClientWindow.h"
#include "ui_ClientWindow.h"

ClientWindow::ClientWindow(QWidget *parent, std::string name, std::string last_name, std::string middle_name) :
    ui(new Ui::ClientWindow),
    QWidget(parent),
    name(name),
    last_name(last_name),
    middle_name(middle_name)

{
    ui->setupUi(this);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

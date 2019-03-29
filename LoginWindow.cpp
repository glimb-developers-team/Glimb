#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegistrationWindow.h"
#include <QMessageBox>
#include <string>


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    sWindow = new ClientWindow();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_Button_Login_clicked()
{
    sWindow ->show();
    this->close();
}

void LoginWindow::on_Button_Registration_clicked()
{
    RegistrationWindow window;
    window.setModal(true);
    window.exec();
}

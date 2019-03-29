#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegistrationWindow.h"
#include <QMessageBox>
#include <string>


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
     try {
         RequestFormer::connect_to_server();
     }
     catch (char const *error) {

        QMessageBox::critical(this, "Внимание!", error);
    }
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_Button_Login_clicked()
{
     std::string login;
    login = ui->lineEdit_Login->text().toUtf8().constData();

    std::string password;
    password = ui->lineEdit_Password->text().toUtf8().constData();

    std::string name, last_name, middle_name;
    try {
        RequestFormer::to_enter(name, last_name, middle_name, login, password);
        sWindow = new ClientWindow(name, last_name, middle_name);
        sWindow->show();
        this->close();
    }
    catch (char const *error) {

        QMessageBox::critical(this, "Внимание!", error);
    }
}

void LoginWindow::on_Button_Registration_clicked()
{
    RegistrationWindow window;
    window.setModal(true);
    window.exec();
}

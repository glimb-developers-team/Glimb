#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RequestFormer.h"
#include "RegistrationWindow.h"
#include <QMessageBox>
#include <string>


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
     ui->setupUi(this);
     try
    {
         RequestFormer::connect_to_server();
    }
     catch (char const *error)
    {

        QMessageBox::critical(this, "Внимание!", error);
    }
}

LoginWindow::~LoginWindow()
{
    RequestFormer::disconnect();
    delete ui;

}

void LoginWindow::on_Button_Login_clicked()
{
     std::string login;
    login = ui->lineEdit_Login->text().toUtf8().constData();

    std::string password;
    password = ui->lineEdit_Password->text().toUtf8().constData();

    std::string name, last_name, middle_name, type;
    std::queue<std::string> clients_numbers;
    try {
        RequestFormer::to_enter(login, password, name, last_name, middle_name, type, clients_numbers);
        sWindow = new ClientWindow(0, name, last_name, middle_name, clients_numbers);
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

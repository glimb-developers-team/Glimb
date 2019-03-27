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


void LoginWindow::on_pushButton_Login_clicked()
{
    
    std::string login;
    login = ui->lineEdit_Login->text().toUtf8().constData();
    
    std::string password;
    password = ui -> lineEdit_Password->text().toUtf8().constData();

    std::string answer;

    try {
        answer = former.to_enter(login, password);

        if (answer == "ok"){
            sWindow ->show();
            this->close();
        }
        else {
            QMessageBox::critical(this, "Внимание!", answer.c_str());
        }
    }
    catch (char const *error) {

        QMessageBox::critical(this, "Внимание!", error);
    }
}

void LoginWindow::on_pushButton_Registration_clicked()
{
    RegistrationWindow window;
    window.setModal(true);
    window.exec();
}

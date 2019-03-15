#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegistrationWindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_pushButton_4_clicked()
{
    QMessageBox::critical(this, "Внимание!", "Неверно введен пароль");

    QMessageBox::critical(this, "Внимание!", "Неверно введен логин");
    QMessageBox::warning(this, "Предупреждение!", "Такой логин уже существует");

    QMessageBox::critical(this, "Внимание!", "Неверно введен ID Пользователя");

}

void LoginWindow::on_pushButton_3_clicked()
{
    RegistrationWindow window;
    window.setModal(true);
    window.exec();
}

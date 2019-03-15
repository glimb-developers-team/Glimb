#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"
#include <QMessageBox>

RegistrationWindow::RegistrationWindow(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::RegistrationWindow)
{
    this->setWindowTitle("Новое название");
    ui->setupUi(this);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_pushButton_clicked()
{
    QMessageBox::critical(this, "Внимание!", "Неверно введена почта");
    QMessageBox::critical(this, "Внимание!", "Неверно введен логин прораба");
    QMessageBox::critical(this, "Внимание!", "Вы заполнили не все поля для регистрации");
}

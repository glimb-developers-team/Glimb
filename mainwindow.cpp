#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    QMessageBox::critical(this, "Внимание!", "Неверно введен пароль");

    QMessageBox::critical(this, "Внимание!", "Неверно введен логин");
    QMessageBox::warning(this, "Предупреждение!", "Такой логин уже существует");

    QMessageBox::critical(this, "Внимание!", "Неверно введен ID Пользователя");

}

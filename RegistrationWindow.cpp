#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"
#include <QMessageBox>
#include "RequestFormer.h"
//#include "former.h"

extern RequestFormer former;

RegistrationWindow::RegistrationWindow(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::RegistrationWindow)
{

    ui->setupUi(this);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_pushButton_RegistrationTwo_clicked()
{

    /*std::string answer;
    try {
        answer = former.to_register(ui->lineEdit_Name->text().toUtf8().constData(),
                                    ui->lineEdit_LastName->text().toUtf8().constData(),
                                    ui->lineEdit_MiddleName->text().toUtf8().constData(),
                                    ui->lineEdit_Password->text().toUtf8().constData(),
                                    ui->lineEdit_Phone->text().toUtf8().constData(),
                                    ui->lineEdit_PhoneContractor->text().toUtf8().constData(),
                                    ui->radioButton_Client->text().toUtf8().constData()
                                    );

        if (answer == "ok") {


        }
        else {
            QMessageBox::critical(this, "Внимание!", answer.c_str());
        }
    }
    catch (char const *error) {
        QMessageBox::critical(this, "Внимание!", error);
    }*/

}

#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"
#include <QMessageBox>
#include "RequestFormer.h"

extern RequestFormer former;

std::string type;

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
	if (ui->radioButton_Client->isChecked()) {
		type = "client";
	}
	else {
		type = "foreman";
	}
     try {
         RequestFormer::to_register(ui->lineEdit_Name->text().toUtf8().constData(),
                                    ui->lineEdit_LastName->text().toUtf8().constData(),
                                    ui->lineEdit_MiddleName->text().toUtf8().constData(),
                                    ui->lineEdit_Phone->text().toUtf8().constData(),
                                    ui->lineEdit_Password->text().toUtf8().constData(),
				    type,
                                    ui->lineEdit_PhoneContractor->text().toUtf8().constData()
                                    );
         sWindow = new ClientWindow(0, ui->lineEdit_Name->text().toUtf8().constData(),  ui->lineEdit_LastName->text().toUtf8().constData(),
                                    ui->lineEdit_MiddleName->text().toUtf8().constData());
         sWindow->show();
         this->close();
    }
    catch (char const *error) {
        QMessageBox::critical(this, "Внимание!", error);
    }

}

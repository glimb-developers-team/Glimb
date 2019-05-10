#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "ClientWindow.h"
#include <QDialog>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:

    void on_Button_RegistrationTwo_clicked();

    void on_radioButton_Contractor_clicked();

    void on_radioButton_Client_clicked();

private:
    ClientWindow *sWindow;
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATION_H

#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "clientwindow.h"
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

    void on_pushButton_RegistrationTwo_clicked();


private:
    ClientWindow *sWindow;
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATION_H

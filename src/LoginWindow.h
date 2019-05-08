#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientWindow.h"


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();



private slots:

    void on_Button_Login_clicked();

    void on_Button_Registration_clicked();

private:
    ClientWindow *sWindow;
    Ui::LoginWindow *ui;
};

#endif // MAINWINDOW_H

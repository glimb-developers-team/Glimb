#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QWidget>
#include "OrderCustomerWindow.h"

namespace Ui {
class CustomerWindow;
}

class CustomerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerWindow(QWidget *parent = 0, std::string name = "",
                            std::string last_name = "", std::string middle_name = "", std::string foreman_number = "");
    ~CustomerWindow();

private slots:
    void on_pushButton_clicked();

private:
    OrderCustomerWindow *WindowOrder;
    Ui::CustomerWindow *ui;
    std::string name;
    std::string last_name;
    std::string middle_name;
    std::string foreman_number;

};

#endif // CUSTOMERWINDOW_H

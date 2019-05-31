#ifndef ORDERCUSTOMERWINDOW_H
#define ORDERCUSTOMERWINDOW_H

#include <QDialog>

namespace Ui {
class OrderCustomerWindow;
}

class OrderCustomerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OrderCustomerWindow(QWidget *parent = 0);
    ~OrderCustomerWindow();

private:
    Ui::OrderCustomerWindow *ui;
};

#endif // ORDERCUSTOMERWINDOW_H

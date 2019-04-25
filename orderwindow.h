#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWindow(QWidget *parent = 0);
    ~OrderWindow();

private slots:

    void on_searchButton_clicked();

    void on_orderButton_clicked();

private:
    Ui::OrderWindow *ui;
};

#endif // ORDERWINDOW_H

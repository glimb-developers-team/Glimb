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

private:
    Ui::OrderWindow *ui;
};

#endif // ORDERWINDOW_H

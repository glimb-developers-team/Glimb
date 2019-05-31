#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>
#include <queue>

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWindow(QWidget *parent = 0, std::queue<std::string> clients_numbers = std::queue<std::string>(), std::string login = "");
    ~OrderWindow();

private slots:

    void on_searchButton_clicked();

    void on_orderButton_clicked();

private:
    Ui::OrderWindow *ui;
    std::queue<std::string> clients_numbers;
    std::string _login;
};

#endif // ORDERWINDOW_H

#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <string>
#include "orderwindow.h"
#include <queue>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0, std::string name = "", std::string last_name = "", std::string middle_name = "", std::queue<std::string> clients_numbers = std::queue<std::string>());
    ~ClientWindow();

private slots:

    void on_but_clicked();

private:
    OrderWindow *oWindow;
    Ui::ClientWindow *ui;
    std::string name;
    std::string last_name;
    std::string middle_name;
    std::queue<std::string> clients_numbers;
};

#endif // CLIENTWINDOW_H

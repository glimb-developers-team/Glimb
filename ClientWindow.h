#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <string>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0, std::string name = "", std::string last_name = "", std::string middle_name = "");
    ~ClientWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ClientWindow *ui;
    std::string name;
    std::string last_name;
    std::string middle_name;
};

#endif // CLIENTWINDOW_H

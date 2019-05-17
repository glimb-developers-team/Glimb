#include "ClientWindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent, std::string name, std::string last_name, std::string middle_name, std::queue<std::string> clients_numbers) :
    ui(new Ui::ClientWindow),
    QWidget(parent),
    name(name),
    last_name(last_name),
    middle_name(middle_name),
    clients_numbers(clients_numbers)
{

    ui->setupUi(this);
    std::string FIO = name;
    last_name + middle_name;
    ui->label_FIO->setText(FIO.c_str());
    for (int g = 1; g < 6; g++)
    {
        QTreeWidgetItem *i = new QTreeWidgetItem(ui->treeWidget);
            ui->treeWidget->addTopLevelItem(i);
            i->setText(0,QString::fromStdString(std::string("Закупка")+std::to_string(g)));
        for(int k = 1; k < 10; k++)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(i);
            item->setText(0,QString::fromStdString(std::string("Материалы")+std::to_string(k)));
        }
    }
}


ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_but_clicked()
{
    oWindow = new OrderWindow(0, clients_numbers);
    oWindow->show();
    this->close();
}

#include "ClientWindow.h"
#include "ui_clientwindow.h"
#include "RequestFormer.h"
#include "LogPrinter.h"

ClientWindow::ClientWindow(QWidget *parent, std::string name, std::string last_name, std::string middle_name, std::queue<std::string> clients_numbers, std::string login) :
    QWidget(parent),
    ui(new Ui::ClientWindow),
    name(name),
    last_name(last_name),
    middle_name(middle_name),
    clients_numbers(clients_numbers),
    _login(login)
{

    ui->setupUi(this);
    std::string FIO = name;
    last_name + middle_name;
    ui->label_FIO->setText(QString::fromStdString("Здравствуйте, "+FIO));
    std::string loginNumber = login;

    while (!clients_numbers.empty())
    {
        ui->clientNumbersBox->addItem(clients_numbers.front().c_str());
        clients_numbers.pop();
    }

    std :: string client_number = ui->clientNumbersBox->currentText().toUtf8().constData();
    std::queue<ShoppingList> purchases = RequestFormer::to_show_purchases(_login, client_number);
    while (!purchases.empty())
    {

        ShoppingList cur_purchase = purchases.front();
        LogPrinter::print("Id: " + std::to_string(cur_purchase.purchase_id));
        QTreeWidgetItem *i = new QTreeWidgetItem(ui->orderTree);
            ui->orderTree->addTopLevelItem(i);

            i->setText(0,QString::fromStdString(std::string("Закупка")+std::to_string(cur_purchase.purchase_id)));//айди закупки
        while(!cur_purchase.purchase.empty())
        {
            Buying cur_material = cur_purchase.purchase.front();
            QTreeWidgetItem *item = new QTreeWidgetItem(i);
            item->setText(0,QString::fromStdString(cur_material.title + " " +
                                                   std::to_string(cur_material.quantity) + " " +
                                                   std::to_string(cur_material.cost)));//материал в закупке
            cur_purchase.purchase.pop();
        }
        purchases.pop();
    }

}


ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_but_clicked()
{
    oWindow = new OrderWindow(0, clients_numbers, _login);
    oWindow->show();
    this->close();
}

void ClientWindow::on_pushButton_4_clicked()
{

}

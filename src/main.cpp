#include "LoginWindow.h"
#include <QApplication>
#include <QTextCodec>
#include "RequestFormer.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();

    return a.exec();
}

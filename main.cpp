#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString inputFilename = argv[1];
    WebSocketClient client(inputFilename);
    MainWindow w(inputFilename, &client);
    w.show();
    return a.exec();
}

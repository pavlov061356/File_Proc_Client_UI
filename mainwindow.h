#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "websocketclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString input, WebSocketClient *client);
    ~MainWindow();

private slots:
    void StartClient();

private:
    Ui::MainWindow *ui;
    QPushButton *button;
    QString filename;
    WebSocketClient *Client;
};
#endif // MAINWINDOW_H

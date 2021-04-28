#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QString input, WebSocketClient *client)
    :ui(new Ui::MainWindow)
{
    Client = client;
    ui->setupUi(this);
    filename = input;
    button = new QPushButton("Click to send file!", this);
    button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(button, SIGNAL (clicked()), this, SLOT (StartClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartClient(){
    Client->StartClient();
}


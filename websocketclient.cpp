#include "websocketclient.h"
#include <QDataStream>
#include <QThread>
#include <QFileInfo>
#include <QDebug>
#include <QHash>

WebSocketClient::WebSocketClient(QString Filename)
{
    filename = Filename;
    //QTextStream cin(stdin);
    //filename = cin.readLine();

}

WebSocketClient::~WebSocketClient(){
    WebSocket.abort();
}

void WebSocketClient::StartClient(){
    qDebug()<<"connection starting";
    connect(&WebSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&WebSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    connect(&WebSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageRecieved);
    //connect(&WebSocket, SIGNAL(textMessageReceived(const QString&)), this, SLOT(ProcessTextMessage(const QString&)));
    WebSocket.open(QUrl(QStringLiteral("ws://0.0.0.0:40901")));
}

void WebSocketClient::onConnected(){
    //qDebug() << WebSocket.state();
    if(i == 0){
        WebSocket.sendTextMessage("File transmission start");
        i++;
    }
    if(transmission ==true){
        fileTransmission(filename, LessorIP, port, token);
        transmission = false;
    }
    //qDebug()<<"Connected";
    //WebSocket.sendTextMessage(QStringLiteral("Hello, world!"));

}

void WebSocketClient::fileTransmissionPreparation(QString LessorIP, QString port, QString token){
        QString LessorURL = "ws://" + LessorIP + ":" + port;
        //WebSocket.sendTextMessage(QStringLiteral("File transmission start"));
        //qDebug() << LessorURL;
        WebSocket.close();
        WebSocket.open(QUrl(LessorURL));
        /*bool test = WebSocket.state() == 2;
        qDebug() << WebSocket.state();
        qDebug() << test;
        while(WebSocket.state() != 3){
            WebSocket.maxAllowedIncomingFrameSize();
            WebSocket.state();
        }*/
        //fileTransmission(filename, LessorIP, port, token);
        //qDebug()<< "Transmission check";

}

void WebSocketClient::fileTransmission(QString filename, QString LessorIP, QString port, QString token){
        //QString LessorURL = "ws://" + LessorIP + ":" + port;
        QString fileNameInDirectory;
        //qDebug() << QString("filename:" + fileNameInDirectory);
        //WebSocket.sendTextMessage(QString("hash:" +  hash));
        WebSocket.sendTextMessage(QString("token:" + token));
        //qDebug() << QString("token:" + token);
        QStringList list= filename.split("/");
        QStringListIterator it(list);
        while (it.hasNext()) {
            fileNameInDirectory = it.next();
        }
        WebSocket.sendTextMessage(QString("filename:" + fileNameInDirectory));
        QFile file(filename);
        QFileInfo fileInfo(file);
        fileSize = fileInfo.size();
        if(file.open(QFile::ReadOnly)) {
            QByteArray data = file.readAll();
            hash = qHash(data)^ data.size();
            qDebug() << hash;
            WebSocket.sendTextMessage("hash:" + QString(hash));
            WebSocket.sendBinaryMessage(data);

            file.close();
            qDebug() << "File sent";// << data;
            data.clear();
        } else {

            qFatal("_CLIENT: File could not be opened!");
        }
};


void WebSocketClient::onTextMessageRecieved(QString message)
{
        qDebug() << "Message received:" << message;
        //WebSocket.sendTextMessage(QStringLiteral("File transmission start"));

        if (message == "Transmission OK!"){
            qDebug() << "The hashes match, transmission successfully completed!";
            //WebSocketClient::~WebSocketClient();
            QCoreApplication::exit(0);
        }
        if (message == "Transmission failed!"){
            if (j < 6){
            fileTransmission(filename, LessorIP, port, token);}
            else{
                qDebug() << "Aborting transmission!";
                //WebSocket.sendTextMessage("Aborting transmission!");
                QCoreApplication::exit(0);
            }
            j++;

        }


        QStringList list= message.split("|");
        if(list.at(0) == "Settings"){
            LessorIP = list.at(1);
            port = list.at(2);
            token = list.at(3);
            qDebug() << "LessorIP:" << LessorIP << "; port:" << port << "; token:" << token;
            transmission = true;
            fileTransmissionPreparation(LessorIP, port, token);
            if (WebSocket.state() == 3){
                //fileTransmission(filename, LessorIP, port, token);
         }
        }

}

void WebSocketClient::ProcessTextMessage(QString message)
{
    qDebug() << "WebSocketClient::ProcessTextMessage: " << message;

}

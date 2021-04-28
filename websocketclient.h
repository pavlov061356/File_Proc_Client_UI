#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <iostream>
#include <QtCore/QCoreApplication>

class WebSocketClient : public QObject{
 Q_OBJECT
public:
    explicit WebSocketClient(QString Filename);
    ~WebSocketClient();
    void StartClient();

signals:
    void connected();
    void closed();

private slots:
    void onConnected();
    void onTextMessageRecieved(QString message);
    void fileTransmissionPreparation(QString LessorIP, QString port, QString token);
    void fileTransmission(QString filename, QString LessorIP, QString port, QString token);
    void ProcessTextMessage(const QString message);

private:
    QWebSocket WebSocket;
    QString LessorIP;
    QString port;
    QString token;
    QString filename;
    uint hash;
    qint64 fileSize;
    int i = 0;
    int j = 1;
    bool transmission = false;

};


#endif // WEBSOCKETCLIENT_H

#ifndef MESSAGECONTROL_H
#define MESSAGECONTROL_H

#include <QObject>
#include<QtNetwork/QUdpSocket>
#include<string>
#include<iostream>
//#include <stdio>
//#include <stdlib>

using namespace std;

class MessageControl : public QObject
{
    Q_OBJECT
public:
    explicit MessageControl(QObject *parent = 0);

    void sendMessage(QString message, int facilID);
    void sendMessageToAll(QString message);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *serverSocket;
    quint16 port;

    QMap<int, QString> facilities;

};

#endif // MESSAGECONTROL_H



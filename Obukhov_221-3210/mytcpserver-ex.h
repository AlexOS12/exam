#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include "client.h"

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();
    //void slotReadClient();
private:
    QMap<int, Client*> clnts;
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    int server_status;
};
#endif // MYSERVER_H








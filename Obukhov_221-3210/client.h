#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <vector>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    explicit Client(QTcpSocket* socket, QObject *parent = nullptr);
    QTcpSocket* Socket;
    void SendtoClient(QString msg);
public slots:
    void SlotRead();
    void SlotClose();
    void sift(int *A, int i, int m, int size);
    void heap_sort(int *A, int n, int size);
private:
    void parser(QString msg);
signals:
    void Close(Client* client);
};

#endif // CLIENT_H

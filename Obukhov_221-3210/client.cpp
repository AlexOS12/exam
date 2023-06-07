#include "client.h"

Client::Client(){}

Client::Client(QTcpSocket *socket, QObject *parent)
{
    Socket = socket;
    connect(Socket, &QTcpSocket::readyRead, this, &Client::SlotRead);
    connect(Socket, &QTcpSocket::disconnected, this, &Client::SlotClose);
}

void Client::SendtoClient(QString msg)
{
    Socket->write(msg.toUtf8() + "\r\n");
}

void Client::SlotRead()
{
    while (Socket->bytesAvailable() > 0){
        QByteArray array = Socket->readAll();
        qDebug() << "[IN] " << array;
        parser(array);
    }
}

void Client::SlotClose()
{
    emit Close(this);
}

void Client::sift(int *A, int i, int m, int size)
{
    int j = i, k = i * 2 + 1;
    while (k <= m){
        if (k<m && A[k]<A[k+1]) k++;
            if (A[j] < A[k])
            { std::swap(A[j], A[k]); j = k; k = k*2+1; }
            else break;

    }
}

void Client::heap_sort(int *A, int n, int size)
{
    int i, m;

    for (i = n/2; i >= 0; i--)
        sift(A, i, n-1, size);
      // сортировка массива
      for (m = n - 1; m >= 1; m--)
      {
        std::swap(A[0], A[m]);
        sift(A, 0, m-1, size);
        QString res = "";
        for (int i = 0; i < size; i++)
            res += QString::number(A[i]) + " ";
        SendtoClient(QString::number(n - m + 1) + "\t" + res);
      }
    SendtoClient("Ready for a new task!");
}

void Client::parser(QString msg)
{
    std::vector<QString> words;

    for (QString s : msg.split('&'))
        words.push_back(s);

   if (!words.size()){ SendtoClient("Wrong INPUT!!!"); return;}
   if (words[0] != "sort") {SendtoClient("No such command!"); return;}
   if (words.size() != 3) {SendtoClient("Wrong Data set!!!"); return;}

   int step = words[1].toInt();
   std::vector<int> nums;
   for (QString n : words[2].split(' '))
       nums.push_back(n.toInt());
    int size = nums.size();
    int *A = new int[size];
    for (int i = 0; i < size; i++)
        A[i] = nums[i];

    heap_sort(A, step, size);
};


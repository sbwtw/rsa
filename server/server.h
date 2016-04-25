#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();

private:
    void receiveMessage();

private slots:
    void establishNewClient();

private:
    QTcpServer *m_server;
    QList<QTcpSocket *> *m_clientList;
};

#endif // SERVER_H

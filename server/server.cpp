#include "server.h"
#include "constants.h"

Server::Server(QObject *parent) :
    QObject(parent),
    m_server(new QTcpServer(this)),
    m_clientList(new QList<QTcpSocket *>)
{
    if (!m_server->listen(QHostAddress::Any, SERVER_PORT))
        qDebug() << m_server->errorString();

    connect(m_server, &QTcpServer::newConnection, this, &Server::establishNewClient);
}

Server::~Server()
{
    // TODO free
}

void Server::receiveMessage()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    const QByteArray str = socket->readAll();

    qDebug() << "server recv: " << str;

    for (QTcpSocket *sock : *m_clientList)
    {
        sock->write(str);
        sock->flush();
    }
}

void Server::establishNewClient()
{
    QTcpSocket *socket = m_server->nextPendingConnection();

    connect(socket, &QTcpSocket::readyRead, this, &Server::receiveMessage);

    m_clientList->append(socket);
}

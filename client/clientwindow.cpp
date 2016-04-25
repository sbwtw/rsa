#include "clientwindow.h"
#include "constants.h"

#include <QVBoxLayout>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent) :
    QFrame(parent),
    m_textArea(new QPlainTextEdit),
    m_messageEdit(new QLineEdit),
    m_sendButton(new QPushButton),

    m_socket(new QTcpSocket(this))
{
    m_textArea->setReadOnly(true);
    m_sendButton->setText(tr("Send"));

    QHBoxLayout *sendLayout = new QHBoxLayout;
    sendLayout->addWidget(m_messageEdit);
    sendLayout->addWidget(m_sendButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_textArea);
    mainLayout->addLayout(sendLayout);

    setLayout(mainLayout);

    connect(m_sendButton, &QPushButton::clicked, this, &ClientWindow::sendMessage);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientWindow::readMessage);

    m_socket->connectToHost(SERVER_ADDR, SERVER_PORT);
}

void ClientWindow::sendMessage()
{
    const QString msg = m_messageEdit->text();
    m_messageEdit->clear();

    m_socket->write(msg.toStdString().c_str());
    m_socket->flush();
}

void ClientWindow::readMessage()
{
    const QString msg = m_socket->readAll();

    m_textArea->appendPlainText(msg);
}

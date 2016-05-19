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
    BigNumber n1, n2;
    n1 = RSA_NUMBER1;
    n2 = RSA_NUMBER2;
    m_rsa.setPublicKey(n1, n2);
    m_rsa.dumpInfo();

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

    BigNumber number;
    number = msg.toStdString();
    number = m_rsa.encode(number);

    m_socket->write(number.toStdString().c_str());
    m_socket->waitForBytesWritten();
    m_socket->flush();

    m_textArea->appendPlainText("sent: \n" + msg);
}

void ClientWindow::readMessage()
{
    const QString msg = m_socket->readAll();

    BigNumber number;
    number = msg.toStdString();

    m_textArea->appendPlainText("recv: \n" + msg);
    m_textArea->appendPlainText("decode: ");
    m_textArea->appendPlainText(m_rsa.decode(number).toStdString().c_str());
}

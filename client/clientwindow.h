#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QFrame>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>

#include "rsa.h"

class ClientWindow : public QFrame
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);

private slots:
    void sendMessage();
    void readMessage();

private:
    QPlainTextEdit *m_textArea;
    QLineEdit *m_messageEdit;
    QPushButton *m_sendButton;

    QTcpSocket *m_socket;

    RSA m_rsa;
};

#endif // CLIENTWINDOW_H

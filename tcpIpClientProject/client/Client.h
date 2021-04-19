#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QObject>
#include <iostream>
#include <string>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <vector>
#include <QSpinBox>
#include <QAbstractSocket>
#include "Interface/iclient.h"
#include "graph/Interface/igraph.h"
#include "configuration/configuration.h"



class ClientOrdi: public IClient
{
    Q_OBJECT

public:
    ClientOrdi(IGraph &igraph);
    ~ClientOrdi();
    double getTempData();


private slots:

    void connectToTheServer();
    void receiveData();
    void disconnectFromServer();
    void errorConnectionHandler(QAbstractSocket::SocketError socketError);
    void connectionController();


private:
    QLabel *m_infoClient, *m_serverPortShow, *m_serverHostAdress;
    QLabel *m_messageReceived;
    QPushButton *m_clientConnectButton, *m_clientDeconnectButton;
    QVBoxLayout *m_clientLayout;
    QLineEdit *m_serverHostAdressText;
    QSpinBox *m_serverPort;
    QTcpSocket *m_clientSocket;
    IGraph &m_igraph;
    QString m_message ;
    QString m_tabMessages[cfig::ClientConfig::tabSize];
    double m_tempMessage, m_speedSetMessage;
    long long m_tempMessageTime;

};

#endif // CLIENT_H

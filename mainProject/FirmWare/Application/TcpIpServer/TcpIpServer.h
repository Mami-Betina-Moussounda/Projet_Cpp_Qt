#ifndef TCPIPSERVER_H
#define TCPIPSERVER_H


#include <QtNetwork>
#include <QObject>
#include <iostream>
#include <string>
#include <vector>
#include <QAbstractSocket>
#include <QTimer>
#include <QDateTime>
#include "FirmWare/Application/ControllerWorker/iworker.h"
#include <sstream>
#include "Configurations/configuration.h"


namespace app
{

namespace tcps
{


class TcpIpServer: public app::ctrw::iWorker
{
    Q_OBJECT
public:
    TcpIpServer();
    ~TcpIpServer();

public slots:
    void initialize() final;
    void sendData(QString msg);

private slots:
    void connectNewClient();
    void deconnectAClient();




private:

    QVector <QTcpSocket*> m_clientSocketTable;
    quint16 m_serverPort;
    QTcpServer *m_server;
    QTcpSocket *m_clientSocket, *m_clientSenderSocket;



};

};
};

#endif // TCPIPSERVER_H

#include "TcpIpServer.h"
#include <QDebug>


namespace app
{

namespace tcps
{

/* This component is the server part of the project
   it allows the communication in tcpIp with a client side
   in order to transmit info: temperature, speedset et speedRun */

TcpIpServer::TcpIpServer()
{

    std:: cout << QThread::currentThreadId()<<"  thread ID in the constructeur server "<< std::endl<<std::endl;

}


void TcpIpServer::initialize()
{
    std:: cout << QThread::currentThreadId()<<"  thread ID in the method initialize of the server "<< std::endl<<std::endl;

    m_serverPort = cfig::TcpIpServerConfig::serverPort;

    m_server = new QTcpServer(this);


    if(!m_server->listen(QHostAddress::Any,m_serverPort))

    {
        std::cout<<"there is a connection problem"<< std::endl;
    }
    else
    {
        std::cout<<"Successful connection "<< m_server->serverPort()<< std::endl;

        qDebug () << "Server new connection status: " << connect(m_server, SIGNAL(newConnection()), this, SLOT(connectNewClient()));

    }

}

void TcpIpServer::connectNewClient()
{
    m_clientSocket = new QTcpSocket;

    m_clientSocket = m_server->nextPendingConnection();
    m_clientSocketTable.push_back(m_clientSocket);


    std:: cout << QThread::currentThreadId()<<"  thread ID in the method connectNewClient "<< std::endl<<std::endl;

    connect(m_clientSocket, SIGNAL(disconnected()), this, SLOT(deconnectAClient()));

}



void TcpIpServer::deconnectAClient()
{
    QTcpSocket *senderClientSocket = qobject_cast<QTcpSocket *>(sender());
    senderClientSocket->deleteLater();
    m_clientSocketTable.removeOne(senderClientSocket);
}



void TcpIpServer::sendData( QString msg)
{

    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);


    out<<msg;


    for (int nbreClient=0;nbreClient<m_clientSocketTable.size();nbreClient++)
    {

        m_clientSocketTable[nbreClient]->write(paquet);

    }

    std:: cout << QThread::currentThreadId()<<" thread ID in the server component" << std::endl<< std::endl;
    std:: cout <<" Data sent: n°" <<msg.toStdString()<< std::endl<< std::endl;
    std:: cout <<" Number of connected clients:  "<<m_clientSocketTable.size()<<std::endl;

}


TcpIpServer::~TcpIpServer()
{

}



};
};



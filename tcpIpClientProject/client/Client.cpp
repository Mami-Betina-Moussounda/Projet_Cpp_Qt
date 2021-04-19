#include "Client.h"

ClientOrdi::ClientOrdi(IGraph &igraph):m_infoClient(nullptr),m_serverPortShow(nullptr),m_serverHostAdress(nullptr),
    m_messageReceived(nullptr),
    m_clientConnectButton(nullptr),m_clientDeconnectButton(nullptr),
    m_clientLayout(nullptr),
    m_serverHostAdressText(nullptr),
    m_serverPort(nullptr),
    m_clientSocket(nullptr),
    m_igraph(igraph)


{

    m_clientSocket = new QTcpSocket(this);

    m_infoClient = new QLabel ("connection status...");
    m_messageReceived = new QLabel("waiting for messages");

    m_messageReceived->setScaledContents(true);

    m_serverPortShow = new QLabel ("Port server");
    m_serverHostAdress= new QLabel("Host Address");
    m_clientConnectButton= new QPushButton ("Connect");
    m_clientDeconnectButton = new QPushButton("Deconnect");
    m_serverPort = new QSpinBox;
    m_serverPort->setRange(cfig::ClientConfig::minRangeServerPort,cfig::ClientConfig::maxRangeServerPort); // ports available by default

    m_serverHostAdressText= new QLineEdit;
    m_serverHostAdressText->setText("192.168.1.43");

    m_clientLayout= new QVBoxLayout;


    m_clientLayout->addWidget (m_serverPortShow);
    m_clientLayout->addWidget(m_serverPort);
    m_clientLayout->addWidget(m_serverHostAdress);
    m_clientLayout->addWidget(m_serverHostAdressText);
    m_clientLayout->addWidget(m_clientConnectButton);
    m_clientLayout->addWidget(m_infoClient);
    m_clientLayout->addWidget(m_messageReceived);
    m_clientLayout->addWidget(m_clientDeconnectButton);

    setLayout(m_clientLayout);

    setWindowTitle("CLIENT");

    connect(m_clientConnectButton,SIGNAL(clicked()), this, SLOT(connectToTheServer()));
    connect(m_clientDeconnectButton,SIGNAL(clicked()), this, SLOT(disconnectFromServer()));
    connect(m_clientSocket,SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(m_clientSocket,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorConnectionHandler(QAbstractSocket::SocketError)));

}

ClientOrdi::~ClientOrdi()
{

}

void ClientOrdi::connectToTheServer()
{
    m_igraph.clearLists();

    m_infoClient->setText("connection status...");
    m_messageReceived->setText("waiting for messages");
    m_clientConnectButton->setEnabled(false);
    m_clientSocket->abort();
    m_clientSocket->connectToHost(m_serverHostAdressText->text(),
                                  static_cast<quint16>(m_serverPort->value()));// The value of the server port must have a quint16 as type
    connect(m_clientSocket,SIGNAL(connected()), this, SLOT(connectionController())); // Signal emitted when the socket has a succeded connection to the server

}

void ClientOrdi::receiveData()
{
    int cntMessages=0;

    m_messageReceived->clear();

    QDataStream in (m_clientSocket);
    in >> m_message;

    std::cout<<m_message.toStdString()<<std::endl;

    QTextStream readMessage(&m_message);

    do
    {
        m_tabMessages[cntMessages]=readMessage.readLine();

        cntMessages++;
    }while (!readMessage.atEnd());


    cntMessages=0;


    if( cfig::ClientConfig::MsgId==m_tabMessages[0].toInt())// Each message from the server is composed by a first char which is a number
                                                            // Its value is checked before sending data to the graph
    {
        m_tempMessage= m_tabMessages[cfig::ClientConfig::tempMsgPosition].toDouble()* cfig::ClientConfig::precisionData;
        m_tempMessageTime =m_tabMessages[cfig::ClientConfig::timeMsgPosition].toLongLong();
        m_igraph.getTempData(m_tempMessage,m_tempMessageTime);
    }


    m_tabMessages->clear();

    m_clientConnectButton->setEnabled(true);

}


void ClientOrdi::disconnectFromServer()
{
    m_clientSocket->disconnectFromHost();
    m_infoClient->setText("deconnection from the server");
}

void ClientOrdi::errorConnectionHandler(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::SocketAccessError:
        m_infoClient->setText( " ERROR: application lacked the required privileges");
        break;

    case QAbstractSocket::HostNotFoundError:
        m_infoClient->setText( " ERROR: server address not found");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        m_infoClient->setText( " ERROR: server refuse the connection");
        break;

    case QAbstractSocket::RemoteHostClosedError:
        m_infoClient->setText( " ERROR: connection stoped from server");
        break;

    case QAbstractSocket::AddressInUseError:
        m_infoClient->setText( " ERROR: this client's socket is already in use");

        break;

    default:
        m_infoClient->setText(m_clientSocket->errorString());

    }

    m_clientConnectButton->setEnabled(true);// Allow to reset the connection
}

void ClientOrdi::connectionController()

{
    m_infoClient->setText("Connected !");
    m_igraph.showGraph();

}

double ClientOrdi::getTempData()
{

    return m_tempMessage;
}



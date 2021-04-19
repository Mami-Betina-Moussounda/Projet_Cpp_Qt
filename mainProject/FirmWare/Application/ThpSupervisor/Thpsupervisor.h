#ifndef THPSUPERVISOR_H
#define THPSUPERVISOR_H



#include "FirmWare/MiddleWare/TempReceptor/TempReceptor.h"
#include "FirmWare/Application/TcpIpServer/TcpIpServer.h"
#include "FirmWare/Application/ControllerWorker/iworker.h"
#include "Configurations/configuration.h"

#include <QTimer>
#include <QObject>
#include <stdint.h>
#include <QElapsedTimer>

namespace app
{

namespace thpr
{

class ThpSupervisor: public app::ctrw::iWorker // inheritancefrom a worker because this component with be execute
                                               // in a specific thread
{
     Q_OBJECT

public:

    // No interface is used for the TCP server because it is impossible to perform a Qt connect on
    // a virtual method (polymorphism is dynamically resolved while a connect is statically resolved)
    ThpSupervisor(app::tcps::TcpIpServer &server);
    void setTempMsg(int32_t tempToSend, qint64 tempTimeToSend);

    ~ ThpSupervisor()
    {}

public slots:

    void initialize()final;
signals:
       void trigSendData(QString msg);

private:
    void UpdateTempData();

    mid::datar::TempReceptor m_tempReceptor;
    app::tcps::TcpIpServer &m_server;

    QTimer *m_timer;

    struct s_Temp
    {
        int32_t temp;
        qint64 tempTime;
    };

    static const uint8_t cTempMsgId = 1U;

};


};
};

#endif // THPSUPERVISOR_H

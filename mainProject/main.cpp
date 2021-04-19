

#include <QCoreApplication>
#include "FirmWare/MiddleWare/TempReceptor/bme280_htp_sensor/bme280_htp_sensor.h"
#include "FirmWare/MiddleWare/TempReceptor/TempReceptor.h"
#include <string>
#include <iostream>
#include "FirmWare/Application/TcpIpServer/TcpIpServer.h"
#include "FirmWare/Application/ThpSupervisor/Thpsupervisor.h"
#include "FirmWare/Application/ControllerWorker/Controller.h"
#include "FirmWare/Application/ControllerWorker/iworker.h"
#include <QThread>
#include <iostream>
#include "FirmWare/Application/ControllerWorker/Controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    app::tcps::TcpIpServer server;
    app::ctrw::Controller TcpIpServerCtrl(server);

    app::thpr::ThpSupervisor thpSup(server);
    app::ctrw::Controller ThpsupervisorCtrl(thpSup);

    std:: cout << QThread::currentThreadId() <<" thread ID of the main " << std::endl << std::endl;

    return a.exec();
}

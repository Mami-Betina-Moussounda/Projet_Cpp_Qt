#include "Thpsupervisor.h"
#include <iostream>

#include <chrono>
#include <QThread>


namespace app
{

namespace thpr
{

/* This objects manage a middleware object which communicates in I2C with a temperature sensor.
   from this objects, the sensor is triggered, data are collected and sent to another object: a server */

ThpSupervisor::ThpSupervisor( app::tcps::TcpIpServer &server): app::ctrw::iWorker(),
    m_server(server), m_timer(nullptr)

{
   m_timer = new QTimer(this);
   connect(m_timer, &QTimer::timeout, this, &ThpSupervisor::UpdateTempData);
   connect(this, &ThpSupervisor::trigSendData, &m_server, &app::tcps::TcpIpServer::sendData);
}



void ThpSupervisor::initialize()
{

    m_tempReceptor.TempSensorInit(); // Trigger of the temperature middleWare part

    m_timer->start(cfig::ThpSupervisorConfig::timerFrequence);
}


void ThpSupervisor::UpdateTempData()
{


    m_tempReceptor.sendTempData(); // Init the data reading from the sensor
    int32_t tempToSend = m_tempReceptor.returnTemp(); // Read temperatures values from sensor
    qint64 tempTimeToSend = m_tempReceptor.returnTempTime(); // Read time values from sensor

    std:: cout <<" thread ID in the component ThpSupervisor "<< QThread::currentThreadId() << std::endl<<std::endl;


    // Updating data for other components
    setTempMsg(tempToSend, tempTimeToSend);

}

void ThpSupervisor::setTempMsg(int32_t tempToSend, qint64 tempTimeToSend)

{
    s_Temp tempStruct;
    tempStruct.temp=tempToSend;
    tempStruct.tempTime=tempTimeToSend;

    QString messageToSend = QString::number(cTempMsgId) + "\n" +
            QString ::number (tempStruct.temp)+"\n" +
            QString ::number (tempStruct.tempTime);

    emit trigSendData(messageToSend);
}


};
};


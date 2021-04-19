#include "TempReceptor.h"
#include <iostream>



namespace mid
{

namespace datar
{

TempReceptor::TempReceptor():m_temperature(0),m_pressure(0),m_humidity(0)
{

}

TempReceptor::~TempReceptor()
{

}

void TempReceptor::TempSensorInit()
{
     m_launchSensor.Initialize();

}

void TempReceptor::sendTempData() //  this method exits only for calling receiveTempData
{
    receiveTempData();
}


void TempReceptor::receiveTempData() // This method is private, so that, retrieving data process shouldn' be easily accessible
{

    m_launchSensor.GetData(m_humidity, m_temperature, m_pressure, m_tempTime);

}

int32_t TempReceptor:: returnTemp() // This method has been created because it was necessary to have an access to the class attributes.
                                  // Moreover, "receiveTempData" method is a private member
{
    return m_temperature;
}

qint64 TempReceptor::returnTempTime()
{
    return  m_tempTime;
}



};
};

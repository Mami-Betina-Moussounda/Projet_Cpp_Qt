#ifndef TEMPRECEPTOR_H
#define TEMPRECEPTOR_H

#include "bme280_htp_sensor/bme280_htp_sensor.h"
#include <QTimer>
#include <stdint.h>

namespace mid
{

namespace datar
{


class TempReceptor : public QObject
{

public:
    TempReceptor();
    virtual ~ TempReceptor();

    void sendTempData();
    void TempSensorInit();
    int32_t returnTemp();
    qint64 returnTempTime();


private:
      void receiveTempData();
      mid::htp::Bme280HtpSensor m_launchSensor;
      int32_t m_temperature;
      uint32_t m_pressure;
      uint32_t m_humidity;
      qint64 m_tempTime;


};
};
};

#endif // TEMPRECEPTOR_H

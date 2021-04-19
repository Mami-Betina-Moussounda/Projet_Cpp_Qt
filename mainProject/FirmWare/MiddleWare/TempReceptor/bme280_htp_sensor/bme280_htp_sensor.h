#ifndef BME280_HTP_SENSOR_H
#define BME280_HTP_SENSOR_H

#include <QObject>
#include "bme280.h"
#include <stdint.h>

namespace mid
{

namespace htp
{

class Bme280HtpSensor : public QObject
{
    Q_OBJECT
public:
    explicit Bme280HtpSensor(QObject *parent = nullptr,
                             int i_DeviceAddress = 0x77);

    bool Initialize();

    bool GetData(uint32_t& o_Humidity,
                 int32_t& o_Temperature,
                 uint32_t& o_Pressure,
                 qint64& dataTime);


private:
    static void DelayMs(uint32_t period);
    static int8_t I2cRead(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
    static int8_t I2cWrite(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
    bool ConvertData(bme280_data& io_DataConv);

    int mDeviceAddress;
    bool mIsInitialized;
    uint32_t mHumidity;
    int32_t mTemperature;
    uint32_t mPressure;
    bme280_dev mDev;
};

}
}


#endif // BME280_HTP_SENSOR_H

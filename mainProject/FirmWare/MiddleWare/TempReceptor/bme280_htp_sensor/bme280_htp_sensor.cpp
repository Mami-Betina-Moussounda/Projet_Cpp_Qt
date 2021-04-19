#include "bme280_htp_sensor.h"
#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <QDateTime>


namespace mid
{

namespace htp
{

int gI2Chandler = -1;


Bme280HtpSensor::Bme280HtpSensor(QObject *parent,
                                 int i_DeviceAddress) :
    QObject(parent),
    mDeviceAddress(i_DeviceAddress),
    mIsInitialized(false),
    mHumidity(0),
    mTemperature(0),
    mPressure(0)
{
    memset(&mDev, 0, sizeof(mDev));
}

bool Bme280HtpSensor::Initialize()
{
    //struct bme280_dev dev;

    /* Variable to define the result */
    int8_t rslt = BME280_OK;

    /* Make sure to select BME280_I2C_ADDR_PRIM or BME280_I2C_ADDR_SEC as needed */
    mDev.dev_id = BME280_I2C_ADDR_PRIM;

    /* dev.dev_id = BME280_I2C_ADDR_SEC; */
    mDev.intf = BME280_I2C_INTF;
    mDev.read = I2cRead;
    mDev.write = I2cWrite;
    mDev.delay_ms = DelayMs;

    gI2Chandler = wiringPiI2CSetup(mDeviceAddress);

    if(gI2Chandler >= 0)
    {
        /* Initialize the bme280 */
        rslt = bme280_init(&mDev);

        if (rslt == BME280_OK)
        {
            /* Variable to define the selecting sensors */
            uint8_t settings_sel = 0;

            mDev.settings.osr_h = BME280_OVERSAMPLING_1X;
            mDev.settings.osr_p = BME280_OVERSAMPLING_16X;
            mDev.settings.osr_t = BME280_OVERSAMPLING_2X;
            mDev.settings.filter = BME280_FILTER_COEFF_16;

            settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

            /* Set the sensor settings */
            rslt = bme280_set_sensor_settings(settings_sel, &mDev);

            if (rslt != BME280_OK)
            {
                mIsInitialized = true;
            }
            else
            {
                //ERROR:
                mIsInitialized = false;
            }
        }
        else
        {
            //ERROR:
            mIsInitialized = false;
        }
    }
    else
    {
        //ERROR:
        mIsInitialized = false;
    }
}

bool Bme280HtpSensor::GetData(  uint32_t& o_Humidity,
                                int32_t& o_Temperature,
                                uint32_t& o_Pressure,
                                qint64& dataTime)
{
    bool isOk;
    struct bme280_data comp_data;

    if(ConvertData(comp_data))
    {
        isOk = true;
        o_Temperature = comp_data.temperature;
        o_Pressure = comp_data.pressure;
        o_Humidity = comp_data.humidity;
        dataTime = QDateTime::currentMSecsSinceEpoch();

    }
    else
    {
        isOk = false;
    }

    return isOk;
}

void Bme280HtpSensor::DelayMs(uint32_t period)
{
    /* Milliseconds convert to microseconds */
    usleep(period * 1000);
}

int8_t Bme280HtpSensor::I2cRead(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t status = BME280_OK;

    if(gI2Chandler >= 0)
    {
        if(len >= 1U)
        {
            for(uint16_t byteNbr = 0U; byteNbr < len; byteNbr++)
            {
                int dataToRead = wiringPiI2CReadReg8(gI2Chandler, reg_addr + byteNbr);
                data[byteNbr] = dataToRead & 0xFF;
            }
        }
        else
        {
            status = BME280_E_COMM_FAIL;
        }
    }
    else
    {
        status = BME280_E_DEV_NOT_FOUND;
    }

    return status;
}

int8_t Bme280HtpSensor::I2cWrite(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t status = BME280_OK;

    if(gI2Chandler >= 0)
    {
        if(len >= 1U)
        {
            for(uint16_t byteNbr = 0U; byteNbr < len; byteNbr++)
            {
                int dataToWrite = data[byteNbr];
                wiringPiI2CWriteReg8(gI2Chandler, reg_addr + byteNbr, dataToWrite );
            }
        }
        else
        {
            status = BME280_E_COMM_FAIL;
        }
    }
    else
    {
        status = BME280_E_DEV_NOT_FOUND;
    }

    return status;
}

bool Bme280HtpSensor::ConvertData(bme280_data& io_DataConv)
{
    bool dataConverted = false;
    int8_t status = BME280_OK;

    if(gI2Chandler >= 0)
    {
        status = bme280_set_sensor_mode(BME280_FORCED_MODE, &mDev);
        if (status == BME280_OK)
        {
            uint32_t req_delay = bme280_cal_meas_delay(&mDev.settings);
            mDev.delay_ms(req_delay);
            status = bme280_get_sensor_data(BME280_ALL, &io_DataConv, &mDev);

            if(status == BME280_OK)
            {
                dataConverted = true;
            }
            else
            {
                //ERROR: Nothing to do;
            }
        }
        else
        {
            //ERROR: Nothing to do;
        }
    }
    else
    {
        status = BME280_E_DEV_NOT_FOUND;
    }

    return dataConverted;
}

}
}

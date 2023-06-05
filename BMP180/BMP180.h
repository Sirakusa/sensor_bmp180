#ifndef BMP180_H
#define BMP180_H

#include "mbed.h"

class BMP180 {
    
public:

    typedef enum{
        ULTRA_LOW_POWER = 0, ///< 1 pressure sample
        STANDARD = 1, ///< 2 pressure samples
        HIGH_RESOLUTION = 2, ///< 4 pressure samples
        ULTRA_HIGH_RESOLUTION = 3 ///< 8 pressure samples
    } oversampling_t;

    BMP180(PinName sda, PinName scl);
    BMP180(I2C *i2c);
    ~BMP180();

    int init(void);
    int reset(void);
    int checkId(void);
    int startPressure(BMP180::oversampling_t oss);
    int getPressure(int *pressure);
    int startTemperature(void);
    int getTemperature(float *tempC);

private:

    typedef union {
        uint16_t value[11];
        struct {
            int16_t ac1;
            int16_t ac2;
            int16_t ac3;
            uint16_t ac4;
            uint16_t ac5;
            uint16_t ac6;
            int16_t b1;
            int16_t b2;
            int16_t mb;
            int16_t mc;
            int16_t md;
        };
    } calibration_t;
    
    I2C *i2c_;
    bool i2c_owner;

    BMP180::calibration_t calib;
    int32_t b5;
    BMP180::oversampling_t oss_;
};

#endif
#include "mbed.h"

#include "BMP180.h"

I2C i2c(I2C_SDA, I2C_SCL);
BMP180 bmp180(&i2c);

int main(void) {
 
    while(1) {
        if (bmp180.init() != 0) {
            printf("Error communicating with BMP180\n");
        } else {
            printf("Initialized BMP180\n");
            break;
        }
        ThisThread::sleep_for(1ms);
    }

    while(true) {
        bmp180.startTemperature();
        ThisThread::sleep_for(5ms);     // Wait for conversion to complete
        float temp;
        if(bmp180.getTemperature(&temp) != 0) {
            printf("Error getting temperature\n");
            continue;
        }

        bmp180.startPressure(BMP180::ULTRA_LOW_POWER);
        ThisThread::sleep_for(10ms);    // Wait for conversion to complete
        int pressure;
        if(bmp180.getPressure(&pressure) != 0) {
            printf("Error getting pressure\n");
            continue;
        }

        printf("Pressure = %d Pa Temperature = %f C\n", pressure, temp);
        ThisThread::sleep_for(1ms);
    }
}
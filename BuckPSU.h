/**
 * BuckPSU.h
 * Library for interfacing with UART on Chinese DC-DC converters.
 * Ben James (benjames.io)
 */

#ifndef BuckPSU_h
#define BuckPSU_h

#include "Arduino.h"

class BuckPSU
{
    public:
        BuckPSU(Stream &port);

        void setVoltageMilliVolts(uint16_t millivolts);
        void setCurrentMilliAmps(uint16_t milliamps);
        void enableOutput(bool status);

        uint16_t readVoltageMilliVolts();
        uint16_t readCurrentMilliAmps();
        bool getOutputEnabled();

    private:
        void intToFourCharStr(char *buf, uint16_t input);   
        Stream *_port;
};

#endif
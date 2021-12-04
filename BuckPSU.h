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
	void enableAuto(bool status);
	void enableLock(bool status);
	void enableDisplay(bool status);
	void setMemory(int loc);
	void getMemory(int loc);

        uint16_t readVoltageMilliVolts();
        uint16_t readCurrentMilliAmps();
	uint16_t readSetMilliVolts();
	uint16_t readSetMilliAmps();
	uint16_t readTimer();
	uint16_t readCapacity();
		
        bool getOutputEnabled();
	bool getAutoEnabled();
	bool getLockEnabled();


    private:
        void intToFourCharStr(char *buf, uint16_t input);   
        Stream *_port;
};

#endif

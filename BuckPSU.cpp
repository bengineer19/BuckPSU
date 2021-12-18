/**
 * BuckPSU.cpp
 * 
 * Library for interfacing with UART on Chinese DC-DC converters.
 * Ben James (benjames.io)
 *
 * The port used can be any of type `Stream`. 
 * This has the side effect of needing to manually begin the Serial
 * port (if it's a Serial port that's used), but hopefully means that
 * this lib is more flexible.
 
 some poorly written documentation for the protocol from Drok:
 https://www.droking.com/cs/support/topic/200220-dc-dc-buck-converter-uart/#post-35186
 
 Ben's realted blog post:
 https://blog.benjames.io/2018/06/29/secret-uart-on-chinese-dcdc-converters/
 
 */

#include "Arduino.h"
#include "BuckPSU.h"


/**
 * Constructor.
 * The Serial port passed in must be manually 'begun' in the main
 * program. 
 * This is because the Stream class is used to provide extensiblity,
 * but Stream has no way of beginning a Serial port.
 */
BuckPSU::BuckPSU(Stream &port)
{
    _port = &port;
}

/**
 * Turns the buck PSU output on or off.
 * @param status true to enable output, false to disable output
 */
void BuckPSU::enableOutput(bool status)
{
    if(status){
        _port->println("awo1");
    }
    else
    {
        _port->println("awo0");
    }
}
/**
 * Enable or disable the power supply being on it's ON mode when it gets power applied.
 * @param status true to enable output, false to disable output
 */


void BuckPSU::enableAuto(bool status)
{
    if(status){
        _port->println("awy1");
    }
    else
    {
        _port->println("awy0");
    }
}

/**
 * Enable or disable the lock on the button interface for local control.
 * @param status true to enable lock, false to disable lock
 */
void BuckPSU::enableLock(bool status)
{
    if(status){
        _port->println("awl1");
    }
    else
    {
        _port->println("awl0");
    }
}
/**
 * Enable or disable the power supply numberic display.
 * @param status true to enable display, false to disable display
 */
void BuckPSU::enableDisplay(bool status)
{
    if(status){
        _port->println("awd1");
    }
    else
    {
        _port->println("awd0");
    }
}
/**
 * Set memory location - location 0 is default for power up there are 10 locations (0-9).
 * @param memoy location to store settings at
 */
void BuckPSU::setMemory(int loc)
{
	char msg[8];
	sprintf(msg, "aws%d", loc);
    _port->println(msg);
}
/**
 * Recall location - location 0 is defualt for power up there are 10 locations (0-9).
 * @param memoy location to store settings at
 */
void BuckPSU::getMemory(int loc)
{
	char msg[8];
	sprintf(msg, "awm%d", loc);
    _port->println(msg);
}

/**
 * Read the status of the PSU output
 * @return bool of whether the output is enabled or not
 */
bool BuckPSU::getOutputEnabled()
{
    char msg[16];

    // Request output status
    _port->println("aro");
    _port->readBytes(msg, 16);

    return (msg[13] == '1') ? true : false;
}
/**
 * Read the status of the PSU output state on power up
 * @return bool of whether the auto output is enabled or not
 */
bool BuckPSU::getAutoEnabled()
{
    char msg[16];

    // Request output status
    _port->println("ary");
    _port->readBytes(msg, 16);

    return (msg[13] == '1') ? true : false;
}
/**
 * Read the status if the main buttons, local interface are enabled or not
 * @return bool of whether the main button interface is enabled or not
 */


bool BuckPSU::getLockEnabled()
{
    char msg[16];

    // Request output lock status
    _port->println("arl");
    _port->readBytes(msg, 16);

    return (msg[13] == '1') ? true : false;
}

/**
 * Reads the current voltage on the OUTPUT (not the voltage that's set).
 * @return voltage in millivolts
 */
uint16_t BuckPSU::readVoltageMilliVolts()
{
    char header[10];
    char msg[4];
    char footer[2];

    // Request voltage reading 
    _port->println("aru");

    _port->readBytes(header, 10);
    _port->readBytes(msg, 4);
    _port->readBytes(footer, 2);

    // Convert byte messsage to int and return as millivolts
    return atoi(msg) * 10;
}

/**
 * Reads the current timer in minutes
 * @return minutes
 */

uint16_t BuckPSU::readTimer()
{
    char header[10];
    char msg[4];
    char footer[2];

    // Request timer reading 
    _port->println("art");

    _port->readBytes(header, 8);
    _port->readBytes(msg, 6);
    _port->readBytes(footer, 2);

    // Convert byte messsage to int and return as millivolts
    return atoi(msg);
}

/**
 * Reads the capacity in minutes
 * @return Amp Hours
 */

uint16_t BuckPSU::readCapacity()
{
    char header[10];
    char msg[4];
    char footer[2];

    // Request capacity reading 
    _port->println("arc");

    _port->readBytes(header, 8);
    _port->readBytes(msg, 6);
    _port->readBytes(footer, 2);

    // Convert byte messsage to int and return as millivolts
    return atoi(msg);
}

/**
 * Reads the current through the OUTPUT (not the current limit that's set).
 * @return Current in milliamps
 */

uint16_t BuckPSU::readCurrentMilliAmps()
{
    char header[10];
    char msg[4];
    char footer[2];

    // Request voltage reading 
    _port->println("ari");

    _port->readBytes(header, 10);
    _port->readBytes(msg, 4);
    _port->readBytes(footer, 2);

    // Convert byte messsage to int and return as milliamps
    return atoi(msg) * 10;
}

/**
 * Reads the current set point.
 * @return Current in milliamps
 */

uint16_t BuckPSU::readSetMilliAmps()
{
    char header[10];
    char msg[4];
    char footer[2];

    // Request voltage reading 
    _port->println("ara");

    _port->readBytes(header, 10);
    _port->readBytes(msg, 4);
    _port->readBytes(footer, 2);

    // Convert byte messsage to int and return as milliamps
    return atoi(msg) * 10;
}

/**
 * Reads the voltage set point.
 * @return Volts in milliamps
 */

uint16_t BuckPSU::readSetMilliVolts()
{
    char header[10];
    char msg[4];
    char footer[2];

    // Request voltage reading 
    _port->println("arv");

    _port->readBytes(header, 10);
    _port->readBytes(msg, 4);
    _port->readBytes(footer, 2);

    // Convert byte messsage to int and return as milliamps
    return atoi(msg) * 10;
}

/**
 * Convert an int (usually millivolts or milliamps) to the format
 * required by the PSU, which is four characters up to e-2.
 * Eg 12340 should return '1234', 150 should return '0015'
 *
 * @param buf   char array to fill with conversion output
 * @param input The integer to convert
 */
void BuckPSU::intToFourCharStr(char *buf, uint16_t input)
{   
    // Convert from milli to centi
    input /= 10;
    // Iterate through units, tens, hundreds etc
    for(int digit = 0; digit < 4; digit++)
    {   
        buf[3 - digit] = ((input / ((int) pow(10, digit))) % 10) + '0'; 
    }
}

/**
 * Set the PSU voltage (doesn't neccessary enable the output)
 * @param millivolts The voltage to set
 */
void BuckPSU::setVoltageMilliVolts(uint16_t millivolts)
{
    char voltage[5];
    intToFourCharStr(voltage, millivolts);
    // Terminate char array
    voltage[4] = '\0';

    // Send command to PSU
    _port->print("awu");
    _port->println(voltage);
}

/**
 * Set the PSU current limit
 * @param milliamps The current limit to set in milliamps
 */
void BuckPSU::setCurrentMilliAmps(uint16_t milliamps)
{
    char current[5];
    intToFourCharStr(current, milliamps);
    // Terminate char array
    current[4] = '\0';

    // Send command to PSU
    _port->print("awi");
    _port->println(current);
}

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
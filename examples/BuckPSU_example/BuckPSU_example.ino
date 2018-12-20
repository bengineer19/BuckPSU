#include <BuckPSU.h>

BuckPSU psu(Serial1);

void setup()
{
    Serial.begin(9600);

    Serial.println("Initialising PSU...");
    // My Chinese DC-DC converter uses 4800 baud
    Serial1.begin(4800);

    psu.setVoltageMilliVolts(12000);
    psu.setCurrentMilliAmps(100);
    psu.enableOutput(true);
}

void loop()
{
    Serial.print("Voltage (mV): ");
    Serial.print(psu.readVoltageMilliVolts());
    Serial.print("\tCurrent (mA): ");
    Serial.print(psu.readCurrentMilliAmps());
    Serial.print("\tOutput enabled?: ");
    Serial.println(psu.getOutputEnabled());

    delay(500);
}

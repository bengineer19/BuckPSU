# BuckPSU
Arduino library for inexpensive (~$30) remotely controllable and monitored DC-DC converters with spport of additional commands -  forked from the great work from Ben James
https://github.com/bengineer19/BuckPSU.

 Ben's realted blog post:
 https://blog.benjames.io/2018/06/29/secret-uart-on-chinese-dcdc-converters/

 Some poorly written documentation for the protocol from Drok:
 https://www.droking.com/cs/support/topic/200220-dc-dc-buck-converter-uart/#post-35186


|Library function| Prototol command |  Use |
| ------------- | ------------- | ------------- |
| setVoltageMilliVolts(uint16_t millivolts) | awu (milivolts) | Sets output Volage in mV |
| setCurrentMilliAmps(uint16_t milliamps) | awi (miliamps) | Sets output Current in mA |
| enableOutput(bool status) | awo1 / awo0 | Enables/Disables the Output |
| enableAuto(bool status) | awy1 / awy0 | Enables/Disables if output enabled at power up |
| enableLock(bool status) |awl1 / awl0| Enables/Disables lock on power supply buttons - local control |
| enableDisplay(bool status) | awd1 / awd0 | Enables/Disables the 4 digit display |
| setMemory(int loc) | aws (loc) | Set values in memory (0-9) *See Note 1 |
| getMemory(int loc) | awm (loc) | Get values from memory (0-9) |
| readVoltageMilliVolts() | aru | Returns active output Voltage |
| readCurrentMilliAmps() | ari | Returns acive output Current |
| readSetMilliVolts() | arv | Returns set output Voltage |
| readSetMilliAmps() | ara | Returns set output Current |
| readTimer() | art | Returns number of seconds supply has run |
| readCapacity() | arc | Returns total amp hours in thousandth of AH |
| getOutputEnabled() | aro | Get the status of the output |
| getAutoEnabled() | ary | Get the status if output is on or off at power up |
| getLockEnabled() | arl | Get if the front panel is locked |

  *Note 1 - Preset memory location zero sets the default power up values.

Fun fact: When the Power Supply is polled by the MCU, it causes the four digit numeric display appear to flicker.


Searching "DC to DC Step Down Power Supply Module 10V-65V" or "DKP6012" yeild the search results to find them for purchase.

The Drok branded device looks like this:

![drok](https://user-images.githubusercontent.com/24259942/144702575-ca30d9d9-6daa-4150-9fa9-8cb83f3330cb.png)

The generic ones found on places like Aliexpress look like these:

![aliexpress](https://user-images.githubusercontent.com/24259942/144702582-652c7fd2-c5f9-4229-8cc1-ab7b0cea26c1.png)

They all function the same with the small recent exception where the default baud rate used to be 4800 but more recently finding it to be 9600 on recently produced devices as of mid 2021.

Wiring notes:

| Power Supply| MCU |
| ------------- | ------------- |
| T | TX |
| G | Signal and DC ground for power supply. |
| R | RX |
| V | +5VDC - *See Note 2 |

*Note 2 - I've come across some of the power supplies that the +5VDC was high (one was 6.2VDC) and could cause issues if being used as the VCC for the MCU.   It's safe to leave the voltage line disconnected if you don't want to use it as a source for voltage to the MCU.

The MCU to Power Supply transmit TTL levels appear to need to be level shifted from 3.3 to 5 volts for best results for devices like the ESP32 and other 3.3v TTL level devices.

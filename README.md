# BuckPSU
Arduino library for inexpensive remotly controllable and monitored DC-DC converters forked from the great work from
https://github.com/bengineer19/BuckPSU.


|Library function| Prototol command |  Use |
| ------------- | ------------- | ------------- |
| setVoltageMilliVolts(uint16_t millivolts) | awu<milivolts> | Sets output volage |
| setCurrentMilliAmps(uint16_t milliamps) | awi<miliamps> | Sets output current |
| enableOutput(bool status) | awo1 / awo0 | Enables/Disables the Output |
| enableAuto(bool status) | awy1 / awy0 | Enables/Disables if output enabled at power up |
| enableLock(bool status) |awl1 / awl0| Enables/Disables lock on power supply buttons - local control |
| enableDisplay(bool status) | awd1 / awd0 | Enables/Disables the 4 digit display |
| setMemory(int loc) | aws<loc> | Set values in memory (0-9)  |
| getMemory(int loc) | awm<loc> | Get values from memory (0-9) |
| readVoltageMilliVolts() | aru | Returns active output Voltage |
| readCurrentMilliAmps() | ari | Returns acive output Current |
| readSetMilliVolts() | arv | Returns set output Voltage |
| readSetMilliAmps( | ara | Returns set output Current |
| readTimer() | art | Reads number of seconds supply has run |
| readCapacity() | arc | Reads total amp hours supply provided |
| getOutputEnabled() | aro | Get the status of the output |
| getAutoEnabled() | ary | Get the status if output is on or off at power up |
| getLockEnabled() | arl | Get if the front panel is locked |


Fun fact: Whan it is working, the poll and response causes the four digit numeric display appear to flicker.

From experimenting and testing, I've found that searching "DC to DC Step Down Power Supply Module 10V-65V" or "DKP6012" yeild the search results to find them for purchase.

The Drok branded device looks like this:

![drok](https://user-images.githubusercontent.com/24259942/144702575-ca30d9d9-6daa-4150-9fa9-8cb83f3330cb.png)

The generic ones found on places like Aliexpress look like these:

![aliexpress](https://user-images.githubusercontent.com/24259942/144702582-652c7fd2-c5f9-4229-8cc1-ab7b0cea26c1.png)

They all function the same with the small recent exception where the default baud rate used to be 4800 but more recently finding it to be 9600.

Wiring notes:

| Power Supply| MCU |
| ------------- | ------------- |
| T | TX |
| G | Signal and Power ground in power supply. |
| R | RX |
| V | +5VDC |

I've come across some that the 5V was high (one was 6.2VDC) and could cause issues if being used as teh VCC for the MCU.   It's safe to leave the voltage line disconnected if you don't want to use it as a source for voltage.

The MCU to Power Supply transmit TTL levels appear to need to be level shifted from 3.3 to 5 volts for best results for devices like the ESP32 and other 3.3v TTL level devices.

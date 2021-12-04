# BuckPSU
Arduino library for inexpensive remotly controllable and monitored DC-DC converters forked from the great work from https://github.com/bengineer19/BuckPSU

Fun fact: Whan it is working, the poll causes the four digit numeric display appear to flicker.

From experimenting and testing, I've found that searching "DC to DC Step Down Power Supply Module 10V-65V" or "DKP6012" yeald the search results to find them

The Drok branded device looks like this:

![drok](https://user-images.githubusercontent.com/24259942/144702575-ca30d9d9-6daa-4150-9fa9-8cb83f3330cb.png)

The more generic ones found on places like Aliexpress look like these:

![aliexpress](https://user-images.githubusercontent.com/24259942/144702582-652c7fd2-c5f9-4229-8cc1-ab7b0cea26c1.png)

They all function the same with the small recent exeption where the default baud rate used to be 4800 but more recently finding it to be 9600.

Wiring notes:

| Power Supply| MCU |
| ------------- | ------------- |
| T | TX |
| G | Signal and Power ground in power supply. |
| R | RX |
| V | +5VDC* |

** I've come across some that the 5V was high (one was 6.2VDC) and could cause issues if being used as teh VCC for the MCU.   It's safe to leave the voltage line disconnected if you don't want to use it as a source for voltage.

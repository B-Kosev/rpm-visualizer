# Car RPM visualization with LED and display
IoT Project during 6th semester at FMI, Sofia University

Using ESP32 microcontroller, ELM327 OBDII connector

### How it works?
ELM327 is connected to the OBDII port of the car. Then the ESP32 can be powered with USB. The microcontroller is attempting to establish a Bluetooth connection with the ELM327. When a connection is established the car's RPM are queried several times per second and the corresponding information is displayed on the display and the LED strip.

# MasterESP
ESP code that receives Serial input, and sends an instruction to a slave Arduino using the I2C communication protocol.

This code can be used in conjunction with 2 (or more) ESP-modules or Arduino's, and a C# app that writes serial data to the Master node. This action will result in the Master node sending a boolean to the Slave. It will then be processed by the slave and sent to an LED or some other kind of actuator.

## Used pins for physical configuration:
```
D21 (ESP)	->	A4 (Arduino)
D22 (ESP)	->	A5 (Arduino)
Gnd (ESP)	->	Gnd (Arduino)
LED		->	Pin 13 (Arduino)
```

# MasterESP
ESP code that receives Serial input, and sends an instruction to a slave Arduino using the I2C communication protocol.

This code can be used in conjunction with 2 ESP-modules or Arduino's, and a C# app that writes serial data to the Master node. This action will result in the Master node sending a boolean to the Slave. It will then be processed by the slave and sent to an LED or some other kind of actuator.

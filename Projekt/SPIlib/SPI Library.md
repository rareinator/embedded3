# SPI Library

The SPI Library is used to setup the SPI Communication between two devices.



## Wiring

This is how the SPI Connection should be wired.

![Schematic](../html/SPIDiagram.png)



## Data protocol

![Capture](../html/SPISession.png)

In the above example we can see how 4 bytes are send via the SPI Connection.



In this case the first byte is the Register and the second byte is a Value.

The transmitted data is as follow:

Reg = 0x01 Value = 0xFF

Reg = 0x00 Value = 0x01





## Initialization

F_CPU is set to 16000000UL

Baud Rate is set to 9600

Baud Tol is set to 2



MOSI is set to output on Master

MISO is set to input on Master

MISO is set to output on Slave

MOSI is set to input on Slave



CPOL is set to 0

CPHA is set to 0


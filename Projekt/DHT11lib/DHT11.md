# DHT11 module

DHT11 is a temperature and humidity sensor.
Its a specific single wire data communication protocol, to send the data back to the Atmega

[Datasheet](../html/DHT11.pdf)


## Data protocol
![Capture](../html/DHT11Session.png)

Seen above is an example of data captured from the DHT11. <br>
The way it works is by sending a start signal, which it does by pulling <br>
the pin low for at least 18ms. After this it changes it to be an input, <br>
this means it goes high, here it waits for the DHT11 to respons by pulling it low for 80us. <br>
After this it pulls it high for 80us, and then the data transmission starts. <br>
The data transmissions starts by pulling it low for 50us, to signal that a bit is incoming, <br>
Then its pulled high to signal either 0 or 1, 26-28us for a 0 and 70us for a 1. <br>
This way it sends out 5 bytes
* Humidity integral <br>
* Humidity decimal <br>
* Temperature integral <br>
* Temperature decimal <br>
* Checksum <br>
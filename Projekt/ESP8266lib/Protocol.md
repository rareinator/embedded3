# MNI TCP protocol

This is describing the protocol used to communicatge with our ESP8266 over wifi.

## Data communication

To send commands to the wifi module, you start with sending 1 byte specifying the register address
you want to communicate with.

After that you send the data bytes that are defined by the register, this is being terminated by sending 0xFF. Which then ends the transmission.

example

| Address | data byte 0 | data byte 1 | data byte 2 | data byte 3  |  data byte 4 | data byte 5  |  data byte 6 |  data byte 7 |  data byte 8 | data byte 9  | data byte 10  | data byte 11  | data byte 12  |  Terminator    |
|---------|---|---|---|---|---|---|---|---|---|---|---|---|---|------|
| 0x00    | M | y | F | i | , | n | i | c | o | l | a | i | 5 | 0xFF |


### WIFI connection (SSID, password)
* address: 0x00
First you send the SSID follow by a comma 0x2C and then followed by the password, until termination byte 0xFF

### Clock set (and show if time)
* address: 0x01
This only has 7 bytes you can send, in this order
hour, minute, second, day, date, month, year, followed by the termination byte 0xFF so a total of 9 bytes including the address and termination byte

### Temperature limit
* address: 0x02
This only has 1 byte of data you can send,
which is the temperature threshold, before it turns the fan on.
So 3 bytes in total should be send including the address and termination byte

### Fan strength (if time)
* address: 0x03
This only has 1 byte of data you can send,
which is the duty cycle that the fan runs on.
So 3 bytes in total should be send including the address and termination byte
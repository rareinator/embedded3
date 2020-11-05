/*
 * ExeProject.c
 *
 * Created: 02/11/2020 10:57:25
 * Author : Looren
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdbool.h>
#include "DHT11library.h"
#include "I2Clibrary.h"
#include "ESP8266.h"

int main(void)
{
	char _buffer[150];
	uint8_t Connect_Status;
	
	bool hasRead = false;

	USART_Init(115200);						/* Initiate USART with 115200 baud rate */
	sei();									/* Start global interrupt */
	DHT11_init();                           /* Initialize DHT11 */
	while(!ESP8266_Begin());
	ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT); /* 3 = Both (AP and STA) */
	ESP8266_ConnectionMode(MULTIPLE);			   /* 0 = Single; 1 = Multi */
	ESP8266_StartServer(80);                       /* Start server mode with port 80 */
	//if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)
	//ESP8266_JoinAccessPoint(SSID, PASSWORD);
	//ESP8266_Start(0, DOMAIN, PORT);
	LED_ON;
	while(1)
	{
		_delay_ms(15000);
		if (!hasRead)
		{
			LED_TOOGLE;
			_delay_ms(10000);
			hasRead = true;
			
			// wait for data to be incoming
			while (!ESP8266_IncomingTransmission) {}; // Waits for a transmission to be started
			//LED_ON;
			Read_Data(_buffer);
			if (strcmp(_buffer[1], "I") == 0)
			{
				LED_ON;
			}
		}
	}
}
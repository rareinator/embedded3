#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "DHT11library.h"
#include "ESP8266.h"
#include "SPIlibrary.h"


#define MAX_TEMP 25


int main(void)
{
	SPI_Init(true);
	DHT11_init();
	DHT11 tempAndHumid;
	
	#pragma region ESP8266_Init
	
	char _buffer[150];
	uint8_t Connect_Status;
	uint8_t Sample = 24;

	USART_Init(115200);						/* Initiate USART with 115200 baud rate */
	sei();									/* Start global interrupt */

	while(!ESP8266_Begin());
	ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);/* 3 = Both (AP and STA) */
	ESP8266_ConnectionMode(SINGLE);			/* 0 = Single; 1 = Multi */
	ESP8266_ApplicationMode(NORMAL);		/* 0 = Normal Mode; 1 = Transperant Mode */
	if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)
	ESP8266_JoinAccessPoint(SSID, PASSWORD);
	ESP8266_Start(0, DOMAIN, PORT);
	//
	#pragma endregion ESP8266_Init

	SPI_WriteData(1,255); // Set fan speed
	_delay_ms(500);
	LED_ON;
	while(1)
	{
		
		DHT11_ReadRaw(&tempAndHumid); // Read temperature
		if (Sample > MAX_TEMP)
		{
			LED_ON;
			SPI_WriteData(0,1); // Turn on fan
		} else {
			SPI_WriteData(0,0); // Turn off fan
		}
		
		#pragma region ESP8266_SendData
		
		Connect_Status = ESP8266_connected();
		if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)
		ESP8266_JoinAccessPoint(SSID, PASSWORD);
		if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
		ESP8266_Start(0, DOMAIN, PORT);
		
		memset(_buffer, 0, 150);
		sprintf(_buffer, "GET /update?api_key=%s&field1=%d", API_WRITE_KEY, Sample);
		ESP8266_Send(_buffer);
		_delay_ms(15000);
		Sample++;		
		
		#pragma endregion ESP8266_SendData
	}
}
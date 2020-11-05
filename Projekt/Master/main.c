#define F_CPU 16000000UL


#include <avr/io.h>
#include <stdbool.h>
#include "DHT11library.h"
#include "ESP8266.h"
#include "SPIlibrary.h"


int main(void)
{
	SPI_Init(true);
	
	SS_ENABLE;
	SPI_Write(1); // Function Register: Register 0 = Turn On/Off - Register 1 = Fan speed
	SS_DISABLE;
	_delay_ms(500);
	SS_ENABLE;
	SPI_Write(255); // Register Value: If register 0 value = 0 or 1 = Off or On - If 1 value = 0-255 for dutycycle
	SS_DISABLE;
	
	_delay_ms(500);
	
	SS_ENABLE;			
	SPI_Write(0); // Function Register: Register 0 = Turn On/Off - Register 1 = Fan speed
	SS_DISABLE;
	_delay_ms(500);
	SS_ENABLE;
	SPI_Write(1); // Register Value: If register 0 value = 0 or 1 = Off or On - If 1 value = 0-255 for dutycycle
	SS_DISABLE;
	
	while(1)
	{
	}
}



//WIFI

//char _buffer[150];
//uint8_t Connect_Status;
//
//USART_Init(115200);						/* Initiate USART with 115200 baud rate */
//sei();									/* Start global interrupt */
//DHT11_init();                           /* Initialize DHT11 */
//while(!ESP8266_Begin());
//ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT); /* 3 = Both (AP and STA) */
//ESP8266_ConnectionMode(MULTIPLE);			   /* 0 = Single; 1 = Multi */
//ESP8266_StartServer(80);                       /* Start server mode with port 80 */
////if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)
////ESP8266_JoinAccessPoint(SSID, PASSWORD);
////ESP8266_Start(0, DOMAIN, PORT);
//while(1)
//{
	////Connect_Status = ESP8266_connected();
	////if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)
	////ESP8266_JoinAccessPoint(SSID, PASSWORD);
	////if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
	////ESP8266_Start(0, DOMAIN, PORT);
	////
	////DHT11 dhtData;
	////DHT11_ReadRaw(&dhtData);
	////
	////memset(_buffer, 0, 150);
	////sprintf(_buffer, "GET /update?api_key=%s&field1=%i&field2=%i", API_WRITE_KEY, dhtData.Temperatur, dhtData.Humidity);
	////ESP8266_Send(_buffer);
	////_delay_ms(15000);
	//
	//
//}
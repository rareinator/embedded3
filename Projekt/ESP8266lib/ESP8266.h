/**	
	@file
	@defgroup ESP8266 WIFI Library
	@code #include <ESP8266.h> @endcode
  
	@brief ESP8266 WIFI library
	
	The library can be used to both, connect to a wifi network, and then open TCP connections,
	and send data and receive data.

	You can also use it to start your own access point and receive data, acting as a TCP server.

	@author Morten Nissen, Nicolai De Jong Bjerg & Kevin Pike Darmer
	@copyright (C) 2020 Morten Nissen, Nicolai De Jung Berg & Kevin Pike Darmer, GNU General Public License Version 3

*/

/**@{*/

#include <avr/io.h>					/* Include AVR std. library file */
#include <util/delay.h>				/* Include Delay header file */
#include <stdbool.h>				/* Include standard boolean library */
#include <string.h>					/* Include string library */
#include <stdio.h>					/* Include standard IO library */
#include <stdlib.h>					/* Include standard library */
#include <avr/interrupt.h>
#define F_CPU 16000000UL

#ifndef ESP8266_H_
#define ESP8266_H_
#define SREG    _SFR_IO8(0x3F)

#define DEFAULT_BUFFER_SIZE		160
#define DEFAULT_TIMEOUT			10000

/* Connection Mode */
#define SINGLE					0
#define MULTIPLE				1

/* Application Mode */
#define NORMAL					0
#define TRANSPERANT				1

/* Application Mode */
#define STATION							1
#define ACCESSPOINT						2
#define BOTH_STATION_AND_ACCESPOINT		3

#define DOMAIN				"api.thingspeak.com"
#define PORT				"80"
#define API_WRITE_KEY		"9XZN1CY19NFLB7RB"
#define CHANNEL_ID			"1217032"

#define SSID				"OP6T"
#define PASSWORD			"11111111"

/** 
 @brief ESP8266_RESPONSE_STATUS is the status that the ESP8266,
 can respond with, these are being used for every connection with the device
 */
enum ESP8266_RESPONSE_STATUS{
	ESP8266_RESPONSE_WAITING,
	ESP8266_RESPONSE_FINISHED,
	ESP8266_RESPONSE_TIMEOUT,
	ESP8266_RESPONSE_BUFFER_FULL,
	ESP8266_RESPONSE_STARTING,
	ESP8266_RESPONSE_ERROR
};

/** 
 @brief ESP8266_CONNECT_STATUS is the status that the ESP8266,
 can be in describing weather or not is is connect to an Access point
 */
enum ESP8266_CONNECT_STATUS {
	ESP8266_CONNECTED_TO_AP,
	ESP8266_CREATED_TRANSMISSION,
	ESP8266_TRANSMISSION_DISCONNECTED,
	ESP8266_NOT_CONNECTED_TO_AP,
	ESP8266_CONNECT_UNKNOWN_ERROR
};

/** 
 @brief ESP8266_JOINAP_STATUS is the status that the ESP8266,
 responds with when you connect to an Access point.
 */
enum ESP8266_JOINAP_STATUS {
	ESP8266_WIFI_CONNECTED,
	ESP8266_CONNECTION_TIMEOUT,
	ESP8266_WRONG_PASSWORD,
	ESP8266_NOT_FOUND_TARGET_AP,
	ESP8266_CONNECTION_FAILED,
	ESP8266_JOIN_UNKNOWN_ERROR
};



void Read_Response(char* _Expected_Response);
void ESP8266_Clear();
void Start_Read_Response(char* _ExpectedResponse);
void GetResponseBody(char* Response, uint16_t ResponseLength);
/** 
 @brief WaitForExpectedResponse is used after the SendATandExpectResponse,
 its used to wait for a certain string being send by the ESP8266.

 This is a dangerous function to use, as there is no timeout so if the string
 never occures its stuck in a loop.
  
 @param  char* ExpectedResponse is the string that it should wait for

 @return returns true for success and false for failure
 */
bool WaitForExpectedResponse(char* ExpectedResponse);

/** 
 @brief SendATandExpectResponse sends a certain AT command to the ESP8266
 and there after uses the WaitForExpectedResponse to wait until a certain message
 has been send by the ESP8266
  
 @param  char* ATCommand is the string that should be send to the ESP8266
 @param  char* EcpectedResponse is the string that it should wait for

 @return Returns true for succes and false for failure
 */
bool SendATandExpectResponse(char* ATCommand, char* ExpectedResponse);

/** 
 @brief ESP8266_ApplicationMode Sets the transmission mode that should be used
 can be either NORMAL or TRANSPERANT check datasheet page 55.
 Calls the AT+CIPMODE command to the ESP8266
  
 @param  uint8_t Mode is the mode it should be set to NORMAL or TRANSPERANT

 @return Returns true for succes and false for failure
 */
bool ESP8266_ApplicationMode(uint8_t Mode);

/** 
 @brief ESP8266_ConnectionMode Set the connection mode that should be used
 This decides how many connections, there are allowed to be. If hosting your own server
 on the device this need to be set to MULTIPLE, otherwise just use SINGLE,
 as long as you are sure only one request is running at a time.
 Page 53
 Calls the AT+CIPMUX command to the ESP8266

 @param  uint8_t Mode is the mode it should be set to SINGLE or MULTIPLE

 @return Returns true for succes and false for failure
 */
bool ESP8266_ConnectionMode(uint8_t Mode);
bool ESP8266_Begin();
bool ESP8266_Close();

/** 
 @brief ESP8266_WIFIMode sets the wifi mode that should be used
 This decides weather you want to act as its own AP or connect to an already existing one.
 You can also use it as both at the same time.
 STATION if you want to connect to WIFI
 ACCESSPOINT if you want it to act as an Access point
 BOTH_STATION_AND_ACCESPOINT is you want it to act as both
 Page 19
 Calls the AT+CWMODE command to the ESP8266
  
 @param  uint8_t _mode is the mode it should be set to STATION, ACCESSPOINT or BOTH_STATION_AND_ACCESPOINT

 @return Returns true for succes and false for failure
 */
bool ESP8266_WIFIMode(uint8_t _mode);

/** 
 @brief ESP8266_StartServer starts a TCP server on a given Port
 This starts the internal TCP server on a given port
 page 54
 Calls the AT+CIPSERVER command to the ESP8266
  
 @param  uint8_t _port is the port that it should listen on

 @return Returns true for succes and false for failure
 */
bool ESP8266_StartServer(uint8_t _port);

/** 
 @brief ESP8266_StopServer stops the started TCP server
page 54
Calls the AT+CIPSERVER command to the ESP8266

 @return Returns true for succes and false for failure
 */
bool ESP8266_StopServer();

/** 
 @brief ESP8266_JoinAccessPoint joins the given access point
 This is used to connect to a certain wifi
 page 22
 Calls the AT+CWJAP,"_SSID","_PASSWORD"
  
 @param  char* _SSID is the name of the SSID to joins
 @param char* _Password is the password that is used to connect

 @return ESP8266_JOINAP_STATUS with how the connection went
 */
uint8_t ESP8266_JoinAccessPoint(char* _SSID, char* _PASSWORD);
uint8_t ESP8266_connected();

/** 
 @brief ESP8266_Start connects to a certain IP and port over TCP
 Connect to a given TCP server
 page 46
 Calls the AT+CIPSTaRT="TCP","Domain",Port

 @param uint8_t _ConnectionNumber is used in MULTIPLE connectionmode to select what connection to use
 single mode should just use 0

 @param char* Domain is the ip or domain that it should connect to
 @param char* Port is the port that it should connect to
  
 @return ESP8266_CONNECT_STATUS with how the connection went
 */
uint8_t ESP8266_Start(uint8_t _ConnectionNumber, char* Domain, char* Port);

/** 
 @brief ESP8266_Send sends data to a previously established connection
 Sends the given data to the already established conenction.
 Takes the data and calculates the byte length, this is then sent to the
 AT+CIPSEND command.
 After that it sends the given data
 page 47
  
 @param  char* Data is the data that should be sent

 @return ESP8266_RESPONSE_STATUS with what the TCP server responds with
 */
uint8_t ESP8266_Send(char* Data);

int16_t ESP8266_DataAvailable();
uint8_t ESP8266_DataRead();
uint16_t Read_Data(char* _buffer);

#endif /* ESP8266_H_ */
# embedded3
Project Intelligent House

* Temperature & Humidity sensor SKAL bruges
* Brug WIFI
* Kofiguration via mobil/hjemmeide (API)
* Brug RTC device


* Vi ønsker at bruge 2 Arduino boards 1 med DHT11 og RTC og 1 med en fan motor tilsluttet.
	* Begge boards skal konfigureres med en Mobil telefon wia WiFi moduler (ESP8266),
	  Altså klokken kan instilles og selve boardsne tilsluttes et eksiterende WiFi.
	
	* Det 1. board med DHT11 og RTC kalder et API som sørger for at starte fan motoren på den andet board så snart temperaturen overstiger x.
	
	
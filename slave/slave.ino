/*******************************************************************************
# Projet : VOR008
# Sous projet : dialogue IIC module capteur odo
#
# Auteurs: MajorLee
#
# Parie esclave
# licence CC-BY-CA
#
#*******************************************************************************
*/
#include <Arduino.h>
#include <Wire.h>

#define mouseOdometerI2Cadd 5

//SDA A4
//SCL A5

void requestEvent(void);

boolean recReq = false;
boolean emet = false;
byte registres[] = { 0x1C,
    0x34, 0x20, 0X21, 0x5B,
    0x00, 0x01, 0x10, 0x12,
    0x20, 0x21, 0x22, 0x23,
    0x35, 0x36, 0x37, 0x38,
    0xF9};
byte regAdd = 0;

void setup()
{
	Serial.begin(115200);
    Serial.println("IIC Slave");
	Wire.begin(0x05);
	//Wire.onReceive(IIChandlerRec);
	Wire.onRequest(requestEvent);
	pinMode(13, OUTPUT);
}

void loop()
{
	delay(200);              // wait for a second
	digitalWrite(13, HIGH);   // set the LED on
	delay(200);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off

}

void requestEvent(void){
        Wire.write(registres, sizeof(registres));
}

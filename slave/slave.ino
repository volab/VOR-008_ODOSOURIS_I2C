/*
#*******************************************************************************
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

void IIChandlerRec(int);
void requestEvent(void);


boolean recReq = false;
boolean emet = false;
byte registres[] = { 0x1C, 0x34, 0x20, 0X21, 0x5B};
byte regAdd = 0;




void setup()
{
	Serial.begin(115200);
    Serial.println("IIC Slave");
	Wire.begin(0x05);
	Wire.onReceive(IIChandlerRec);
	Wire.onRequest(requestEvent);
	pinMode(13, OUTPUT);
}

void loop()
{
	delay(200);              // wait for a second
	digitalWrite(13, HIGH);   // set the LED on
	delay(200);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off
//	if (Wire.available()){
//        Serial.print("Recu");
//        Wire.read();
//	}
	if (recReq) {
        Serial.print("Adresse recue = ");Serial.println(regAdd, HEX);
        recReq = false;
	}
//	if (emet){
//        Serial.println("emet");
//        emet = false;
//	}
}


void IIChandlerRec(int combien){
    Serial.print(combien);Serial.println(" octet recue");
    recReq = true;
    if (Wire.available()) regAdd = Wire.read();

}

void requestEvent(void){
//    Serial.println("emission");
        Wire.write(registres, 3);
//    Wire.write("h");
//    Serial.print("regAdd = ");Serial.print(regAdd);
//    emet = true;
}

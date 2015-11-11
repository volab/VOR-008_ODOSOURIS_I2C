/*******************************************************************************
# Projet : VOR008
# Sous projet : dialogue IIC module capteur odo
#
# Auteurs: MajorLee
#
# Partie maitre
# licence CC-BY-CA
#
#*******************************************************************************
*/
#include <Arduino.h>
#include <Wire.h>

#define mouseOdometerI2Cadd 5 // totalement arbitraire
#define LED 13

boolean newTrame=false;
byte bufferIn[18];

byte i2c_read_trame( byte deviceaddress, byte *buffer, byte longueur){
    Wire.requestFrom(deviceaddress, longueur);
    for (int i=0; i<longueur; i++){
        if (Wire.available()) buffer[i] = Wire.read();
    }
    return longueur; // totalement inutile
}

void setup(){
	Serial.begin(115200);
    Wire.begin();
    serialEventRun();
	pinMode(LED, OUTPUT);
	digitalWrite(LED, true);
	Serial.println("************Master****************");
}

byte octet;
byte longLu = 18;

void loop(){
    if (newTrame){
        Serial.println("Trame transmise");
        newTrame=false;
        octet = i2c_read_trame(mouseOdometerI2Cadd, bufferIn,longLu);
        for ( int i=0; i< longLu; i++){
            Serial.print( bufferIn[i], HEX);
            Serial.print(" - ");
        }
        Serial.println("fin de trame");
    }
}

void serialEvent(){
    Serial.println("dans serialEvent");
    digitalWrite(LED, !digitalRead(LED));
    newTrame = true;
    Serial.read();
}



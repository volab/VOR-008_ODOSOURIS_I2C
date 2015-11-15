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
#define DXDADD 1

boolean newTrame=false;
byte bufferIn[18];
signed long dxd;

byte i2c_read_trame( byte deviceaddress, byte *buffer, byte longueur){
    Wire.requestFrom(deviceaddress, longueur);
    for (int i=0; i<longueur; i++){
        if (Wire.available()) buffer[i] = Wire.read();
    }
    return longueur; // totalement inutile
}

signed long toSL(byte *buffer, uint8_t pos){
    signed long data;
    data = (signed long)buffer[pos]<<24;
    data |= (signed long)buffer[pos+1] << 16 ;
    data |= (signed long)buffer[pos+2] << 8 ;
    data |= (signed long)buffer[pos+3] ;
    Serial.print(buffer[pos],HEX);
    Serial.print(buffer[pos+1],HEX);
    Serial.print(buffer[pos+2], HEX);
    Serial.println(buffer[pos+3],HEX);
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
//        Serial.println("Trame transmise");
        newTrame=false;
        octet = i2c_read_trame(mouseOdometerI2Cadd, bufferIn,longLu);
//        for ( int i=0; i< longLu; i++){
//            Serial.print( bufferIn[i], HEX);
//            Serial.print(" - ");
//        }
//        Serial.println("fin de trame");
        //dxd = toSL(bufferIn, DXDADD);
        dxd = (signed long)bufferIn[DXDADD]<<24;
        dxd |= (signed long)bufferIn[DXDADD+1] << 16 ;
        dxd |= (signed long)bufferIn[DXDADD+2] << 8 ;
        dxd |= (signed long)bufferIn[DXDADD+3] ;
        float dx_float = (float)dxd*25.4/421.0;
        Serial.print("Delta X = ");Serial.println(abs(dx_float));//Serial.print("mm");
    }



}

void serialEvent(){
    //Serial.println("dans serialEvent");
    digitalWrite(LED, !digitalRead(LED));
    newTrame = true;
    Serial.read();
}



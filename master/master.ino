#include <Arduino.h>
#include <Wire.h>

#define mouseOdometerI2Cadd 5 // totalement arbitraire
#define LED 13

boolean newTrame=true;
byte bufferIn[10];

byte i2c_read_byte( int deviceaddress, byte eeaddress ) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write( eeaddress ); // MSB
    Serial.println(Wire.endTransmission());
    delayMicroseconds(500);
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available()) rdata = Wire.read();
    return rdata;
  }

//byte i2c_read_trame( byte deviceaddress, byte adresseInterne, byte *buffer, byte longueur){
//    Wire.beginTransmission(deviceaddress);
//    Wire.write( adresseInterne ); // MSB
//    //Serial.println(Wire.endTransmission());
//    Wire.endTransmission();
//
//    delayMicroseconds(500);
//    Wire.requestFrom(deviceaddress, longueur);
//    for (int i=0; i<longueur; i++){
//        if (Wire.available()) buffer[i] = Wire.read();
//    }
//
//    return longueur;
//}

void setup()
{
	Serial.begin(115200);
    Wire.begin();
    serialEventRun();
	pinMode(LED, OUTPUT);
	digitalWrite(LED, true);
	Serial.println("************Master****************");
}

byte octet;
byte longLu = 3;



void loop()
{

	//Serial.println("Attente return pour nouvelle trame");
	//attendSuite = true;
    //while( attendSuite ) delay(1);
    //Serial.read();
    if (newTrame){
        Serial.println("Trame transmise");
        newTrame=false;
        //octet = i2c_read_byte(mouseOdometerI2Cadd, 1);
        octet = i2c_read_trame(mouseOdometerI2Cadd, 0x0, bufferIn,longLu);
        //Serial.print("Octet recu = ");Serial.println(octet, HEX);
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

/*
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Wire.begin();
    pinMode(LED, OUTPUT);
	digitalWrite(LED, true);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent(){
    Serial.read();
    Serial.println("3dents");
    digitalWrite(LED, !digitalRead(LED));
    attendSuite = false;
}

/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */
/*
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  S
  inputString.reserve(200);
}

void loop() {
  serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
 /*
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
*/

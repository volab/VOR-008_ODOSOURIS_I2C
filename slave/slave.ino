/*******************************************************************************
# Projet : VOR008
# Sous projet : dialogue IIC module capteur odo
#
# Auteurs: MajorLee
#
# Partie esclave
# licence CC-BY-CA
#
#*******************************************************************************
# v0.1 premiere version stable avec juste une trame fixe
*/
// Pour memoire
//SDA A4
//SCL A5

#include <Arduino.h>
#include <Wire.h>
#include "ADNS2610.h"
#include "OdoRegisters.h"


/*******************************************************************************
 Macro
*******************************************************************************/
#define mouseOdometerI2Cadd 5
#define SCLKd 3                       // Serial clock pin on the Arduino
#define SDIOd 2                       // Serial data (I/O) pin on the Arduino
//Ajouter capteur gauche

//PB0 PIN8
#define INSTRUMPIN 8

/*******************************************************************************
 Gestionnaire d'�v�nements
*******************************************************************************/
void requestEvent(void);            // Traitement des requ�te IIC entrantes


/*******************************************************************************
 Vaiables globales
*******************************************************************************/
uint8_t *registres;
byte regAdd = 0;

signed long dxd, dyd, dxg, dyg;
boolean trameLue = false;
ADNS2610 capteurDroit = ADNS2610(SCLKd, SDIOd);
odoRegisters mesRegistres;

int c = 0;
uint8_t portReg, pinBitMask;
volatile uint8_t *portAdd;

void setup()
{
	Serial.begin(115200);
    Serial.println("IIC Slave");
	Wire.begin(mouseOdometerI2Cadd);
	Wire.onRequest(requestEvent);
	pinMode(13, OUTPUT);
	pinMode( INSTRUMPIN, OUTPUT);
	registres = mesRegistres.getRegBankStartAdd();
	portReg = digitalPinToPort(INSTRUMPIN);
	portAdd = portOutputRegister(portReg);
	Serial.print("Port de la pine 8 = ");Serial.println(portReg);
	pinBitMask = digitalPinToBitMask(INSTRUMPIN);
	Serial.print("bit de la pin 8 = ");Serial.println(pinBitMask);
}

void loop()
{
    *portAdd ^= pinBitMask;
    //PORTB ^= (1<<0);
    dxd += capteurDroit.dx();
    dyd += capteurDroit.dy();
    if (trameLue){
        mesRegistres.setDataLong(DXDADD, dxd);
        mesRegistres.setDataLong(DYDADD, dyd);
        trameLue = false;
    }

}

void requestEvent(void){
        int taille = mesRegistres.getSize();
        Wire.write(registres, taille);
        trameLue =  true;
}

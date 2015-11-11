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
* v0.2 version satble avec capteur optique réel
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
 Gestionnaire d'événements
*******************************************************************************/
void requestEvent(void);            // Traitement des requête IIC entrantes


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
	Wire.begin(mouseOdometerI2Cadd);
	Wire.onRequest(requestEvent);

	pinMode( INSTRUMPIN, OUTPUT);
	registres = mesRegistres.getRegBankStartAdd();
	portReg = digitalPinToPort(INSTRUMPIN);
	portAdd = portOutputRegister(portReg);
	pinBitMask = digitalPinToBitMask(INSTRUMPIN);

}

void loop()
{
    for(;;){
        *portAdd ^= pinBitMask; //Instrumentation temps de cycle
        dxd += capteurDroit.dx();
        dyd += capteurDroit.dy();
        if (trameLue){
            mesRegistres.setDataLong(DXDADD, dxd);
            mesRegistres.setDataLong(DYDADD, dyd);
            trameLue = false;
        }
    }
}

void requestEvent(void){
        int taille = mesRegistres.getSize();
        Wire.write(registres, taille);
        trameLue =  true;
}

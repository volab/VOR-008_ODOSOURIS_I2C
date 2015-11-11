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

void setup()
{
	Serial.begin(115200);
    Serial.println("IIC Slave");
	Wire.begin(0x05);
	//Wire.onReceive(IIChandlerRec);
	Wire.onRequest(requestEvent);
	pinMode(13, OUTPUT);
	//mesRegistres.serialPrintTrame();
	registres = mesRegistres.getRegBankStartAdd();
	Serial.println((unsigned int)(registres), HEX);
	mesRegistres.serialPrintAdd();
}

void loop()
{
    dxd += capteurDroit.dx();
    dyd += capteurDroit.dy();
    //Mise au point
    if (c++ & 0x80){
        mesRegistres.setDataLong(DXDADD, dxd);
        mesRegistres.setDataLong(DYDADD, dyd);
        //mesRegistres.serialPrintTrame();
            Serial.print("Tramesize : ");
            Serial.println( mesRegistres.getSize());
            //int taille = mesRegistres.getSize();
            Serial.print ("Trame : ");
            //for( int i; i<( taille ); i++ ){
            //for( int i; i<( ODOREGISTERSSIZE); i++ ){
            for( int i; i<( mesRegistres.getSize()); i++ ){
                Serial.print (registres[i], HEX);
                //Serial.print(i);
                Serial.print(" ");
            }
            Serial.println(" End");
        c=0;
    }

    if (trameLue){
        mesRegistres.setDataLong(DXDADD, dxd);
        mesRegistres.setDataLong(DYDADD, dyd);
        trameLue = false;
    }

}

void requestEvent(void){
        Wire.write(registres, sizeof(registres));
        trameLue =  true;
}

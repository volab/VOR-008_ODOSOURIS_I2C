#include "OdoRegisters.h"
#include <Arduino.h>

odoRegisters::odoRegisters(){
    _size = ODOREGISTERSSIZE;
    for( int i; i<ODOREGISTERSSIZE; i++ ){
        _registerBank[i] = 0;
    }
    _registerBank[0] = VERSION << 4;
    _registerBank[ODOREGISTERSSIZE-1] = 0xff;

}

int odoRegisters::getSize(){
    return _size;
}

void odoRegisters::setDataLong(int add, signed long data){
    _registerBank[add] = data >> 24;
    _registerBank[add++] = data >> 16;
    _registerBank[add++] = data >> 8;
    _registerBank[add++] = data & 0xff;
}

//Pour mise au point
void odoRegisters::serialPrintTrame(){
    Serial.print ("Trame : ");
    for( int i; i<ODOREGISTERSSIZE; i++ ){
        Serial.print (_registerBank[i], HEX);
        Serial.print(" ");
    }
    Serial.println(" End");
}

void odoRegisters::serialPrintAdd(){
    Serial.println((unsigned int)(_registerBank), HEX);
}

uint8_t * odoRegisters::getRegBankStartAdd(){
    return _registerBank;
}

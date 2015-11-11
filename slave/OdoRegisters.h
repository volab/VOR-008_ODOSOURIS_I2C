#ifndef ODOREGISTERS_H_INCLUDED
#define ODOREGISTERS_H_INCLUDED


#include <math.h>
//#include <Arduino.h>
#include <stdint.h>

#define ODOREGISTERSSIZE 18
#define VERSION 1 // Trame I2C version
#define VERSIONSTATUSADD 0
#define DXDADD 1
#define DYDADD 5
#define DXGADD 9
#define DYGADD 13
#define CSADD ODOREGISTERSSIZE-1

class odoRegisters{

    public:
        odoRegisters();
        int getSize();
        void setDataLong(int add, signed long data);
        uint8_t getReg(int add);
        void serialPrintTrame();
        uint8_t *getRegBankStartAdd();
        void serialPrintAdd();
    private:

        int _size;
        uint8_t _registerBank[ODOREGISTERSSIZE];

};

#endif // ODOREGITERS_H_INCLUDED

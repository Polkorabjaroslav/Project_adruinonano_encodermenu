#include <Arduino.h>
#include <Wire.h>
#include "TDA7440.h"

TDA7440::TDA7440()
{
    Wire.begin();   //comunication start 
}

void TDA7440::setInput(uint8_t input)   //input selection
{
    switch(input)
    {
        case 1: 
            input = TDA7440_Input_1;
            break;

        case 2: 
            input = TDA7440_Input_2;
            break;

        case 3: 
            input = TDA7440_Input_3;
            break;

        case 4: 
            input = TDA7440_Input_4;
            break;
    }
    writeWire(TDA7440_Input_sel,input);
}

void TDA7440::inputGain(uint8_t gain)   //gain
{
    writeWire(TDA7440_Input_Gain, gain);
}

void TDA7440::setVolume(uint8_t volume) //volume
{
    switch (volume)
    {
    case 0:
        volume = TDA7440_Mute;
        break;
    case 13: 
        volume = 0x00;
        break;
    case 12:
        volume = 0x01;
        break;
    case 11:
        volume = 0x02;
        break;
    case 10:
        volume = 0x03;
        break;
    case 9:
        volume = 0x04;
        break;
    case 8:
        volume = 0x05;
        break;
    case 7:
        volume = 0x06;
        break;
    case 6:
        volume = 0x07;
        break;
    case 5:
        volume = 0x08;
        break;
    case 4:
        volume = 0x10;
        break;
    case 3:
        volume = 0x18;
        break;
    case 2:
        volume = 0x20;
        break;
    case 1:
        volume = 0x28;
        break;
    }
    
    
    writeWire(TDA7440_Volume, volume);
}

void TDA7440::setSnd(int8_t val, uint8_t sel) //1Bass and 2Treble settings
{
    switch (sel)
    {
    case 1:
        sel = TDA7440_Bass;
        break;
    
    case 2:
        sel = TDA7440_Treble;
        break;
    }
    switch (val)
    {
    case -7:
        val = 0x00;
        break;
    case -6:
        val = 0x01;
        break;
    case -5:
        val = 0x02;
        break;
    case -4:
        val = 0x03;
        break;
    case -3:
        val = 0x04;
        break;
    case -2:
        val = 0x05;
        break;
    case -1:
        val = 0x06;
        break;
    case 0:
        val = 0x07;
        break;
    case 1:
        val = 0b1110;
    case 2:
        val = 0b1101;
    case 3:
        val = 0b1100;
    case 4:
        val = 0x1011;
    case 5:
        val = 0x1010;
    case 6:
        val = 0x1001;
    case 7:
        val = 0x1000;
    }
    writeWire(sel,val);
}

void TDA7440::mute()
{
    writeWire(TDA7440_Volume,TDA7440_Mute);
}

void TDA7440::spkAtt(uint8_t atten)
{
    switch (atten)
    {
    case 0:
        atten = 0;
    case 16:
        atten = 0x01;
        break;
    case 15:
        atten = 0x02;
        break;
    case 14:
        atten= 0x03;
        break;
    case 13:
        atten = 0x04;
        break;
    case 12:
        atten = 0x05;
        break;
    case 11:
        atten = 0x06;
        break;
    case 10:
        atten = 0x07;
        break;
    case 9:
        atten = 0x08;
        break;
    case 8:
        atten = 0x10;
        break;
    case 7:
        atten = 0x18;
        break;
    case 6:
        atten = 0x20;
        break;
    case 5:
        atten = 0x28;
        break;
    case 4:
        atten = 0x30;
        break;
    case 3:
        atten = 0x38;
        break;
    case 2:
        atten = 0x40;
        break;
    case 1:
        atten = 0x48;
        break;
    }
    writeWire(TDA7440_Attenuate_l,atten);
    writeWire(TDA7440_Attenuate_r,atten);
}

void TDA7440::writeWire(char a, char b)
{
  Wire.beginTransmission(TDA7440_Address);
  Wire.write (a);
  Wire.write (b);
  Wire.endTransmission();
}
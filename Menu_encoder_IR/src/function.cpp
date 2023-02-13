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
    if (volume == 0)
    {
        volume = TDA7440_Mute;
    }
    else
    {
        volume = 48 - volume;
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
        val = 0;
        break;
    case -6:
        val = 1;
        break;
    case -5:
        val = 2;
        break;
    case -4:
        val = 3;
        break;
    case -3:
        val = 4;
        break;
    case -2:
        val = 5;
        break;
    case -1:
        val = 6;
        break;
    case 0:
        val = 7;
        break;
    
    default:
        break;
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
        break;
    case 1:
        atten = 1;
        break;
    case 2:
        atten = 2;
        break;
    case 3:
        atten = 3;
        break;
    case 4:
        atten = 4;
        break;
    case 5:
        atten = 5;
        break;
    case 6:
        atten = 6;
        break;
    case 7:
        atten = 7;
        break;
    case 8:
        atten = 8;
        break;
    case 9:
        atten = 16;
        break;
    case 10:
        atten = 24;
        break;
    case 11:
        atten = 32;
        break;
    case 12:
        atten = 40;
        break;
    case 13:
        atten = 48;
        break;
    case 14:
        atten = 56;
        break;
    case 15:
        atten = 64;
        break;
    case 16:
        atten = 72;
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
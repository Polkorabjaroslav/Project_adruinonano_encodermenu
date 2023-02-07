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

void TDA7440::setSnd(int8_t val, uint8_t sel)
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
}



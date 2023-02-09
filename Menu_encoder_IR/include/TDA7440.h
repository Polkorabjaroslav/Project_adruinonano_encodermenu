#ifndef TDA7440_H
#define TDA7440_H

//address of slave
#define TDA7440_Address 0x44

//subaddress of slave
#define TDA7440_Input_sel 0x00
#define TDA7440_Input_Gain 0x01
#define TDA7440_Volume 0x02
#define TDA7440_Bass 0x03
#define TDA7440_Treble 0x05
#define TDA7440_Attenuate_r 0x06
#define TDA7440_Attenuate_l 0x07

//input selection address
#define TDA7440_Input_1 0x03
#define TDA7440_Input_2 0x02
#define TDA7440_Input_3 0x01
#define TDA7440_Input_4 0x00

#define TDA7440_Mute 0x38

#include <Arduino.h>
class TDA7440
{
  public:
    TDA7440();
	void setInput(uint8_t input); // 1 to 4
	void inputGain(uint8_t gain); // 0 to 30
	void setVolume(uint8_t volume); // 0 to 48 ( 0 is mute)
	void setSnd(int8_t val, uint8_t sel); //-7 to +7 , 1 - Bass  | 2 - Trebble
	void mute();
	void spkAtt(uint8_t atten); // Output attenuation 0 to 79 (db) 
  private:
	void writeWire(char a, char b);
};



#endif
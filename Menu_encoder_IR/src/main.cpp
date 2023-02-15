#include <Arduino.h>
#include <Wire.h>
#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>
#include "TDA7440.h"

#define CLK PD3
#define DT  PD2
#define SW  PC2
#define Button PD4

LiquidCrystal_I2C lcd(0x27, 16, 2);

IRrecv receiver(7);

int8_t numOptions = 4;
const char* menu[] = {"Treble", "Volume", "Bass", "Gain","Equalizer"};
const char* submenu[] = {"Middle","Bass","Flat"};
int8_t currentOption = 0;

int16_t lastStateCLK;
int16_t currentStateCLK;

uint16_t actualMillis;
uint8_t irMillis;
uint8_t resumMillis;  

uint8_t buttonoption;
uint8_t buttonDebounce = 0;
uint8_t delayDebounce = 100;
uint8_t buttonPress;

int8_t gainStart = 0;
int8_t volumeStart = 0;
int8_t trebleStart = 0;
int8_t bassStart = 0;

TDA7440 amp = TDA7440();

void codeIR();
void menuOption();
void handleEncoder();
void checkValues();
void changeMenuTab(uint8_t value);
void printArrows();
void clearLine(uint8_t line);
void buttonRead();
void trebleEnc();
void trebleVal(int8_t trebleVal);
void bassEnc();
void bassVal(int8_t trebleVal);
void subMenu();

void setup()
{
  lcd.init();
  lcd.backlight();
  IrReceiver.enableIRIn();
  amp.inputGain(gainStart);
  amp.setVolume(volumeStart);
  amp.spkAtt(0);
  amp.setSnd(1,bassStart); //1 Bassy
  amp.setSnd(2,trebleStart);// 2 treble

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT);
  lastStateCLK = digitalRead(CLK);
  menuOption();
}

void loop() 
{
  actualMillis = millis();

  if(actualMillis - irMillis > 100)
  {
    irMillis = actualMillis;
    if(IrReceiver.decode())
    {
      codeIR();
      if(actualMillis - resumMillis > 100)
      {
        resumMillis = actualMillis;
        IrReceiver.resume();
      }
    }
  }
  buttonRead();
  handleEncoder();
  checkValues();
}

void buttonRead()
{
  if(digitalRead(Button) == 1 && buttonPress == 0)
  {
    if((millis() - buttonDebounce) > delayDebounce)
    {
     buttonPress = 1;
     subMenu();
     buttonDebounce = millis();
    }
  }
}

void subMenu()
{
  while (true)
  {
    switch (currentOption)
    {
    case 0:
      trebleEnc();
      break;
    case 1:
      lcd.setCursor(0,1);
      lcd.print(1);
      break;
    case 2:
      bassEnc();
      break;
    case 3:
      lcd.setCursor(0,1);
      lcd.print(3);
      break;
    case 4:
      lcd.setCursor(0,1);
      lcd.print(4);
      break;
    }

    if(millis() % 10 == 0 && digitalRead(Button) == 1 && buttonPress == 1 && (millis() - buttonDebounce) > delayDebounce) //double press borec
    {
      buttonPress = 0;
      buttonDebounce = millis();
      lcd.setCursor(0,1);
      lcd.print("         ");
      break;  
    }
  }
}

void changeMenuTab(uint8_t value)
{
  currentOption += value;
  checkValues();
  menuOption();
}

void checkValues()
{
  if (currentOption < 0)
  {
    currentOption = numOptions;
    return;
  }

  if (currentOption > numOptions)
  {
    currentOption = 0;
  }
}

void handleEncoder()
{
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) 
  {
    if(digitalRead(DT) != currentStateCLK)
    {
      changeMenuTab(-1);
    }
    else 
    {
      changeMenuTab(1);
    }
  }

  lastStateCLK = currentStateCLK;
}

void printArrows()
{
  lcd.setCursor(1,0);
  lcd.print("<");
  lcd.setCursor(14,0);
  lcd.print(">");
}

void clearLine(uint8_t line)
{
  lcd.setCursor(4, line);
  lcd.print("          ");
}

void menuOption()
{
  printArrows();
  clearLine(0);
  lcd.setCursor(8 - strlen(menu[currentOption]) / 2, 0);
  lcd.print(menu[currentOption]);  
}

void codeIR()
{
  switch (IrReceiver.decodedIRData.command)
  {
    case 90:  // >
      changeMenuTab(1);
      break;

    case 82:  // V
      lcd.setCursor(5,1);
      lcd.print("down");
      break;

    case 8:   // <
      changeMenuTab(-1);
      break;

    case 24:  
      lcd.setCursor(5,1);
      lcd.print("up");
      break;

    default:
     break;
  }
}

void trebleEnc()
{
  if(trebleStart < 0)
  {
    lcd.setCursor(6, 1);
    lcd.print(trebleStart);
  }
  if(trebleStart >= 0)
  {
    lcd.setCursor(6,1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    lcd.print(trebleStart);
  }
  
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) 
  {
    if(digitalRead(DT) != currentStateCLK)
    {
      trebleVal(-1);
    }
    else 
    {
      trebleVal(1);
    }
  }
  lastStateCLK = currentStateCLK;
}

void trebleVal(int8_t trebleVal)  
{
  trebleStart += trebleVal;

  if(trebleStart < -7)
  {
    trebleStart = -7;
  }
  if(trebleStart > 7)
  {
    trebleStart = 7;
  }
  amp.setSnd(2,trebleStart);
}

void bassEnc()
{
  if(bassStart < 0)
  {
    lcd.setCursor(6, 1);
    lcd.print(bassStart);
  }
  if(bassStart >= 0)
  {
    lcd.setCursor(6,1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    lcd.print(bassStart);
  }
  
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) 
  {
    if(digitalRead(DT) != currentStateCLK)
    {
      bassVal(-1);
    }
    else 
    {
      bassVal(1);
    }
  }
  lastStateCLK = currentStateCLK;
}

void bassVal(int8_t bassVal)  
{
  bassStart += bassVal;

  if(bassStart < -7)
  {
    bassStart = -7;
  }
  if(bassStart > 7)
  {
    bassStart = 7;
  }
  amp.setSnd(1,bassStart);
}
#include <Arduino.h>
#include <Wire.h>
#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>

#define CLK PD3
#define DT  PD2
#define SW  PC2
LiquidCrystal_I2C lcd(0x27, 16, 2);
// create an encoder object
IRrecv receiver(7);
// define some constants for the menu options
int8_t numOptions = 4;
const char* menu[] = {"Treble", "Volume", "Bass", "Gain","Equalizer"};
const char* submenu[] = {"Middle","Bass","Flat"};
int8_t currentOption = 0;

int16_t lastStateCLK;
int16_t currentStateCLK;

uint8_t newPos;
uint16_t actualMillis;
uint16_t menuMillis;
uint8_t irMillis;
uint8_t resumMillis;  

void codeIR();
void menuOption();
void handleEncoder();
void checkValues();
void changeMenuTab(uint8_t value);

void setup() 
{
  lcd.init();
  lcd.backlight();
  IrReceiver.enableIRIn();

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  lastStateCLK = digitalRead(CLK);
  menuOption();
}

void loop() 
{
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print(currentOption);
  lcd.setCursor(0, 1);

  actualMillis = millis();

  if(actualMillis - irMillis > 200)
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

  handleEncoder();
  checkValues();
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

void menuOption()
{
  lcd.setCursor(1,0);
  lcd.print("<");
  lcd.setCursor(14,0);
  lcd.print(">");

  lcd.setCursor(4,0);
  lcd.print("          ");

  int wordOffset = (sizeof(menu[currentOption]) / sizeof(char)) / 2;

  lcd.setCursor(8 - wordOffset, 0);

  // switch (currentOption)
  // {
  //   case 0:
  //     lcd.setCursor(5,0);
  //     break;
    
  //   case 1:
  //     lcd.setCursor(5,0);
  //     break;

  //   case 4:
  //     lcd.setCursor(4,0);
  //     break;

  //   default:
  //     lcd.setCursor(6,0);
  //     break;
  // }

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
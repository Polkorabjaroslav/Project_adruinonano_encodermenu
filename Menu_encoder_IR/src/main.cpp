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

void codeIR();
void menuOption();
void setup() 
{
  lcd.init();
  lcd.backlight();
  IrReceiver.enableIRIn();

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  lastStateCLK = digitalRead(CLK);
}

void loop() 
{
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print(currentOption);
  lcd.setCursor(0, 1);

  currentStateCLK = digitalRead(CLK);
  actualMillis = millis();
  
  if(actualMillis - menuMillis > 100)
  {
    menuMillis = actualMillis;
    menuOption();
  }
  if(actualMillis - irMillis > 200)
  {
    irMillis = actualMillis;
    if(IrReceiver.decode())
    {
    codeIR();
    IrReceiver.resume();
    }
  }

  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) 
  {
    if(digitalRead(DT) != currentStateCLK)
    {
      currentOption -= 1;
    }
    else 
    {
      currentOption += 1;
    }
  }
  lastStateCLK = currentStateCLK;

  if(currentOption < 0)
  {
    currentOption = numOptions;
  }
  else if (currentOption > numOptions)
  {
    currentOption = 0;
  }
}
void menuOption()
{
  lcd.setCursor(1,0);
  lcd.print("<");
  lcd.setCursor(14,0);
  lcd.print(">");

  if (currentOption == 0 || currentOption == 1)
  {
    lcd.setCursor(4,0);
    lcd.print("          ");
    lcd.setCursor(5,0);
    lcd.print(menu[currentOption]);
  }
  else if(currentOption == 4)
  {
    lcd.setCursor(4,0);
    lcd.print("       ");
    lcd.setCursor(4,0);
    lcd.print(menu[currentOption]);
  }
  else
  {
    lcd.setCursor(4,0);
    lcd.print("         ");
    lcd.setCursor(6,0);
    lcd.print(menu[currentOption]);
  }
  





}
void codeIR()
{
  switch (IrReceiver.decodedIRData.command)
  {
    case 90:  // >
      if(currentOption > 4)
      {
        currentOption = 0;
      }
      else
      {
        currentOption +=1;
      }
      break;
    case 82:  // V
      lcd.setCursor(5,1);
      lcd.print("down");
      break;
    case 8:   // <
      if(currentOption < 0)
      {
        currentOption = 4;
      }
      else
      {
        currentOption -= 1;
      }
      break;
    case 24:  
      lcd.setCursor(5,1);
      lcd.print("up");
      break;
    default:
     break;
  }
}
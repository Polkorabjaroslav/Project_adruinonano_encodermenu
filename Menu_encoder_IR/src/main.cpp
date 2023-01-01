#include <Arduino.h>
#include <Wire.h>
#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>
#include<Encoder.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// create an encoder object
Encoder encoder(2, 3);
IRrecv receiver(7);
// define some constants for the menu options
int8_t numOptions = 4;
const char* options[] = {"Treble", "Volume", "Bass", "Gain"};
int8_t currentOption = 0;
int16_t lastStateCLK = -200;
uint8_t newPos;
uint16_t lastMillis;
uint16_t actualMillis;

void codeIR();

void setup() 
{
  lcd.init();
  lcd.backlight();
  IrReceiver.enableIRIn();
}

void loop() 
{
  actualMillis = millis();
  lcd.setCursor(0, 1);

   if(IrReceiver.decode())
  {
    codeIR();
    IrReceiver.resume();
  }

  if(actualMillis - lastMillis > 300)
  {
    lastMillis = actualMillis;
    newPos = encoder.read();
  }
  
  if (newPos != lastStateCLK) 
  {
    currentOption += 1;
    if(currentOption < 0)
    {
      currentOption = numOptions - 1;
    }
    else if (currentOption >= numOptions)
    {
      currentOption = 0;
    }
    
    lastStateCLK = newPos;
    lcd.setCursor(4,0);
    lcd.print("<");
    lcd.setCursor(11,0);
    lcd.print(">");
    if (currentOption == 0 || currentOption == 1)
    {
      lcd.setCursor(5,0);
      lcd.print("      ");
      lcd.setCursor(5,0);
      lcd.print(options[currentOption]);
    }
    else
    {
      lcd.setCursor(5,0);
      lcd.print("      ");
      lcd.setCursor(6,0);
      lcd.print(options[currentOption]);
    }
  }

  
}

void codeIR()
{
  switch (receiver.decodedIRData.command)
  {
    case 90:  // >
      lcd.setCursor(5,1);
      lcd.print("right");
      break;
    case 82:  // V
      lcd.setCursor(5,1);
      lcd.print("down");
      break;
    case 8:   // <
      lcd.setCursor(5,1);
      lcd.print("left");
      break;
    case 24:  
      lcd.setCursor(5,1);
      lcd.print("up");
      break;
    default:
     break;
  }
}
/*
  TEA5767LCD.ino - Example file for library for using I2C TEA5767 FM recipier with Arduino.
  Created by Pierre-Yves Merle, Januar 11, 2013.
  Released into the public domain.
  
  Connect SDA to A4 on Arduino UNO or 20 on Arduino MEGA
  Connect SCL to A5 on Arduino UNO or 21 on Arduino MEGA
  Schema available on this directory: schema/Schema.jpg (You must add TEA5767)
  
  Use 75cm antenna
  
  You MUST include Wire.h
*/

#define BT_NEXT_STA 7
#define BT_PREW_STA 6
#define BT_NEXT_FREQ 8
#define BT_PREW_FREQ 9

#define delays(x); delay(x*1000); //delay function but with seconds

#include <Wire.h>
#include <TEA5767.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
TEA5767 FM;

void setup()
{
	FM.begin();
	lcd.begin(16, 2);
	pinMode(BT_NEXT_STA, INPUT);
	digitalWrite(BT_NEXT_STA, HIGH); //pull up resistor
	pinMode(BT_PREW_STA, INPUT);
	digitalWrite(BT_PREW_STA, HIGH); //pull up resistor
	pinMode(BT_NEXT_FREQ, INPUT);
	digitalWrite(BT_NEXT_FREQ, HIGH); //pull up resistor
	pinMode(BT_PREW_FREQ, INPUT);
	digitalWrite(BT_PREW_FREQ, HIGH); //pull up resistor
	FM.setFrequency(87.5);
}

void loop()
{
	lcd.print(FM.readFrequency()); lcd.print(" FM"); //Display frequency
	if (FM.isSearchMode()) {lcd.setCursor(12,0); lcd.print("SCAN"); lcd.setCursor(12,0); lcd.print("    ");} //Display scann
	lcd.setCursor(0,1); lcd.print("LEVEL: "); lcd.print(FM.signalQuality()); lcd.print("/16 ");
	if (FM.isStereo()) {lcd.print("STE"); lcd.print("MONO");} //Display channel MONO or STEREO
	delays(1); //same as delay(1000) Wait 1 second.
}
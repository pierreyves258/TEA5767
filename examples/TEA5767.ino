/*
  TEA5767.ino - Example file for library for using I2C TEA5767 FM recipier with Arduino.
  Created by Pierre-Yves Merle, Januar 11, 2013.
  Released into the public domain.
  
  Connect SDA to A4 on Arduino UNO or 20 on Arduino MEGA
  Connect SCL to A5 on Arduino UNO or 21 on Arduino MEGA
*/

#include <TEA5767.h>

#define delays(x); delay(x*1000); //delay function but with seconds

TEA5767 FM;

void setup()
{
	Serial.begin(9600);
	FM.begin();
	FM.setFrequency(100.2); //Skyrock montpellier
}

void loop()
{
	Serial.print(FM.readFrequency()); Serial.println(" FM"); //Print frequency
	(FM.isStereo())?Serial.println("Stereo");:Serial.println("Mono"); //Print channel
	Serial.print(FM.signalQuality()); Serial.println("/16"); //Print signal quality
	Serial.println("\n"); //Jump 2 lines
	delays(10); //evry 10 seconds (same as delay(10000))
}
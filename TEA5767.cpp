/*
  TEA5767.cpp - Library for using I2C TEA5767 FM recipier with Arduino.
  Created by Pierre-Yves Merle, Januar 11, 2013.
  Released into the public domain.
*/

#include "Arduino.h"
#include "TEA5767.h"
#include <Wire.h>

TEA5767::TEA5767()
{
	//Wire.begin(); //USE begin !
	_search_mode=false;
	_freq_available=0; 
	_channelN=false;
	_signal_quality=0;
}

void TEA5767::begin()
{
	Wire.begin();
}

void TEA5767::setFrequency(double frequency)
{
	_frequencyB=4*(frequency*1000000+225000)/32768; //calculating PLL word
	_frequencyH=_frequencyB>>8;
	_frequencyL=_frequencyB&0XFF;
	Wire.beginTransmission(ADDR);   //writing TEA5767
	Wire.write(_frequencyH);
	Wire.write(_frequencyL);
	Wire.write(SETFREQ);
	Wire.write(0x10);
	Wire.write(0x00);
	Wire.endTransmission();
	delay(100);
}

boolean TEA5767::isSearchMode()
{
	_read();
	return _search_mode;
}

boolean TEA5767::isStereo()
{
	_read();
	return _channelN;
}

int TEA5767::signalQuality()
{
	_read();
	return _signal_quality;
}

double TEA5767::readFrequency()
{
	_read();
	return _frequency;
}

void TEA5767::nextFrequency()
{
	_read();
	setFrequency(_frequency+0.05);
}

void TEA5767::previousFrequency()
{
	_read();
	setFrequency(_frequency-0.05);
}

void TEA5767::nextStation()
{
	_search_mode=1;
	Wire.beginTransmission(ADDR);   
	Wire.write(_frequencyH+0x40);
    Wire.write(_frequencyL);
    Wire.write(SEARCHUP);
    Wire.write(0x1F);
    Wire.write(0x00); 
	Wire.endTransmission();
}

void TEA5767::previousStation()
{
	_search_mode=1;
	Wire.beginTransmission(ADDR);   
	Wire.write(_frequencyH+0x40);
    Wire.write(_frequencyL);
    Wire.write(SEARCHDOWN);
    Wire.write(0x1F);
    Wire.write(0x00); 
	Wire.endTransmission();
}

void TEA5767::_read()
{
	Wire.requestFrom(ADDR,5); //reading TEA5767
	if (Wire.available()) 
	{
		for (int i=0; i<5; i++) 
		{
			_buffer[i]= Wire.read();
		}
	_freq_available=(((_buffer[0]&0x3F)<<8)+_buffer[1])*32768/4-225000;
	_search_mode=!(_buffer[0]&0x80);
    _signal_quality=(_buffer[3]>>4);
	_channelN=(_buffer[2]&0x80);
	_frequency=_freq_available/1000000;
	_frequencyH=((_buffer[0]&0x3F));
	_frequencyL=_buffer[1];
}
}
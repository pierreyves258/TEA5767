/*
  TEA5767.cpp - Library for using I2C TEA5767 FM recipier with Arduino.
  Created by Pierre-Yves Merle, Januar 11, 2013.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WProgram.h"
#include "TEA5767.h"

TEA5767::TEA5767()
{
	//Wire.begin(); //USE begin !
}

TEA5767::begin()
{
	Wire.begin();
}

TEA5767::setFrequency(double frequency)
{
	_frequencyB=4*(frequency*1000000+225000)/32768; //calculating PLL word
	_frequencyH=frequencyB>>8;
	_frequencyL=frequencyB&0XFF;
	Wire.beginTransmission(ADDR);   //writing TEA5767
	Wire.send(frequencyH);
	Wire.send(frequencyL);
	Wire.send(SETFREQ);
	Wire.send(0x10);
	Wire.send(0x00);
	Wire.endTransmission();
	delay(100);
}

bool TEA5767::isSearchMode()
{
	_read();
	return _search_mode;
}

bool TEA5767::isStereo()
{
	_read();
	return _channelN;
}

int TEA5767::signalQuality();
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
	_read;
	setFrequency(_frequency+0.05);
}

void TEA5767::previousFrequency()
{
	_read;
	setFrequency(_frequency-0.05);
}

void TEA5767::nextStation()
{
	_search_mode=1;
	Wire.beginTransmission(ADDR);   
	Wire.send(frequencyH+0x40);
    Wire.send(frequencyL);
    Wire.send(SEARCHUP);
    Wire.send(0x1F);
    Wire.send(0x00); 
	Wire.endTransmission();
}

void TEA5767::previousStation()
{
	_search_mode=1;
	Wire.beginTransmission(ADDR);   
	Wire.send(frequencyH+0x40);
    Wire.send(frequencyL);
    Wire.send(SEARCHDOWN);
    Wire.send(0x1F);
    Wire.send(0x00); 
	Wire.endTransmission();
}

void TEA5767::_read()
{
	Wire.requestFrom(ADDR,5); //reading TEA5767
	if (Wire.available()) 
	{
		for (int i=0; i<5; i++) 
		{
			_buffer[i]= Wire.receive();
		}
	freq_available=(((buffer[0]&0x3F)<<8)+_buffer[1])*32768/4-225000;
	_search_mode=!(buffer[0]&0x80);
    _signal_quality=(buffer[3]>>4);
	_channelN=(buffer[2]&0x80);
	_frequency=_freq_available/1000000;
	_frequencyH=((buffer[0]&0x3F));
	_frequencyL=buffer[1];
}
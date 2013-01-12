/*
  TEA5767.h - Library for using I2C TEA5767 FM recipier with Arduino.
  Created by Pierre-Yves Merle, Januar 11, 2013.
  Released into the public domain.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

#define ADDR 0x60
#define SEARCHUP 0xD0
#define SEARCHDOWN 0x50
#define SETFREQ 0xB0

class TEA5767
{
  public:
	TEA5767();	//done
	void begin();
	boolean isSearchMode();	//done
	int signalQuality(); //done
	double readFrequency(); //done
	void setFrequency(double); //done
	//void searchMode();	//OBSOLET, use next ou previous Station.
	//void stopSearchMode(); //OBSOLET
	void nextStation(); //done
	void previousStation(); //done
	void nextFrequency(); //done
	void previousFrequency(); //done
	boolean isStereo(); //done
  private:
	boolean _search_mode;
	double _freq_available; 
	bool _channelN;
	int _signal_quality;
	unsigned char _buffer[5];
	void _read();
	double _frequency;
	unsigned char _frequencyH;
	unsigned int _frequencyB;
	unsigned char _frequencyL;
};

#endif
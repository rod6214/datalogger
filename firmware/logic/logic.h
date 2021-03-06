/**
 * SB3 Datalogger Project
 * David Turner & Jon Sowman
 * May 2012
 */
#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "system\typedefs.h"

#define TIMER_PRELOAD			111
#define TIMER_ICLK				46875UL
#define TIMER_PSICLK			23437UL
#define MAX_SAMPLE_RATE			20000UL
#define MIN_SAMPLE_RATE			100UL
#define MAX_SAMPLE_NUM			0x20000

#define INT_MODE_TRIGGER		0x00
#define INT_MODE_SAMPLE			0x01

#define MODE_ASYNC				0x01
#define MODE_SYNC				0x02
#define EDGE_RISE				0x04
#define EDGE_FALL				0x08
#define EDGE_BOTH				0x10
#define OPTIONS_VALID			0x80

// Configure the analyser with the options 8-bit bitfield
bool logicConfig(uint8_t options);

// Check whether the supplied options byte is valid
bool verifyOptions(uint8_t options);

// Arm the analyser
bool logicStart(void);

// Getting and setting samplerate and samplenumber
bool setSampleRate(uint32_t* samplerate);
uint32_t getSampleRate(void);
bool setSampleNumber(uint32_t* count);
uint32_t getSampleNumber(void);

// Get the current state of the analyser (LOGIC_POLL)
uint8_t getLogicState(void);

// Fill the USB buffer with data from SRAM
uint8_t* fillUSBBuffer(uint8_t* usbptr);

// Reset the analyser
void logicReset(void);

// Private prototypes
uint8_t _calcPrescaler(uint32_t rate);
uint8_t _calcPreload(uint32_t targetrate, uint8_t ps);
void _beginSampling(uint8_t config);
void _initTimer(void);
void _startTimer(void);
void _startExtInterrupt(uint8_t config);

// ISR prototypes
void low_isr(void);
void high_isr(void);

#endif /* __LOGIC_H__ */

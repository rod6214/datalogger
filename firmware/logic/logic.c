/**
 * SB3 Datalogger Project
 * David Turner & Jon Sowman 2012
 */
#include <p18cxxx.h>
#include <usart.h>
#include <timers.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "io_cfg.h"

/**
 * Set up an interrupt to run at the samplerate,
 * discard data for now.
 */
void initAcquisition(uint16_t samplerate)
{	
	// Enable interrupt priority
	RCONbits.IPEN = 1;

	// Stop timer
	T0CONbits.TMR0ON = 0;

	// Set to 8 bit mode
	T0CONbits.T08BIT = 1;

	// Clock on instruction clock cycles
	T0CONbits.T0CS = 0;
	
	// 256 prescaler
	T0CONbits.PSA = 0;
	T0CONbits.T0PS2 = 1;
	T0CONbits.T0PS1  = 1;
	T0CONbits.T0PS0 = 1;

	// Enable TIMER0 OVF interrupt, periph interrupt
	// and global interrupts
	INTCONbits.TMR0IE = 1;
	INTCONbits.TMR0IF = 0;
	INTCONbits.GIEL  = 1;
	INTCONbits.GIEH = 1;

	// Set TIMER0 OVF to high priority
	INTCON2bits.TMR0IP = 1;

	// Finally enable the timer
	T0CONbits.TMR0ON = 1;
}
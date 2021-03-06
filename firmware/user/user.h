#ifndef PICDEM_FS_DEMO_H
#define PICDEM_FS_DEMO_H

// Includes
#include "system\typedefs.h"

// PICDEM FS USB Demo Version
#define MINOR_VERSION   0x00
#define MAJOR_VERSION   0x01

// Temperature Mode
#define TEMP_REAL_TIME  0x00
#define TEMP_LOGGING    0x01

// Structs
typedef union DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];		// For byte access
    word _word[USBGEN_EP_SIZE/2];	// For word access
    struct
    {
        enum
        {
            READ_VERSION		= 0x00,
            ID_BOARD      	 	= 0x31,
            UPDATE_LED			= 0x32,
            //UCAM
            PING				= 0xDD,
			GET_ADC_COMMAND		= 0xED,
            BLINK_LED_COMMAND	= 0xEE,
            RESET				= 0xFF,
			// Logic analyser commands
			LOGIC_SET_SRATE		= 0x40,
			LOGIC_GET_SRATE		= 0x41,
			
			// Analyser setup and sampling
			LOGIC_CONFIG		= 0x42,
			LOGIC_ARM			= 0x60,
			LOGIC_START			= 0x61,
			LOGIC_WAITING		= 0x62,
			LOGIC_INPROGRESS	= 0x63,
			LOGIC_END			= 0x64,
			LOGIC_POLL 			= 0x65,
			
			// Getting data back from analyser
			LOGIC_DATA			= 0x66,
			LOGIC_END_DATA		= 0x67,
			
			// Other
			LOGIC_RESET			= 0x6E,
			LOGIC_IDLE			= 0x6F,
			LOGIC_ERROR			= 0xAA
        } CMD;
        byte len;
    };
} DATA_PACKET;

// Error values returned by the Logic Analyser
#define	ERROR_CMD_NOT_FOUND				0x01
#define ERROR_INVALID_SAMPLE_RATE		0x02
#define ERROR_INVALID_SAMPLE_NUMBER		0x03
#define ERROR_INVALID_CONFIG			0x04
#define ERROR_END_OF_DATA				0x05
#define ERROR_DATA_UNAVAILABLE			0x06

// Public prototypes
void UserInit(void);
void ProcessIO(void);
void ServiceRequests(void);
void Blink(byte onState);
byte readPOT(void);
void nullSampler(void);
void CallDelay(int delay);
void UserTasks(void);

#endif /* PICDEM_FS_DEMO_H */

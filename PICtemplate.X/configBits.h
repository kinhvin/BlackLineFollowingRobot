//configBits.c
/*******************************************************************
	Configuration Bit Macros
********************************************************************/

// Enable the internal 8MHz Fast RC OSC, Disable Two-speed startup
_FOSCSEL(FNOSC_FRC & IESO_OFF & SOSCSRC_DIG)

// Disable primary oscillator module, Do not route int OSC signal to pins 9-10
_FOSC(POSCMOD_NONE & OSCIOFNC_OFF)

// Disable the watchdog timer
_FWDT(FWDTEN_OFF)

// Use PGED1/PGEC1 pins for program/debug
_FICD(ICS_PGx1)

// Disable deep-sleep watchdog timer
_FDS(DSWDTEN_OFF)


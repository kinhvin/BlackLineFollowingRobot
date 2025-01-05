//TEJ3M mainWritePort.c
/*********************************************************************

Author: Kevin Truong
Date:	Jan 11, 2023

This program turns on certain LEDs in the motor simulator depending on what RA input is high.

Hardware Notes:
 * PIC24FV32KA302 operating at 8MHz

Outputs:
 * RB4:RB11 
********************************************************************/

/*******************************************************************
	Include Files
********************************************************************/
#include "p24FV32KA302.h"
#include "configBits.h"
#include "delay.h"

/*******************************************************************
	Symbolic Constants used by main()
********************************************************************/

/* ----------------------------------------------------------------
Local Function Prototypes
---------------------------------------------------------------- */
void initTimer (void);
/* ----------------------------------------------------------------
Global Variable Declarations
---------------------------------------------------------------- */
// variables declared go here, before main ()
unsigned int allon;
unsigned int alloff;
unsigned int uturn;
/* ----------------------------------------------------------------
main() function
---------------------------------------------------------------- */
int main (void)
{
 //set variable values here
 alloff = 0x0000;
 allon = 0xffff;
 uturn = 0;

 //initialize peripherals
 initTimer();
 
 //teach all PORTB to be outputs
 TRISB=0x00;
 //initialize all PORTB
 LATB=0;
 //initialize all PORTA
 ANSA=0;
 
 while (1)
 {
     // Go forward if both sensors detect white
     if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1)
     {
         LATBbits.LATB6=0;//left back off
         LATBbits.LATB7=1;//left forward on
         LATBbits.LATB8=1;//right forward on
         LATBbits.LATB9=0;//right back off
         delay(40);
         //all off
         LATBbits.LATB6=0; 
         LATBbits.LATB7=0; 
         LATBbits.LATB8=0;
         LATBbits.LATB9=0;  
         delay(80);
     }//end of if
     
     // Turn left
      else if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1)
     {
         LATBbits.LATB6=1;//left backwards on
         LATBbits.LATB7=0;//left forward off
         LATBbits.LATB8=1;//right forward on
         LATBbits.LATB9=0;//right backwards off
         delay(80);
         //all off
         LATBbits.LATB6=0; 
         LATBbits.LATB7=0; 
         LATBbits.LATB8=0;
         LATBbits.LATB9=0;
         delay(60);
     }
     // Turn right
     else if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0)
     {
         LATBbits.LATB6=0;//left backwards off
         LATBbits.LATB7=1;//left forward on
         LATBbits.LATB8=0;//right forward off
         LATBbits.LATB9=1;//right backwards on
         delay(80);
         //all off
         LATBbits.LATB6=0; 
         LATBbits.LATB7=0; 
         LATBbits.LATB8=0;
         LATBbits.LATB9=0;
         delay(60);
     }//end of else if

         // U-Turn
         else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && uturn == 0)
         {
         //move backwards a little
         LATBbits.LATB6=1;//left backwards on
         LATBbits.LATB7=0;//left forward off
         LATBbits.LATB8=0;//right forward off
         LATBbits.LATB9=1;//right backwards on
         delay(150);
         //all off
         LATBbits.LATB6=0; 
         LATBbits.LATB7=0; 
         LATBbits.LATB8=0;
         LATBbits.LATB9=0;
         delay(80);
         //while the left sensor detects white, turn left
         while (PORTAbits.RA0 == 1)
            {
         LATBbits.LATB6=1;//left backwards on
         LATBbits.LATB7=0;//left forward off
         LATBbits.LATB8=1;//right forward on
         LATBbits.LATB9=0;//right backwards off
         delay(80);
         //all off
         LATBbits.LATB6=0; 
         LATBbits.LATB7=0; 
         LATBbits.LATB8=0;
         LATBbits.LATB9=0;
         delay(60);
            } //end of while
         //add 1 to the uturn variable so that the condition to turn will not be met the next time
         uturn=uturn++;
         } //end of else if
 } // end of main while
}
// end main.c
/*******************************************************************
	List of Functions
********************************************************************/

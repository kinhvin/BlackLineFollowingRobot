//delay.h
/*********************************************************************
 This contains all functions that deal with the
 initialization and function of the delay
********************************************************************/

//	List of Functions
/********************************************************************/

/*******************************************************************************
 * Function:        initializeTimer
 *
 * PreCondition:    -
 *
 * Input:           none
 *
 * Output:          none
 *
 * Side Effects:
 *
 * Overview:  This is intended to initialize the microcontroller peripherals
 *            , such as combining Timer2 and Timer3 so that we can generate
 *            delays using a 32-bit register. This will allow us to create very
 *            long delays if needed
 *
 * Note:
 ******************************************************************************/

void initTimer (void)
{

    //Combine Timer2 and Timer3 as a 32-bit Timer
        T2CON = 0;
        T3CON = 0;

    //These settings will do the following:
    // Use Fcyc as source (4MHz)
    // Set prescale to 1:1 = 4MHz
            // -results in 250ns/clock cycle
            // (1/4,000,000 clock cycles/second)
    // Stop any 16-bit Timer2 operation
    // Stop any 16-bit Timer3 operation

        TMR3 = 0; 		//Clear contents of the Timer3 register
        TMR2 = 0; 		//Clear contents of the Timer2 register

	IFS0bits.T3IF = 0;	// Clear out the T3 overflow flag
	T2CONbits.T32 = 1; 	// Enable 32-bit Timer operation
	T2CONbits.TON=1;	// Turn on Timer2 (32-bit Timer2/3)

} //end initializeTimer

/*******************************************************************************
 * Function:        delay
 *
 * PreCondition:    -
 *
 * Input:           number of milliseconds
 *
 * Output:          none
 *
 * Side Effects:    none
 *
 * Overview:  This function generates a delay using milliseconds as the sole
 *            parameter. The Timer2/3 combination keeps track of the number
 *            of clock cycles needed. When that value reaches whatever
 *            is loaded in the PR2 register, an interrupt flag for
 *            is set, indicating the delay is complete. *
 *
 * Note:      32 bits mean 4,294,967,296 (2^32) in decimal
              The smallest value being 0, the largest 4,294,967,295
              This translates into a delay range of 0 up to 1073s! or
 *            17 minutes!! (4,294,967,296/250ns period)
 ******************************************************************************/

void delay (unsigned long milli)
{

    // declare variable to use to calculate PR3:PR2
        unsigned long PeriodRegisterValue;

    //initialize with 32-bit value
        PeriodRegisterValue = milli * 4000ul;

    //Clear Timer Registers
        TMR2 = 0;
        TMR3 = 0;

    //load upper 2 bytes of 32-bit
        PR3 = (unsigned int) (PeriodRegisterValue >> 16);

    //load lower 2 bytes of-32 bit
        PR2 = (unsigned int) (PeriodRegisterValue & 0x0000FFFF);

    //continue to loop until the flag has been set
        while (!IFS0bits.T3IF==1);

    //clear interrupt flag so the entire process can repeat
    //Timer 2 and 3 automatically reset to 0
        IFS0bits.T3IF=0;

} // end delay procedure









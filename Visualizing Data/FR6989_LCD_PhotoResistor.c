#include <msp430.h>
#include "LCDDriver.h"
#include <config.h>


unsigned int percent;
unsigned int volt;
unsigned int hundreds;
unsigned int tens;
unsigned int ones;

void LCDInit();


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //Disables high impedance mode

	LCDInit();
	LED1INIT;
	LED2INIT;
	LED1OFF;
	LED2OFF;


    //ADC config
    REFCTL0=REFON + REFVSEL_2;           //Use a reference voltage of 2.5V
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;   // Sampling time, S&H=16, ADC12 on
    ADC12CTL1 = ADC12SHP;                // Use sampling timer, ADC12SC conversion start, clock=OSC
    ADC12CTL2 |= ADC12RES_2;             // 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_3;           // ADC input select
    ADC12IER0 |= ADC12IE0;               // Enable ADC conv complete interrupt
    ADC12CTL0 |= ADC12ENC;               //Enable conversion
    P1SEL0 |=BIT3;                      //Configure pin 1.3 for input channel 3
    P1SEL1 |=BIT3;

    //TA0 config
    TA0CCTL0 = CCIE;                 // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + ID_3 + MC_1; //SMCLK/8, upmode
    TA0CCR0 =  255;                  //Sets to 1 Hz

    _BIS_SR(LPM0_bits+GIE);

    while(1);
	return 0;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    LED2SWITCH;
    volt=ADC12MEM0/15;
    percent=volt*100/255;

    //Display percent on LCD
    hundreds=percent/100;
    tens=(percent - hundreds*100)/10;
    ones=percent - hundreds*100 - tens*10;

    if(hundreds==0)//not an overflow
    {
        showChar(hundreds+48,1);
        showChar(tens+48,2);
        showChar(ones+48,3);
        showChar(' ',4);
        showChar(' ',5);
        //showChar('%',4);
    }
    else //Overflow
    {
        showChar('O',1);
        showChar('V',2);
        showChar('E',3);
        showChar('R',4);
        showChar('f',5);
    }


    ADC12IFGR0=0; //Reset all Flags, as a precaution
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer1(void)
{
    LED1SWITCH;
    ADC12CTL0 |= ADC12SC;//Start conversion
}

void LCDInit()
{
    PJSEL0 = BIT4 | BIT5;                   // For LFXT

    // Initialize LCD segments 0 - 21; 26 - 43
    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure LFXT 32kHz crystal
    CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
    CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
    do
    {
      CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
      SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
    CSCTL0_H = 0;                           // Lock CS registers

    // Initialize LCD_C
    // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;

    // VLCD generated internally,
    // V2-V4 generated internally, v5 to ground
    // Set VLCD voltage to 2.60v
    // Enable charge pump and select internal reference for it
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;

    LCDCCPCTL = LCDCPCLKSYNC;               // Clock synchronization enabled

    LCDCMEMCTL = LCDCLRM;                   // Clear LCD memory
    //Turn LCD on
    LCDCCTL0 |= LCDON;
}

#include <msp430.h> 
#include <config.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //Disables high impedance mode


    P1SEL1 |= BIT2; // Configure P1.2 for ADC
    P1SEL0 |= BIT2;


    //LEDs for debugging
    LED1INIT;
    LED2INIT;
    LED1OFF;
    LED2OFF;

    //ADC config
    REFCTL0=REFON + REFVSEL_2;           //Use a reference voltage of 2.5V
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;   // Sampling time, S&H=16, ADC12 on
    ADC12CTL1 = ADC12SHP;                // Use sampling timer, ADC12SC conversion start, clock=OSC
    ADC12CTL2 |= ADC12RES_2;             // 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_2;           // ADC input select
    ADC12IER0 |= ADC12IE0;               // Enable ADC conv complete interrupt
    ADC12CTL0 |= ADC12ENC;               //Enable conversion


    //TA1 config
    TB0CCTL0 = CCIE;             // CCR0 interrupt enabled

    TB0CTL=TASSEL_2+ID_3+MC_1; //Sets timer A0 to SMCLK/8 in upmode

    TB0CCR0 = 255; //Sets CCR0

    TB0CCTL3 = OUTMOD_7; //Sets CCR4 to Set/Reset
    TB0CCR3 = 1; //Sets CCR4, higher number= higher brightness

    TB0CCTL4 = OUTMOD_7; //Sets CCR5 to Set/Reset
    TB0CCR4 = 0; //Sets CCR5

    TB0CCTL5 = OUTMOD_7; //Sets CCR3 to Set/Reset
    TB0CCR5 = 0; //Sets CCR3


    //Configure PWM bits(Pin 3.4, 3.5, 3.6)
    P3SEL0 |=BIT4|BIT5|BIT6;
    P3SEL1 &=~(BIT4|BIT5|BIT6);
    P3DIR |=BIT4|BIT5|BIT6;
    //Led goes: Red, ground, Blue, Green
    //Ground is the longest pin

    _BIS_SR(LPM0_bits+GIE);             // Enable interrupt
    while(1);

}

#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void)
{
    LED2SWITCH;
    TB0CCR3=ADC12MEM0/2;
    TB0CCR4=255-TB0CCR3;
    ADC12IFGR0=0; //Reset all Flags, as a precaution
}

#pragma vector=TIMERB0_VECTOR
__interrupt void Timer1(void)
{
    LED1SWITCH;
    ADC12CTL0 |= ADC12SC;//Start conversion
}

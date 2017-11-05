#include <msp430.h>
#include<config.h>


unsigned int Volt=0;


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //LEDs for debugging
    LED2INIT;
    LED1INIT;
    LED1OFF;
    LED2OFF;

    //ADC config
    ADC12CTL0 = ADC12SHT02 + ADC12ON+REFVSEL_2+REFON;// Sampling time, ADC12 on, 2.5V ref
    ADC12CTL1 = ADC12SHP;                     // Use sampling timer
    ADC12MCTL0 |= ADC12INCH_0;               // ADC input select
    ADC12IE = ADC12IE0;                      // Enable interrupt
    ADC12CTL0 |= ADC12ENC;                     //Conversion Enable
    P6SEL |= BIT0;                            // P6.0 ADC option select
    P1DIR |= BIT0;


    //TA0 config
    TA0CCTL0 = CCIE;                 // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + ID_3 + MC_1; //SMCLK/8, upmode
    TA0CCR0 =  255;                  //Sets to 1 Hz

    P1SEL|=BIT2+BIT3;
    P1DIR|=BIT2+BIT3;

    TA0CCTL1 = OUTMOD_7; //Sets CCR1 to Set/Reset
    TA0CCR1 = 1; //Sets CCR1, higher number= higher brightness

    TA0CCTL2 = OUTMOD_7; //Sets CCR2 to Set/Reset
    TA0CCR2 = 0; //Sets CCR2


    ADC12CTL0 |= ADC12SC;//Start conversion

    _BIS_SR(LPM0_bits+GIE);             // Enable interrupt
    while(1);

}
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
   LED2SWITCH;
   Volt=ADC12MEM0/10;
   TA0CCR1=Volt;
   TA0CCR2=255-TA0CCR1;
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0 (void)
{

   // LED1SWITCH;
   ADC12CTL0 |= ADC12SC;// Start conversion-software trigger

}

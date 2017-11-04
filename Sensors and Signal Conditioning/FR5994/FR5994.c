#include <msp430.h>
#include<config.h>

void UARTconfig();

unsigned int tempC=0;
unsigned int tempF=0;
unsigned int res=0;
unsigned int trans=0;
float volt=0;
unsigned int test;
unsigned int ADCMEM;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //Disables high impedance mode

    UARTconfig(); //Configures UART in a separate function

    P1SEL1 |= BIT2+BIT3+BIT4; // Configure P1.2,3,4 for ADC
    P1SEL0 |= BIT2+BIT3+BIT4;


    //LEDs for debugging
    LED2INIT;
    LED1INIT;
    LED1OFF;
    LED2OFF;

    BTN1INIT;

    //ADC config
   REFCTL0=REFON + REFVSEL_2;              //Use a reference voltage of 2.5V
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;      // Sampling time, S&H=16, ADC12 on
    ADC12CTL1 = ADC12SHP;                   // Use sampling timer, ADC12SC conversion start, clock=OSC
    ADC12CTL2 |= ADC12RES_2;                // 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_2;              // ADC input select
    ADC12MCTL1 |= ADC12INCH_3;              // ADC input select
    ADC12MCTL2 |= ADC12INCH_4;              // ADC input select
    ADC12IER0 |= ADC12IE0 | ADC12IE1 | ADC12IE2;// Enable ADC conv complete interrupt
    ADC12CTL0 |= ADC12ENC;                   //Enable conversion


    //TA0 config
    TA0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA0CTL = TASSEL_1 + ID_3 + MC_1;    //ACLK/8, upmode
    TA0CCR0 =  1088;                  //Sets to 1 Hz

    ADC12CTL0 |= ADC12SC;//Start conversion

    _BIS_SR(LPM0_bits+GIE);             // Enable interrupt
    while(1);

}
#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void)
{
    LED2SWITCH;
    /*if(ADC12IFG0) //input channel 2 complete
    {
        test=ADC12MEM0;
        volt=test/1000; Converts mV to V
       res=(3300.0/volt) - 1000;
        while(!(UCA0IFG&UCTXIFG));
            UCA0TXBUF = res; //Send over UART
    }*/
    if(ADC12IFG1)//input channel 3 complete
    {
        ADCMEM=ADC12MEM1;
        tempC=ADCMEM / 100;
        tempF=9*tempC/5+32;
        while(!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = tempF; //Send over UART
        ADC12IFGR0 &= ~ADC12IFG1; //Reset Flag
    }
/*
    if(ADC12IFG2)//input channel 4 complete
    {
        while(!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = ADC12MEM2;
    }
    */
   ADC12IFGR0=0; //Reset All Flags, as a precaution
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0 (void)
{

   // LED1SWITCH;
    //ADC12CTL0 |= ADC12SC;// Start conversion-software trigger

}
#pragma vector=PORT5_VECTOR
__interrupt void Button (void)
{
    //LED2SWITCH;
    ADC12CTL0 |= ADC12SC;// Start conversion-software trigger
    BTN1CLR;
}
void UARTconfig()
{
    // Configure GPIO
    P2SEL0 &= ~(BIT0 | BIT1);
    P2SEL1 |= BIT0 | BIT1;                  // USCI_A0 UART operation

    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;           // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // Set all dividers
    CSCTL0_H = 0;                           // Lock CS registers

    // Configure USCI_A0 for UART mode
    UCA0CTLW0 = UCSWRST;                    // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;             // CLK = SMCLK
    UCA0BRW = 52;                           // 8000000/16/9600
    UCA0MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
    UCA0CTLW0 &= ~UCSWRST;                  // Initialize eUSCI
}


#include <msp430.h>
int input=0;
float volt =0;
float res=0;
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  UART_config();
  Timer_config();
  ADC10_config();
  
  __bis_SR_register(GIE);       // enable interrupts
    while(1){

    }

}
//============================ Configurations ===================================================
//-------------------------------- ADC10 ----------------------------------------------------------
void ADC10_config()
{
    ADC10CTL1 = INCH_7 + SHS_1;               // P1.7, TA1 trigger sample start
      ADC10AE0 = 0x80;                          // P1.7 ADC10 option select
      P1DIR |= 0x01;                            // Set P1.0 to output direction
}
//-------------------------------- Timer --------------------------------------------------------
void Timer_config()
{
    
    TACCTL0 = CCIE;                           // Enable interrupt
    TACCR0 = 4096-1;                            // PWM Period
    TACCTL1 = OUTMOD_3;                       // TACCR1 set/reset
    TACCR1 = 256;                               // TACCR1 PWM Duty Cycle
    TACTL = TASSEL_1 + MC_1 + ID_3;                  // ACLK, up mode   
}
//-------------------------------- UART ---------------------------------------------------------
void UART_config()
{
    if (CALBC1_1MHZ==0xFF)                  // If calibration constant erased
      {
        while(1);                               
      }
      DCOCTL = 0;                               // Select lowest DCOx and MODx settings
      BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
      DCOCTL = CALDCO_1MHZ;
      P1SEL |= BIT1 + BIT2 + BIT5;              // P1.1 = RXD, P1.2=TXD
      P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
      UCA0CTL1 |= UCSSEL_2;                     // SMCLK
      UCA0BR0 = 104;                            // 1MHz 9600
      UCA0BR1 = 0;                              // 1MHz 9600
      UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
      UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  //    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}
//============================== Interrupts ========================================================
//----------------------------- ADC10 -----------------------------------------------------------
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)

{
  ADC10CTL0 &= ~ENC;                        // ADC10 disabled
  ADC10CTL0 = 0;                            // ADC10, Vref disabled completely
  //- - - - - - - - - - - - Calculations - - - - - - - - - - - - - - - - - - - - - 
  input = ADC10MEM;
  volt = input *0.0032;
  res=(3300.0/volt) - 1000;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  UCA0TXBUF = res;                     //send to TX

}

//-------------------------------- Timer A0---------------------------------------------------------------
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)

{
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE;
  ADC10CTL0 |= ENC;                         // ADC10 enable set

}

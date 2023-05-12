/*
 * Part3.c
 *
 *      Author: Elise Heim
 *
 */

#include <msp430.h>

void LEDSetup();
void ButtonSetup();
void timerInit();

int time;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5; //unlock MSP
 
  void LEDSetup();
  void ButtonSetup();
  void timerInit();
__bis_SR_register(LPM3_bits | GIE);
}

void LEDSetup()
{
  P1DIR |= BIT0; //set red led as output, 1.0
  P1OUT &= ~BIT0; //clear previous config for red led, 1.0
}

void ButtonSetup()
{
  P2DIR &= ~BIT3; //set button 2.3 as input
  P2REN |= BIT3; //enable button 2.3
  P2OUT |= BIT3; //pull up resistor
  P2IES &= ~BIT3; //low to high edge
  P2IFG =| BIT3; 
  P2IE |= BIT3;
  
  P4DIR &= ~BIT1; //set button 4.1 as input
  P4REN |= BIT1; //enable button 4.1
  P4OUT |= BIT1; //pull up resistor
  P4IES &= ~BIT1; //low to high edge
  P4IFG =| BIT1; 
  P4IE |= BIT1; 
}

void timerInit()
{
  TB1CCTL0 |= CCIE; //timer B control interrupt enable
  TB1CCR0 = 8000; // just under 4 Hz
  TB1CTL = TBSSEL_1 | MC_2 | TBCLR; //A clock continuous, clear timer
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT ^= BIT0; //toggle red led, 1.0
    TB0CCTL0 &= ~CCIFG; // clear flag
    TB1CCR0 += time; 
}

#pragma vector=PORT2_VECTOR
__interrupt void ISR_Port2_S3(void)
{
    TB1CTL |= TBCLR; // clear timer B
    P2IFG &= ~BIT3; //clear 2.3 flag 
  
    if (!(P2IN &= ~BIT3)) //if button 2.3 pressed 
    {
      P2IES &= ~BIT3; //look for low to high
      TB1CCR0 = 0;
      P1OUT &= ~BIT0; //turn off red led, 1.0
    }
    else
    {
      P2IES |= BIT3; //look for high to low
      TB1CCR0 = time;
      P1OUT |= BIT0; //turn on red led, 1.0
    }
}
#pragma vector=PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    TB1CTL |= TBCLR; // clear timer B
    TB1CCR0 = 8000;
    P4IFG &= ~BIT1; //clear 4.1 flag 
}



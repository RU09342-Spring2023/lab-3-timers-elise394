/*
 * Part2.c
 *
 *  Created on: Feb 11, 2023
 *  Author: Russell Trafford
 * Changes made by Elise Heim
 *      This code will need to change the speed of an LED between 3 different speeds by pressing a button.
 */

#include <msp430.h>

void gpioInit();
void timerInit();

void main(){

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    gpioInit();
    timerInit();
    
    int counter = 20000;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);

}


void gpioInit(){
    // @TODO Initialize the Red or Green LED
    P1DIR |= BIT0; //1.0 as output
    P1OUT &= ~BIT0; //1.0 clear previous config
    
    // @TODO Initialize Button 2.3
    P2OUT |= BIT3; //2.3 pulled up
    P2REN |= BIT3; //pull up register enabled for 2.3
    P2IES &= ~BIT3; //low to high edge 
    P2IE |= BIT3; // interrupt enabled for 2.3
}

void timerInit(){
    // @TODO Initialize Timer B1 in Continuous Mode using ACLK as the source CLK with Interrupts turned on
    TB1CCTL0 = CCIE; //interrupt enabled
    TB1CCR0 = 50000; //set max for timer B
    TB1CTL = TBSSEL_1 | MC_2; // ACLK as continuous 
     
}


/*
 * INTERRUPT ROUTINES
 */

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO Remember that when you service the GPIO Interrupt, you need to set the interrupt flag to 0.
    P1OUT ^= BIT0; //toggle red led, 1.0
    // @TODO When the button is pressed, you can change what the CCR0 Register is for the Timer. You will need to track what speed you should be flashing at.
    P2IFG &= ~BIT3; //set interrupt flag as 0
    
    switch(counter) //cycle through the different clock cycles
    {
        case 0: {
            TB1CCR0 = 20000;
            counter++;
            break;
        }
    }
        case 1: {
            counter = 5000;
            counter++;
            break;
        }
    
        case 2: {
            counter = 50000;
            counter++;
            break;
        }
        
    }

// Timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    // @TODO You can toggle the LED Pin in this routine and if adjust your count in CCR0.
    P1OUT ^= BIT0; toggle red led, 1.0
    TB1CCR0 += counter; // add offset that's equal to counter
}



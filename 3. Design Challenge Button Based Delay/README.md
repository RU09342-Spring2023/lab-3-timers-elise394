Thise is how my program works. I started by creating some functions to set up the LED, buttons, and timer. I also made a time variable. I then stopped the watchdog timer, unlocked the MSP, and called my functions in the main function.

My LED setup was simple, and consisted of me setting the red LED 1.0 as an output, and then clearing any previous configurations for it. 

The ButtonSetup function consisted of setting button 2.3 as an input, enabling it, setting it as pulled up, low to high edged, and with a flag generator. I followed the same steps for button 4.1. 

For the Timer B function, I enabled it, set it to just under 4 Hz (8000), and used A clock. I used a clock divider, and cleared the timer afterwardss. 

I also set the interrupt so that upon a flag, it would toggle the red LED, clear the flag, and added time to the timer. 

In setting up my interrupt for my 2.3 button, I started by clearing the timer and interrupt flag. Then, if the button was pressed, I ensured that it looked for a low to high clock edge, set the timer to 0, and turned off the red LED. If the button was not pressed, the interrupt would look for a high to low edge, set the timer equal to my time variable, and turn off the red LED. 

For my 4.1 button interrupt, I started by clearing the timer, clearing the interrupt flag, and setting the timer equal to my own value of 8000, which is just below 4 Hz. 

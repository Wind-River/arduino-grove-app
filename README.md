# Using an Arduino style API with the Grove Starter Kit

This example demonstrates the use of an Arduino style API in combination with devices from the Grove Starter Kit. 

You can configure the project to build an application that includes various functionality. Configuration is controlled through the use of macros defined at the beginning of the code as follows:

 - ENABLE_GROVE_KIT    (defined by default)
 - ENABLE_LCD          (defined by default) 
 - ENABLE_INTERRUPT

By default, the ENABLE_GROVE_KIT and ENABLE_LCD macros are defined meaning that the built code will include support for several components from the Grove Starter Kit (including a push button switch, a rotary angle sensor and an LCD display). For the example code to run correctly (if the Grove Starter Kit is used) then the following should be connected:

 * the Grove Shield should be plugged onto the Galileo Gen2 board
 * plug the LCD Display into one of the I2C connectors
 * plug the Push Button into the D3 connector
 * plug the LED adaptor board (with an LED) into the D6 connector
 * plug the Rotary angle sensor (potentiometer) into the A0 connector

If the ENABLE_GROVE_KIT macro is undefined then the code will be configured to accept text input and provide text output at the console (i.e. no external sensors or displays are used).

If the ENABLE_INTERRUPT macro is defined then the code will be configured to used (polled mode) interrupts to sense a change of state in the push button switch. Without this macro being defined the push button switch is sensed using an Arduino style digitalRead() statement on each cycle within the loop() function.

## More Information

Instructions for running this example are available from the  
[example wiki](https://github.com/???).

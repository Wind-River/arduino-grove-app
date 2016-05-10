/* 
 * Copyright (c) 2016, Wind River Systems, Inc. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, are 
 * permitted provided that the following conditions are met: 
 * 
 * 1) Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer. 
 * 
 * 2) Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation and/or 
 * other materials provided with the distribution. 
 * 
 * 3) Neither the name of Wind River Systems nor the names of its contributors may be 
 * used to endorse or promote products derived from this software without specific 
 * prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

/* 
 * DESCRIPTION
 * A simple sample program using an Arduino style API and sensors from the 
 * Grove Starter Kit.
 * 
 * Connect the Grove Start Kit as follows:
 *    Connector D3 = Push button
 *    Connector D6 = LED
 *    Connector A0 = Rotary angle sensor (potentiometer)
 *    I2C          = LCD Display
 */

#include <Arduino-lite.h>

/* Set the following defines to configure the code:
 *  ENABLE_GROVE_KIT - define this if you have a Grove Starter Kit connected to 
 *                     the Galileo Gen2. Connect the components of the kit as
 *                     shown in the section above.
 *  ENABLE_INTERRUPT - define this to enable changing of LED state via an
 *                     Arduino style interrupt. If this is not enable then the 
 *                     LED state is changed within the loop(). You must also 
 *                     define the ENABLE_GROVE_KIT macro.
 *  ENABLE_LCD       - define this macro to switch on the LCD and display the
 *                     raw output value of the potentimeter. You must also 
 *                     define the ENABLE_GROVE_KIT macro. 
 */
#define ENABLE_GROVE_KIT
#define ENABLE_LCD         /* ENABLE_GROVE_KIT must also be defined ! */
#undef  ENABLE_INTERRUPT   /* ENABLE_GROVE_KIT must also be defined ! */

/* Include additional libraries we will be using... */
/* ... the Wire library */
#include <Wire.h>
/* ... the rgb_lcd (Grove LCD display) library */
#include <rgb_lcd.h>

const int pinButton     = 3;
const int pinLed        = 6;
const int boardLed      = 13;    // LED built onto board
const int potentiometer = A0;

int lastValue = 0;

#ifdef ENABLE_LCD
 char tstring[32];
#endif

#ifdef ENABLE_INTERRUPT
 int ledOn = 0;
 void intCallback1(void) {
    ledOn = !ledOn;
    if(ledOn)                	// when button is pressed
    {
        digitalWrite(boardLed, HIGH);         // led on
    }
    else
    {
        digitalWrite(boardLed, LOW);          // else LED is off
    }
 }
#endif

void setup()
{
    pinMode(pinButton, INPUT);                // set button INPUT
    pinMode(boardLed, OUTPUT);                // set led OUTPUT
    pinMode(potentiometer, INPUT);            // set potentiometer INPUT
    
#ifdef ENABLE_LCD
    Wire.begin();
    lcd.begin(16,2);                /* set LCD to 16 columns, 2 lines */
    lcd.setRGB(0xe0, 0x10, 0x10);   /* LCD backlight goes red */
#endif   /* ENABLE_LCD */

#ifdef ENABLE_INTERRUPT
    attachInterrupt(pinButton, intCallback1, RISING);
#endif   /* ENABLE_INTERRUPT */
}

void loop()
{
#ifdef ENABLE_GROVE_KIT
    int inputValue;
    int outputValue;
    
    inputValue = analogRead(potentiometer);   // read the potentiometer

#ifdef ENABLE_LCD
    /* show raw A0 output on LCD */
    sprintf(tstring, "Input A0 = %d", inputValue);
    lcd.print(tstring, 1);
#endif   /* ENABLE_LCD */

    if(inputValue != lastValue) 
    {
        Serial.print((char *)"Potentiometer value changed to : ");
        Serial.println(inputValue);               // print pot value to screen

        outputValue = map(inputValue, 0, 1023, 0, 255);   // convert from 10 bit to 8 bit
        analogWrite(IO6, outputValue);            // set LED brightness to pot level

        lastValue = inputValue;
    }

#ifndef ENABLE_INTERRUPT
    if(digitalRead(pinButton))                // when button is pressed
    {
        digitalWrite(boardLed, HIGH);         // led on
    }
    else
    {
        digitalWrite(boardLed, LOW);          // else LED is off
    }
#endif   /* !ENABLE_INTERRUPT */

    delay(200);                               // wait for 0.2 second

#else
	char * ptr_end;
	long int iNum;
    char * myText;
    
    Serial.println((char *)"Please input a number between 0 and 90 :");
    myText = Serial.readString();
    if(isDigit(*myText)) {
    	iNum = strtol (myText,&ptr_end,10);
        if((iNum > 90) || (iNum < 0)) {
            Serial.println((char *)"Error : that number is outside the limits !");
        } else {
            float rads = (iNum * M_PI / 180.0);
            Serial.print((char *)"The number you input is ");
            Serial.println((int)iNum);
            Serial.print((char *)" The sine of that number is ");
            Serial.println(sin((float)rads), 4);
            Serial.print((char *)" The cosine of that number is ");
            Serial.println(cos((float)rads), 4);
            Serial.print((char *)" The tangent of that number is ");
            Serial.println(tan((float)rads), 4);
        }
    } else {
        Serial.println((char *)"Error : your text started with a non-numeric character !");
    }
#endif   /* !ENABLE_GROVE_KIT */
    
}

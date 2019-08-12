/* ========================================
 * This code will test/use the functionality of all of the below peripherals.
 * Fully working code: 
 * PWM      : 
    Cycle up and down when enabled
 * Encoder  : 
    Calibrate the wheels when enabled

 * ADC      :
    Prints the ADC reading (in volts) to UART

 * USB      : port displays speed and position.

 * CMD: "PW xx"

 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
//* ========================================
#include "defines.h"
#include "vars.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================



void cycle_PWM()
{
    uint16 fluct;
    
    for(fluct = 30; fluct <= 100; fluct++)
    {
        PWM_1_WriteCompare(fluct);
        PWM_2_WriteCompare(fluct);
        CyDelay(30);
    }
    
    for(fluct = 100; fluct >= 30; fluct--)
    {
        PWM_1_WriteCompare(fluct);
        PWM_2_WriteCompare(fluct);
        CyDelay(30);
    }
    
}

int main()
{  

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    
    
     PWM_1_Start();// starting the pwm
     PWM_2_Start();// starting the pwm

// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);

    //usbPutString("Started");
    for(;;)
    {
        /* Place your application code here. */
        cycle_PWM();
        handle_usb();
        if (flag_KB_string == 1)
        {
            usbPutString(line);
            flag_KB_string = 0;
        }     
        
    }   
}
//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')

#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
#endif    
}
//* ========================================

void uart_set_PWM()
{
    uint8 c;
     if (USBUART_DataIsReady() != 0)
        {  
            c = USBUART_GetChar();
            
            if(c <= 100 && c > 0){
                PWM_1_WriteCompare(c);
                usbPutString(c);
            }
        }
}

void handle_usb()
{
    // handles input at terminal, echos it back to the terminal
    // turn echo OFF, key emulation: only CR
    // entered string is made available in 'line' and 'flag_KB_string' is set
    
    static uint8 usbStarted = FALSE;
    static uint16 usbBufCount = 0;

    if (!usbStarted)
    {
        if (USBUART_GetConfiguration())
        {
            USBUART_CDC_Init();
            usbStarted = TRUE;
        }
    }
    else
    {
       
    }    
}


/* [] END OF FILE */

/* ========================================
 * This code will test/use the functionality of all of the below peripherals.
 * Fully working code: 
 * PWM      : done
    Cycle up and down when enabled
 * Encoder  : 
    Calibrate the wheels when enabled

 * ADC      : done
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

//ADC:
CY_ISR (adc_isr)
{
    adc_result = ADC_GetResult16(0);
    flag_receive_ADC = 1;
    LED_Write(~LED_Read());
}

CY_ISR (isr_quad1)
{
    //LED_Write(~LED_Read());
    quad_count1 = QuadDec_M1_GetCounter();
    quad_count2 = QuadDec_M2_GetCounter();
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    flag_calc_wheelspeed = 1;
}

void Quad_Dec_response()
{
    //Check if the flag has been set
    if (!flag_calc_wheelspeed) return;
    flag_calc_wheelspeed = 0;
    
    char wheel_1_str [16];
    char wheel_2_str [16];
    sprintf(wheel_1_str, "quad count 1 is: %d\n\r", quad_count1);
    usbPutString(wheel_1_str);
    sprintf(wheel_2_str, "quad count 2 is: %d\n\r", quad_count2);
    
    usbPutString(wheel_2_str);
    
    int16 relativeSpeed = quad_count1 - quad_count2;
    
    //if rs is positive, quad count 1 is larger
    //if rs is negative, quad count 2 is larger
    if(relativeSpeed > 0)
    {
        
    }
    else if (relativeSpeed < 0)
    {
        
    }
}    

void print_ADC()
{
   //usbPutString("HII\n");
    if(flag_receive_ADC == 1)
    {
        //usbPutString("AAA\r\n");
        flag_receive_ADC = 0;
        
       // int8 channel = ADC_
        int16 converted_val = (484 * adc_result) / 4096;
        
        char result_str[16];
        sprintf(result_str, "%d\n\r", converted_val);
        
        usbPutString(result_str);
    }
}


//PWM:
void cycle_PWM()
{
    uint16 fluct;
    if (direction == 0){
        for(fluct = 25; fluct < 100; fluct++)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
        
        for(fluct = 100; fluct > 25; fluct--)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
    } else {
        for(fluct = 100; fluct > 25; fluct--)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
        
        for(fluct = 25; fluct < 100; fluct++)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
    }
    direction = !direction;
    M1_IN2_Write(direction);
    M2_IN2_Write(direction);
}

int main()
{  

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    if(ENABLE_PWM)
    {
        PWM_1_Start();// starting the pwm
        PWM_2_Start();// starting the pwm
    }
    
    if(ENABLE_ADC)
    {
        ADC_Start();
        isr_eoc_StartEx(adc_isr);
        ADC_StartConvert();
    }
    
    if (ENABLE_QUAD)
    {
        QuadDec_M1_Start();
        QuadDec_M2_Start();
        
        isr_quad1_StartEx(isr_quad1);
        
        Timer_1_Start();
        
        //isr_quad1_Start();
    }

// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);

    //usbPutString("Started");
    for(;;)
    {
        /* Place your application code here. */
        if(ENABLE_PWM && ENABLE_CYCLE) cycle_PWM();
        if(ENABLE_ADC) print_ADC();
        if(ENABLE_QUAD) Quad_Dec_response();
        
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
            usbPutString("Started\n");
        }
    }
    else
    {
       
    }    
}


/* [] END OF FILE */

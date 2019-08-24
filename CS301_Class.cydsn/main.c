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

void setSpeed(int right, int left){
    leftSpeedLimit = right;
    rightSpeedLimit = left;
}

void brakeMotor(){
    setSpeed(0, 0);
    PWM_1_WriteCompare(0);
    PWM_2_WriteCompare(0);
    right_duty_cycle = 0;
    left_duty_cycle = 0;
}

//ADC:
CY_ISR (adc_isr)
{
    //adc_result = ADC_GetResult16(0);
    adc_result = ADC_GetResult16();
    flag_receive_ADC = 1;
    //LED_Write(~LED_Read());
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

CY_ISR (Stop_on_line)
{
    brakeMotor();
}

CY_ISR (button)
{
    LED_Write(~LED_Read());
    setSpeed(30, 30);
}

void Quad_Dec_response()
{
    //Check if the flag has been set
    if (!flag_calc_wheelspeed) return;
    flag_calc_wheelspeed = 0;
    
    char wheel_1_str [64];
    char wheel_2_str [64];
    sprintf(wheel_1_str, "quad count 1 is: %d\n\r", quad_count1);
    usbPutString(wheel_1_str);
    sprintf(wheel_2_str, "quad count 2 is: %d\n\r", quad_count2);
    
    usbPutString(wheel_2_str);
    
    int16 leftSpeed = quad_count1;
    int16 rightSpeed = quad_count2;
    
    int16 left_direction = 1;
    int16 right_direction = 1;
    
    if (leftSpeed >= 0) {
        left_direction = 1;
    } else {
        left_direction = -1;
    }
    if (rightSpeed <= 0) {
        right_direction = 1;
    } else {
        right_direction = -1;
    }
    
    if (abs(leftSpeed) > leftSpeedLimit){
        //sprintf(wheel_1_str,"Left wheel too fast! Slowing down \r\n");
        usbPutString(wheel_1_str);
        
        left_duty_cycle = left_duty_cycle + (-1 * left_direction);
    } else if (abs(leftSpeed) < leftSpeedLimit) {
       // sprintf(wheel_1_str,"Left wheel too slow! Speeding up \r\n");
        usbPutString(wheel_1_str);
        left_duty_cycle = left_duty_cycle + left_direction;
    }
    
    if (abs(rightSpeed) > rightSpeedLimit){
        sprintf(wheel_2_str,"Right wheel too fast! Slowing down \r\n");
        usbPutString(wheel_2_str);
        right_duty_cycle = right_duty_cycle + (-1 * right_direction);
        sprintf(wheel_2_str,"Right wheel duty cycle is now:%d\r\n", right_duty_cycle);
        usbPutString(wheel_2_str);
    } else if (abs(rightSpeed) < rightSpeedLimit) {
        sprintf(wheel_2_str,"Right wheel too slow, speeding up! \r\n");
        usbPutString(wheel_2_str);
        sprintf(wheel_2_str,"Right wheel duty cycle is now:%d\r\n", right_duty_cycle);
        usbPutString(wheel_2_str);
        right_duty_cycle = right_duty_cycle + right_direction;
    }
    
    if(right_duty_cycle < 0) right_duty_cycle = 0;
    if(left_duty_cycle < 0) left_duty_cycle = 0;
    PWM_1_WriteCompare(left_duty_cycle);
    PWM_2_WriteCompare(right_duty_cycle);
        
}

void print_ADC()
{
   //usbPutString("HII\n");
    if(flag_receive_ADC == 1)
    {
        //usbPutString("AAA\r\n");
        flag_receive_ADC = 0;
        
       // int8 channel = ADC_
        float scalingFactor = 0.972;
        int16 converted_val = (5000 * adc_result) / 4096 * scalingFactor * 2;
        
        char result_str[16];
        sprintf(result_str, "Battery Voltage: %dmv\n\r", converted_val);
        
        //usbPutString(result_str);
    }
}


//PWM:
void cycle_PWM()
{
    uint16 fluct;
    if (direction == 0){
        for(fluct = 30; fluct < 70; fluct++)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
        
        for(fluct = 70; fluct > 30; fluct--)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
    } else {
        for(fluct = 70; fluct > 30; fluct--)
        {
            PWM_1_WriteCompare(fluct);
            PWM_2_WriteCompare(fluct);
            CyDelay(30);
        }
        
        for(fluct = 30; fluct < 70; fluct++)
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
    
    if(ENABLE_STOP){
        isr_OnLine_StartEx(Stop_on_line);
        isr_button_StartEx(button);
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

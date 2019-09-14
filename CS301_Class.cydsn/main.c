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
#include <math.h>
//* ========================================
#include "defines.h"
#include "vars.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
//void handle_usb();
//* ========================================


void handle_rx_binary()
{
    if(flag_rx == 1)
    {    
        flag_rx = 0;
        
        uint16 packet_bytes = (packet[1] << 8) | (packet[0]);
        //uint16 packet_bytes = packet[0] & packet[1];
        char byte_packet[12];
        char string_packet[12];
        //sprintf(string_packet, "%d", packet_bytes);
        //sprintf(byte_packet, "%d", (int8)packet[0]);
       // sprintf(string_packet, "%d", packet_bytes);
        //usbPutString(string_packet);
       // usbPutString(string_packet);
       // usbPutChar(' ');
        
        switch(byteCount)
        {
            case 4:
                //usbPutString("RSSI:");
                //usbPutString(byte_packet);
                //usbPutString("\r\n");
                buffer_state.rssi = packet[0];
                buffer_state.index = packet[1];
            break;
            case 6:
                //usbPutString("robot_x:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.robot_xpos = packet_bytes;
            break;
            case 8:
                //usbPutString("robot_y:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.robot_ypos = packet_bytes;
            break;
            case 10:
                //usbPutString("robot_dir:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.robot_orientation = packet_bytes;
            break;
            case 12:
                //usbPutString("g0_x:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g0_xpos = packet_bytes;
            break;
            case 14:
                //usbPutString("g0_y:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g0_ypos = packet_bytes;
            break;
            case 16:
                //usbPutString("g0_speed:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g0_speed = packet_bytes;
            break;
            case 18:
                //usbPutString("g1_dir:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g0_direction = packet_bytes;
            break;
            case 20:
                //usbPutString("g1_x:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g1_xpos = packet_bytes;
            break;
            case 22:
                //usbPutString("g1_y:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g1_ypos = packet_bytes;
            break;
            case 24:
                //usbPutString("g1_speed:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g1_speed = packet_bytes;
            break;
            case 26:
                //usbPutString("g1_dir:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g1_direction = packet_bytes;
            break;
            case 28:
                //usbPutString("g2_x:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g2_xpos = packet_bytes;
            break;
            case 30:
                //usbPutString("g2_y:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g2_ypos = packet_bytes;
            break;
            case 32:
                //usbPutString("g1_speed:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                buffer_state.g2_speed = packet_bytes;
            break;
            case 34:
                buffer_state.g2_direction = packet_bytes;
                //usbPutString("g2_dir:");
                //usbPutString(string_packet);
                //usbPutString("\r\n");
                
            break;
        }
        
    }
}

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

//Binary RF Data
CY_ISR(rxInt){
    char rf_char = UART_GetChar();
    if(rf_char == SOP){
            //we should evalute whether the last packet was valid by measuring the length of data
            if(byteCount == 34)
            {
                system_state = buffer_state;
            }
            byteCount = 2; //2 for legacy purposes - fix this
            flag_rx = 0;
             //LED_Write(~LED_Read()); //flash an LED so we know the interrupt is called
        }
        else
        {
            packet[byteCount % 2] = rf_char;
           
            if(byteCount % 2 == 1) //we have received a whole 16-bit packet
            {
                flag_rx = 1;
            }
            byteCount = (byteCount + 1);
        }
}

//ADC:
CY_ISR (adc_isr)
{
    //adc_result = ADC_GetResult16(0);
    adc_result = ADC_GetResult16();
    flag_receive_ADC = 1;
    flag_print_rf = 1;
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
    direction = !direction;
    M1_IN2_Write(direction);
    M2_IN2_Write(direction);
    setSpeed(20, 20);
}

CY_ISR(isr_adcTimer)
{
    ADC_StartConvert();
}

void Quad_Dec_response()
{
    //Check if the flag has been set
    if (!flag_calc_wheelspeed) return;
    flag_calc_wheelspeed = 0;
    
    char wheel_1_str [64];
    char wheel_2_str [64];
    sprintf(wheel_1_str, "quad count 1 is: %d\n\r", quad_count1);
    //usbPutString(wheel_1_str);
    sprintf(wheel_2_str, "quad count 2 is: %d\n\r", quad_count2);
    
    //usbPutString(wheel_2_str);
    
    int16 leftSpeed = quad_count1;
    int16 rightSpeed = quad_count2;
//    
//    int16 left_direction = 1;
//    int16 right_direction = 1;
//    
//    if (leftSpeed > 0) {
//        left_direction = -1;
//    } else {
//        left_direction = 1;
//    }
//    if (rightSpeed < 0) {
//        right_direction = -1;
//    } else {
//        right_direction = 1;
//    }
//    
    int interCalc = leftSpeedLimit - abs(leftSpeed);
    int nextSpeed = (abs(interCalc) / interCalc) * sqrt(abs(interCalc));
    left_duty_cycle = left_duty_cycle + nextSpeed;
    interCalc = rightSpeedLimit - abs(rightSpeed);
    nextSpeed = (abs(interCalc) / interCalc) * sqrt(abs(interCalc));
    right_duty_cycle = right_duty_cycle + nextSpeed;
//    
//    if (abs(leftSpeed) > leftSpeedLimit){
//        //sprintf(wheel_1_str,"Left wheel too fast! Slowing down \r\n");
//        //usbPutString(wheel_1_str);
//        
//        left_duty_cycle = left_duty_cycle + (-1 * left_direction);
//    } else if (abs(leftSpeed) < leftSpeedLimit) {
//       // sprintf(wheel_1_str,"Left wheel too slow! Speeding up \r\n");
//        //usbPutString(wheel_1_str);
//        left_duty_cycle = left_duty_cycle + left_direction;
//    }
//    
//    if (abs(rightSpeed) > rightSpeedLimit){
//        sprintf(wheel_2_str,"Right wheel too fast! Slowing down \r\n");
//       // usbPutString(wheel_2_str);
//        right_duty_cycle = right_duty_cycle + (-1 * right_direction);
//        sprintf(wheel_2_str,"Right wheel duty cycle is now:%d\r\n", right_duty_cycle);
//        //usbPutString(wheel_2_str);
//    } else if (abs(rightSpeed) < rightSpeedLimit) {
//        sprintf(wheel_2_str,"Right wheel too slow, speeding up! \r\n");
//        //usbPutString(wheel_2_str);
//        sprintf(wheel_2_str,"Right wheel duty cycle is now:%d\r\n", right_duty_cycle);
//        //usbPutString(wheel_2_str);
//        right_duty_cycle = right_duty_cycle + right_direction;
//    }
    
    if(right_duty_cycle < 0) right_duty_cycle = 0;
    if(left_duty_cycle < 0) left_duty_cycle = 0;
    if(right_duty_cycle > 100) right_duty_cycle = 100;
    if(left_duty_cycle > 100) left_duty_cycle = 100;
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
        converted_val = (converted_val + prevVoltage + prevVoltage2) / 3; //smooth rapid changes in the voltage
        prevVoltage2 = prevVoltage;
        prevVoltage = converted_val;
        
        char result_str[16];
        sprintf(result_str, "Battery Voltage: %dmv\n\r", converted_val);
        
        usbPutString(result_str);
    }
}

void print_RF()
{
    if(flag_print_rf == 1)
    {
        char printString[16];
        flag_print_rf = 0;
        usbPutString("RSSI:");
        sprintf(printString, "%d\r\n", system_state.rssi);
        usbPutString(printString);
        usbPutString("robot_x:");
        sprintf(printString, "%d\r\n", system_state.robot_xpos);
        usbPutString(printString);
        usbPutString("robot_y:");
        sprintf(printString, "%d\r\n", system_state.robot_ypos);
        usbPutString(printString);
        usbPutString("robot_dir:");
        sprintf(printString, "%d\r\n", system_state.robot_orientation);
        usbPutString(printString);
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

// -------------------------------------------------------------------------------MAIN-----------------------------MAIN---------------------------MAIN  
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
        //ADC_StartConvert();
        
        //start the ADC timer for software trigger mode
        Timer_TS_Start();
        isr_TS_StartEx(isr_adcTimer);
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
    if (USE_USB){    
        USBUART_Start(0,USBUART_5V_OPERATION);
        if (USBUART_GetConfiguration())
            {
                 USBUART_CDC_Init();
            }
    }
    
    if(BIN_ENABLED){
        isrRF_RX_StartEx(rxInt);
        UART_Start();
    }
    
    RF_BT_SELECT_Write(0);

    //usbPutString("Started");
    for(;;)
    {
        /* Place your application code here. */
        if(ENABLE_PWM && ENABLE_CYCLE) cycle_PWM();
        if(ENABLE_ADC) print_ADC();
        if(ENABLE_QUAD) Quad_Dec_response();
        
        if(BIN_ENABLED == 1)
        {
            handle_rx_binary();
            print_RF();
        }
        
        //handle_usb();        
    }   
}
//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')
    if (USE_USB && portOpen)    
    {
            uint32 cnt = 0;
            while (USBUART_CDCIsReady() == 0)
            {
                cnt++;
                if(cnt == 3000000){
                    portOpen = 0;
                    return;
                }
            }
            s[63]='\0';
            s[62]='!';
            USBUART_PutData((uint8*)s,strlen(s));
    }
}
//* ========================================
void usbPutChar(char c)
{
    if (USE_USB && portOpen)    
    {    
        uint32 cnt = 0;
        while (USBUART_CDCIsReady() == 0){
            cnt++;
            if(cnt == 3000000){
                portOpen = 0;
                return;
            }
        }
        USBUART_PutChar(c);
    }    
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

/* [] END OF FILE */

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
#include "pathfinder.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
//void handle_usb();
//* ========================================

#define QUAD_RATIO 0.99556

char instructions[DEFAULT_ARRAY_SIZE] = {0};
uint16 instructionCount = 0;
uint8 sensorsDisabled = 0;

uint8 robot_direction = 4;

uint8 path[DEFAULT_ARRAY_SIZE][3] = {0};
uint8 start[2] = {1, 1};//(y, x) array starts at 0
uint8 destination[2] = {13, 17};//(y, x)


uint8 map[15][19] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
                    {1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
                    {1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
                    {1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1},
                    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
                    {1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
                    {1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1},
                    {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
                    {1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
                    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
                    {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
                    {1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
//first number is the y coord, second is x
//first number is row, second column

//uint8 food_list[6][2]= {{4,5},{7,1},{11,5},{10,11},{5,8},{17,2}};
uint8 food_list[6][2]= {{5,11}, {1, 17}, {13, 1}};
uint8 food_length = 3;

void changeToRF();
void changeToBT();

void handle_rx_binary()
{
    if(flag_rx == 1)
    {    
        flag_rx = 0;
        
        uint16 packet_bytes = (packet[1] << 8) | (packet[0]);
        char byte_packet[12];
        char string_packet[12];
        
        switch(byteCount)
        {
            case 4:
                buffer_state.rssi = packet[0];
                buffer_state.index = packet[1];
            break;
            case 6:
                buffer_state.robot_xpos = packet_bytes;
            break;
            case 8:
                buffer_state.robot_ypos = packet_bytes;
            break;
            case 10:
                buffer_state.robot_orientation = packet_bytes;
            break;
            case 12:
                buffer_state.g0_xpos = packet_bytes;
            break;
            case 14:
                buffer_state.g0_ypos = packet_bytes;
            break;
            case 16:
                buffer_state.g0_speed = packet_bytes;
            break;
            case 18:
                buffer_state.g0_direction = packet_bytes;
            break;
            case 20:
                buffer_state.g1_xpos = packet_bytes;
            break;
            case 22:
                buffer_state.g1_ypos = packet_bytes;
            break;
            case 24:
                buffer_state.g1_speed = packet_bytes;
            break;
            case 26:
                buffer_state.g1_direction = packet_bytes;
            break;
            case 28:
                buffer_state.g2_xpos = packet_bytes;
            break;
            case 30:
                buffer_state.g2_ypos = packet_bytes;
            break;
            case 32:
                buffer_state.g2_speed = packet_bytes;
            break;
            case 34:
                buffer_state.g2_direction = packet_bytes;
            break;
        }
    }
}

void setLeftDir(uint8 dir)
{
    M2_IN2_Write(dir);
}

void setRightDir(uint8 dir)
{
    M1_IN2_Write(dir);
}

void reverseDirection()
{
    direction = !direction;
    setLeftDir(direction);
    setRightDir(direction);
    char mes[16];
     sprintf(mes, "dir: %d\r\n", direction);
    UART_PutString(mes);
}

void setSpeed(double left, double right){
    if(right < 0.0)
    {
        //char mes[16];
       // sprintf(mes, "right dir: %d\r\n", !direction);
       // UART_PutString(mes);
        setRightDir(!direction);
        right = -right;
    }
    else setRightDir(direction);
    
    if(left < 0.0)
    {
       // char mes[16];
        //sprintf(mes, "left dir: %d\r\n", !direction);
        //UART_PutString(mes);
        setLeftDir(!direction);
        left = -left;
    }
    else setLeftDir(direction);
    
    int16 countsLeft = left*QUAD_RATIO;
    int16 countsRight = right*QUAD_RATIO;
    
    leftSpeedLimit = countsRight;
    rightSpeedLimit = countsLeft;
}

void brakeLeft()
{
    PWM_1_WriteCompare(0);
    left_duty_cycle = 0;
}

void brakeRight()
{
     PWM_2_WriteCompare(0);
     right_duty_cycle = 0;
}

void brakeMotor(){
    setSpeed(0, 0);
    brakeLeft();
    brakeRight();
}

void driveForwards()
{
    setSpeed(speed, speed);
}

void turnRight()
{
    setSpeed(0,speed*2.0);
}

void turnLeft()
{
    setSpeed(speed*2.0,0);
}

void turnU()
{
    setSpeed(-speed*2.0,speed*2.0);
}

void initTurnLeft(){
    Timer_2_Stop();
    prev_movement_state = movement_state;
    movement_state = LTURN;
    brakeLeft();
    start_turn_count = QuadDec_M2_GetCounter();
    Timer_2_Start();
}

void initTurnRight(){
    Timer_2_Stop();
    prev_movement_state = movement_state;
    movement_state = RTURN;
    brakeRight();
    start_turn_count = QuadDec_M1_GetCounter();
    Timer_2_Start();
}

void initTurnU(){
    Timer_2_Stop();
    prev_movement_state = movement_state;
    movement_state = UTURN;
    brakeMotor();
    start_turn_count = QuadDec_M1_GetCounter();
    Timer_2_Start();
}

void initForward(){
    brakeMotor();
    movement_state = DRIVE;
}

void initBrake(){
    movement_state = STOPPED;
}

void initTrack()
{
    movement_state = TRACKING;
}

void initTrackU(){
    movement_state = TRACKING_U;
}

void inittrackLineZ(){
    movement_state = TRACKING_SOFT;
}



//Binary RF Data
CY_ISR(rxInt){
    char rf_char = UART_GetChar();
    if(rf_char == SOP){
            //we should evalute whether the last packet was valid by measuring the length of data
            if(byteCount == 34)
            {
                system_state = buffer_state;
                if(initial_pos_valid == 0)
                {
                    LED_Write(~LED_Read());
                    initial_pos_valid = 1;
                }
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

CY_ISR(BT_rxInt)
{
    char rf_char = UART_GetChar();
    switch(rf_char){
    case 'a':
        initTurnLeft();
        track_mode = NO_TRACK;
        break;
    case 'w':
        initForward();
        track_mode = NO_TRACK;
        break;
    case 's': 
        reverseDirection();
        track_mode = NO_TRACK;
        break;
    case 'd':
        initTurnRight();
        track_mode = NO_TRACK;
        break;
    case 'f':
        initBrake();
        track_mode = NO_TRACK;
        break;
    case('t'):
        track_mode = CURVE_TRACK;
        initTrack();
        break;
    case('u'):
        initTrackU();
        track_mode = U_TRACK;
        break;
    case('z'):
        track_mode = SQUARE_TRACK;
        inittrackLineZ();
        break;
    case('q'):
        track_mode = QUAD_STOP;
        accum_dist = 0;
        target_distance_quad = target_distance_cm * quad_per_cm;
        char mes[16];
        sprintf(mes, "target quad: %d\r\n", target_distance_quad);
        UART_PutString(mes);
        initForward();
        break;
    case ('r'):
        track_mode = RF_STOP;
        changeToRF();
        // Make initial position
        initial_pos_valid = 0;
        initBrake();
        break;
    case ('x'):
        track_mode = DEST_TEST;
        tracked_direction = robot_direction;
        generateDirections();
        char message[128];
        sprintf(message, "p:%s\r\n", instructions);
        UART_PutString(message);
        inittrackLineZ();
        break;
    }
}

//BT
CY_ISR(BT_txInt)
{
    
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
    last_quad_count1 = quad_count1;
    last_quad_count2 = quad_count2;
    quad_count1 = QuadDec_M1_GetCounter();
    quad_count2 = QuadDec_M2_GetCounter();
    quad_diff1 = quad_count1 - last_quad_count1;
    quad_diff2 = quad_count2 - last_quad_count2;
    
    if(abs(quad_count1) > 3000 && movement_state != LTURN && movement_state != RTURN && track_mode != QUAD_STOP && movement_state != UTURN)
    {
        QuadDec_M1_SetCounter(0);
        QuadDec_M2_SetCounter(0);
        quad_count1 = 0;
        quad_count2 = 0;
    }

    flag_calc_wheelspeed = 1;
    
    if (track_mode == QUAD_STOP)
    {
        accum_dist += quad_diff1;
        char mes[16];
        sprintf(mes, "dist: %d\r\n", accum_dist);
        UART_PutString(mes);
        if(abs(accum_dist) >= target_distance_quad)
        {
            initBrake();
            track_mode = NO_TRACK;
        }
    } else if (track_mode == RF_STOP)
    { 
        // Do pythag
        double dist = hypot((system_state.robot_xpos - initial_x_pos) / px_per_x_cm , (system_state.robot_ypos - initial_y_pos) / px_per_y_cm);
        if (dist >= target_distance_cm)
        {
            initBrake();
            track_mode = NO_TRACK;
        }
    }
    
}

CY_ISR(isr_turn_timer)
{
    if(movement_state == LTURN)
    {
        if(abs(QuadDec_M2_GetCounter() - start_turn_count) >= 208)
        {
            //movement_state = STOPPED;
            brakeMotor();
            movement_state = prev_movement_state;
            Timer_2_Stop();
        }
    }
    else if (movement_state == RTURN)
    {
        if(abs(QuadDec_M1_GetCounter() - start_turn_count) >= 208)
        {
            //movement_state = STOPPED;
            brakeMotor();
            movement_state = prev_movement_state;
            Timer_2_Stop();
        }
    }
    else if (movement_state == UTURN)
    {
        if(abs(QuadDec_M1_GetCounter() - start_turn_count) >= 208)
        {
            //movement_state = STOPPED;
            brakeMotor();
            movement_state = prev_movement_state;
            Timer_2_Stop();
        }
    }
}


CY_ISR (Stop_on_line)
{
    movement_state = STOPPED;
    if(movement_state != DRIVE) return;
    //initTurnLeft();
}

CY_ISR (button)
{
    if(BT_ENABLED)
    {
        UART_PutString("Starting robot!\r\n");
    }
    movement_state = DRIVE;
}

CY_ISR(isr_adcTimer)
{
    ADC_StartConvert();
}


void changeToRF()
{
        //disable BT
        BT_ENABLED = 0;
        isrRF_RX_Stop();
        UART_Stop();
        
        //enable RF
        BIN_ENABLED = 1;
        UART_clk_SetDividerValue(130);
        isrRF_RX_StartEx(rxInt);
        UART_Start();
        RF_BT_SELECT_Write(0);
}

void changeToBT()
{
        //disable RF
        BIN_ENABLED = 0;
        isrRF_RX_Stop();
        UART_Stop();
        
        //enable BT
        BT_ENABLED = 1;
        UART_clk_SetDividerValue(781);
        isrRF_RX_StartEx(BT_rxInt);
        UART_Start();
        RF_BT_SELECT_Write(1);
}


void Quad_Dec_response()
{
    //Check if the flag has been set
    if (!flag_calc_wheelspeed) return;
    flag_calc_wheelspeed = 0;
    
    //char wheel_1_str [64];
    //char wheel_2_str [64];
    //sprintf(wheel_1_str, "quad count 1 is: %d\n\r", quad_diff1);
    //usbPutString(wheel_1_str);
    //sprintf(wheel_2_str, "quad count 2 is: %d\n\r", quad_diff2);
    
    //usbPutString(wheel_2_str);
    
    int16 leftSpeed = quad_diff1;
    int16 rightSpeed = quad_diff2;
    double scalingLeft = 1;
    double scalingRight = 1;
    
    //there's an initial right tilt by default, so we want to decrease the initial left speed
    if(leftSpeed == 0 && rightSpeed == 0){ 
       //leftSpeed = 3;
        scalingLeft = 8;
        scalingRight = 8;
    }

    int interCalc = leftSpeedLimit - abs(leftSpeed);
    int nextSpeed = (abs(interCalc) / interCalc) * sqrt(abs((int)(interCalc)));
    left_duty_cycle = left_duty_cycle + scalingLeft*nextSpeed;
    interCalc = rightSpeedLimit - abs(rightSpeed);
    nextSpeed = (abs(interCalc) / interCalc) * sqrt(abs(interCalc));
    right_duty_cycle = right_duty_cycle + scalingRight*nextSpeed;
    
    if(right_duty_cycle < 0) right_duty_cycle = 0;
    if(left_duty_cycle < 0) left_duty_cycle = 0;
    if(right_duty_cycle > 100) right_duty_cycle = 100;
    if(left_duty_cycle > 100) left_duty_cycle = 100;
    PWM_1_WriteCompare(left_duty_cycle);
    PWM_2_WriteCompare(right_duty_cycle);
}

void trackLine()
{
    //read the value of the three central-front sensors
    
    uint8 nl = NLSens_out_Read();
    uint8 nr = NRSens_out_Read();
    uint8 mid = MSens_out_Read();
    //if only the left one, hard left
    if(nl && !nr && !mid) //if only the left one, hard left
    {
        setSpeed(speed / 1.5, -speed / 1.5);
    }
    else if(nl && mid && !nr)   //if centre/middle, soft left
    {
        setSpeed(speed, 0);
    }
    else if (nr && mid && !nl)//if centre/right, soft right
    {
        setSpeed(0, speed);
    }
   else if (nr && !mid && !nl)    //if only right, hard right
    {
        setSpeed(-speed / 1.5,speed / 1.5);
    }
    else if (mid && !nr && !nl)
    {
        setSpeed(speed,speed);
    }
   // else if (!mid && !nr && !nl)
    //{
        //setSpeed(0,0);
    //}
}

void trackLineZ()
{
    //read the value of the three central-front sensors
    
    uint8 nl = NLSens_out_Read();
    uint8 nr = NRSens_out_Read();
    uint8 mid = MSens_out_Read();
    
    //if only the left one, hard left
    if(nl && !nr && !mid)// && trackTurnCount > 0)
    {
        setSpeed(speed, -speed);
    }
    else if(nl && mid && !nr)   //if centre/middle, soft left
    {
        //setSpeed(speed,speed / 1.5);
        //setSpeed(speed, -speed);
    }
    else if (nr && mid && !nl)//if centre/right, soft right
    {
       // setSpeed(speed / 1.5,speed);
        //setSpeed(-speed,speed);
    }
   else if (nr && !mid && !nl)    //if only right, hard right
    {
        setSpeed(-speed,speed);
    }
    else if (mid && !nr && !nl)
    {
        setSpeed(speed,speed);
    }
    //else setSpeed(speed, speed);
  
   // else if (!mid && !nr && !nl)
    //{
        //setSpeed(0,0);
    //}
}

void trackLineU()
{
    //read the value of the three central-front sensors
    
    uint8 nl = NLSens_out_Read();
    uint8 fl = FLSens_out_Read();
    uint8 nr = NRSens_out_Read();
    uint8 fr = FRSens_out_Read();
    uint8 mid = MSens_out_Read();
    if (fl && mid && fr) // T intersection
    {
        // not implemented
    }
    else if (fl && mid) // if far left + centre, we're at a left-turning intersection
    {
        setSpeed(speed, speed);
    }
    else if (fr && mid) // if far right + centre, we're at a right-turning intersection
    {
        setSpeed(speed, speed);
    }
    else if(nl && !nr && !mid) //if only the left one, hard left
    {
         setSpeed(speed / 1.5,-speed / 1.5);
    }
    else if(nl && mid && !nr)   //if centre/middle, soft left
    {
        setSpeed(speed, 0);
    }
    else if (nr && mid && !nl)//if centre/right, soft right
    {
        setSpeed(0, speed);
    }
   else if (nr && !mid && !nl)    //if only right, hard right
    {
         setSpeed(-speed / 1.5,speed / 1.5);
    }
    else if (mid && !nr && !nl)
    {
        setSpeed(speed,speed);
    }
   // else if (!mid && !nr && !nl)
    //{
        //setSpeed(0,0);
    //}
   

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

void readFrontSensors(uint8 sensorVals[5])
{
    sensorVals[0] = FLSens_out_Read();
    sensorVals[1] = NLSens_out_Read();
    sensorVals[2] = MSens_out_Read();
    sensorVals[3] = NRSens_out_Read();
    sensorVals[4] = FRSens_out_Read();
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
        isr_turn_count_StartEx(isr_turn_timer);
        
        Timer_1_Start();
    }
    
    if(ENABLE_STOP){
        isr_OnLine_StartEx(Stop_on_line);
        
    }
    isr_button_StartEx(button);
    

    // ------USB SETUP ----------------    
    if (USE_USB){    
        USBUART_Start(0,USBUART_5V_OPERATION);
        if (USBUART_GetConfiguration())
            {
                 USBUART_CDC_Init();
            }
    }
    
    if(BIN_ENABLED){
        changeToRF();
    }
    
    if(BT_ENABLED){
        changeToBT();
    }
    
    //usbPutString("Started");
    for(;;)
    {
        if(ENABLE_ADC) print_ADC();
        if(ENABLE_QUAD) Quad_Dec_response();
        if(BIN_ENABLED == 1)
        {
            handle_rx_binary();
            print_RF();
        }
        // NO_TRACK, CURVE_TRACK, U_TRACK, SQUARE_TRACK
        
        uint8 frontSensors[5];
        readFrontSensors(frontSensors);
        
        switch(track_mode)
        {
            case SQUARE_TRACK:
                if(movement_state != LTURN && movement_state != RTURN)
                {
                    if(frontSensors[0] == 1 && frontSensors[2] == 1){ //left turn
                        initTurnLeft();
                    }
                    else if (frontSensors[4] == 1 && frontSensors[2] == 1) //right turn
                    {
                        initTurnRight();
                    }
                    else inittrackLineZ();
                }
            break;
            case NO_TRACK:
            break;
            case CURVE_TRACK:
            break;
            case U_TRACK:
            break;
            case QUAD_STOP:
            break;
            case RF_STOP:
                if(initial_pos_valid == 1)
                {
                    //changeToBT();
                   // UART_PutString("Valid RF detected!");
                    //changeToRF();
                    initial_x_pos = system_state.robot_xpos;
                    initial_y_pos = system_state.robot_ypos;
                    initial_pos_valid = 2;
                    initForward();
                }
            break;
            case DEST_TEST:
                if(movement_state != LTURN && movement_state != RTURN && movement_state != UTURN){
                    //when we hit an intersection, verify the next step then evaluate
                    char nextStep = instructions[instructionCount];
                    if(((frontSensors[0] == 1 && frontSensors[2] == 1) || (frontSensors[4] == 1 && frontSensors[2] == 1))){ //intersection
                        if(sensorsDisabled == 0)
                        {
                            sensorsDisabled = 1;
                            switch(nextStep)
                            {
                                case 'S':
                                    initTrackU();
                                    //do nothing
                                break;
                                case 'L':
                                    //if(tracked_direction == 1) tracked_direction = 4; else tracked_direction--;
                                    initTurnLeft();
                                break;
                                case 'R':
                                    //if(tracked_direction == 4) tracked_direction = 1; else tracked_direction++;
                                    initTurnRight();
                                    
                                break;
                                case 'U':
                                    // Direction not tracked any more
                                    initTurnU();
                                break;
                                default:
                                    //do nothing
                                    break;
                            }
                            instructionCount++;
                        }
                    }
                    else if (frontSensors[0] == 0 && frontSensors[1] == 0 && frontSensors[2] == 0 && frontSensors[3] == 0 && frontSensors[4] == 0 && nextStep == 'U')
                    {
                        if(sensorsDisabled == 0)
                        {
                            sensorsDisabled = 1;
                            initTurnU();
                            instructionCount++;
                        }
                    }
                    else
                    {
                        inittrackLineZ();
                        sensorsDisabled = 0;
                    }
                }
                break;
        }
        
        switch(movement_state)
        {
            case DRIVE:
                driveForwards();
            break;
            case LTURN:
                turnLeft();
            break;
            case RTURN:
                turnRight();
            break;
            case UTURN:
                turnU();
            break;
            case STOPPED:
                brakeMotor();
            break;
            case TRACKING:
                trackLine();
            break;
            case TRACKING_U:
                trackLineU();
            break;
            case TRACKING_SOFT:
                trackLineZ();
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

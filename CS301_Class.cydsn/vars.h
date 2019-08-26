/* ========================================
 *
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include "defines.h"
//* ========================================
uint8 ts = 0;
uint16 ts_enc = 0;
uint16 ts_update = 0;
uint16 ts_speed = 0;
uint16 ts_display = 0;

uint8 flag_ts_enc = 0;
uint8 flag_ts_update = 0;
uint8 flag_ts_speed = 0;
uint8 flag_ts_display = 0;


uint8 flag_rx = 0;
uint8 flag_packet = 0;
uint8 flag_KB_string = 0;

uint8 dataready_flag =0;

uint8 flag_rf_transmission_active = UNKNOWN; // [TRUE if receieving data, FALSE is not, UNKNOWN at startup]
uint8 flag_print_rf = 0;

uint8 flag_receive_ADC = 0;
int16 adc_result;

uint8 direction = 0;

//==========================================
// Quad decoder
uint8 flag_calc_wheelspeed = 0;
int16 quad_count1 = 0;
int16 quad_count2 = 0;

int16 left_duty_cycle = 0;
int16 right_duty_cycle = 0;

//Motor controll================
int16 leftSpeedLimit = 0;
int16 rightSpeedLimit = 0;

// Flags =======================
uint8 brakeFlag;
uint8 portOpen = 1;

//Voltage measurements
int16 prevVoltage;
int16 prevVoltage2;

//* ========================================
char displaystring[BUF_SIZE] = "CS301 2016\n";
char line[BUF_SIZE], entry[BUF_SIZE];
uint8 usbBuffer[BUF_SIZE];
//* ========================================
typedef struct data_main {
	int8            rssi;	
    uint8           index;			// index number of packet. incremented number
	int16			robot_xpos;	 	// 
	int16			robot_ypos;		//
    int16         robot_orientation;
	int16			g0_xpos;		//
	int16			g0_ypos;		//
	int16			g0_speed;		//
	int16		g0_direction;	//
	int16			g1_xpos;		//
	int16			g1_ypos;		//
	int16			g1_speed;		//
    int16		g1_direction;	//
    int16			g2_xpos;		//
    int16			g2_ypos;		//
    int16			g2_speed;		//
    int16		g2_direction;	//
} vtype1;    
struct data_main buffer_state;
struct data_main system_state;

uint8 byteCount = 0;
char packet[2];
//* ========================================


//* ========================================
/* [] END OF FILE */

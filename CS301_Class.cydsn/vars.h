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

//BT/RF control
uint8 BIN_ENABLED = 0;
//BLE
uint8 BT_ENABLED = 1;


//==========================================
// Quad decoder
uint8 flag_calc_wheelspeed = 0;
int16 quad_count1 = 0;
int16 quad_count2 = 0;
int16 last_quad_count1 = 0;
int16 last_quad_count2 = 0;
int16 quad_diff1 = 0;
int16 quad_diff2 = 0;

//turning
int16 start_turn_count = 0;
//

int16 left_duty_cycle = 0;
int16 right_duty_cycle = 0;

//Motor controll================
int16 leftSpeedLimit = 0;
int16 rightSpeedLimit = 0;


int16 target_distance_cm = 100;
//quadrature decoder distance stopping
int16 accum_dist = 0;
int16 target_distance_quad = 0;
float quad_per_cm = 11.166;

//RF distance stopping
uint8 initial_pos_valid = 0;
int16 initial_x_pos = 0;
int16 initial_y_pos = 0;

// Flags =======================
uint8 brakeFlag;
uint8 portOpen = 1;

//Voltage measurements
int16 prevVoltage;
int16 prevVoltage2;

//pathfinding
char instructions[] = {'R','L','S','S','R','L','R','L','R',0};
uint16 instructionCount = 0;
uint8 sensorsDisabled = 0;

//concept of robot state
enum state {DRIVE = 0, LTURN, RTURN, STOPPED, TRACKING, TRACKING_U, TRACKING_SOFT}; 
enum mode {NO_TRACK, CURVE_TRACK, U_TRACK, SQUARE_TRACK, QUAD_STOP, RF_STOP, DEST_TEST};
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

enum state prev_movement_state = STOPPED;
enum state movement_state = STOPPED;
enum mode track_mode = NO_TRACK;

uint8 byteCount = 0;
char packet[2];
//* ========================================

//double speed = 16; // the speed of the robot in cm/s
double speed = 16;

//* ========================================
/* [] END OF FILE */

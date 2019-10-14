/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <project.h>

#define Y_SIZE 15
#define X_SIZE 19

#define DEFAULT_ARRAY_SIZE 800


//pathfinding
extern uint16 instructionCount;
extern uint8 sensorsDisabled;

extern uint8 map[15][19];

extern uint8 food_list[6][2];
extern uint8 path[DEFAULT_ARRAY_SIZE][3];
extern uint8 start[2];//(y, x) array starts at 0
extern uint8 destination[2];//(y, x)
extern uint8 robot_direction;
uint8 tracked_direction; 
extern uint8 food_length;
extern char instructions[DEFAULT_ARRAY_SIZE];

int generateDirections();
uint8 djikstras(uint8 map[Y_SIZE][X_SIZE], uint8 food_list[6][2], uint8 path[DEFAULT_ARRAY_SIZE][3], uint8 start[], uint8 destination[]);

/* [] END OF FILE */

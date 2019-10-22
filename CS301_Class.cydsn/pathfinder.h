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
extern uint32_t sensorsDisabled;

extern uint32_t map[15][19];

extern uint32_t food_list[6][2];
extern uint32_t path[DEFAULT_ARRAY_SIZE][3];
extern uint32_t start[2];//(y, x) array starts at 0
extern uint32_t destination[2];//(y, x)
extern uint32_t robot_direction;
uint32_t tracked_direction; 
extern uint32_t food_length;
extern char instructions[DEFAULT_ARRAY_SIZE];

uint32_t generateDirections();
uint32_t generateEntireMapDirections();
uint32_t djikstras(uint32_t map[Y_SIZE][X_SIZE], uint32_t food_list[6][2], uint32_t path[DEFAULT_ARRAY_SIZE][3], uint32_t start[], uint32_t destination[]);

/* [] END OF FILE */

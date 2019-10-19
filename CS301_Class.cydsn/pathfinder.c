#include "pathfinder.h"
//define the variables
#define VALUE_OF_FOOD 0 //penalty for going over food pellets.
#define DEFAULT_NODE_COST 10 //the cost of moving to a normal node.
#define CORNER_PENALTY 0 //penalty for changing direction.
#define PATH 0 //idicates weather the path is the 1s or the 0s.



#define STRAIGHT 'S'
#define LEFT 'L'
#define RIGHT 'R'
#define UTURN 'U'
#define DRIVE 'D'

#define INF_16 65535

#define VISITED 1
#define UNVISITED 0

#define X 1
#define Y 0
#define DIR 2

//struct for nodes
typedef struct node{
   uint32_t path;// 1
   uint32_t visited;// 2
   uint16 cost;// 6
   uint32_t x;
   uint32_t y;
   struct node* prevNode;
   //uint32_t previous_y;// 4
   //uint32_t previous_x; // 5
   uint16 tentative_cost; // 3
   uint32_t direction;
} node;

/**pathfinding algorithm
* returns the length of the path array 0 if no path is found
* map - map to be searched through (needs size)
* food_list - list of food (needs size)
* path - will be filled with the path found by the algorithm
* start - is the start node duh
* destination - end node
* direction - the initial direction of the robot
*/
uint32_t djikstras(uint32_t map[Y_SIZE][X_SIZE], uint32_t food_list[6][2], uint32_t path[DEFAULT_ARRAY_SIZE][3], uint32_t start[], uint32_t destination[]){
   node Nodes[Y_SIZE][X_SIZE];
   //fill up the default information for each node
    uint32_t i;
   for(i = 0; i < Y_SIZE; i++){
      uint32_t j;
      for(j = 0; j < X_SIZE; j++){
            Nodes[i][j].path = map[i][j];//map information
            //printf("%d\n", map[i][j]);
            Nodes[i][j].visited = UNVISITED; //set all unvisited
            Nodes[i][j].cost = DEFAULT_NODE_COST; // seet the cost of going to this node to the default cost of each node
            Nodes[i][j].y = i;
            Nodes[i][j].x = j;
            Nodes[i][j].prevNode = 0;
            Nodes[i][j].tentative_cost = INF_16;// set the current cost to infinity
            Nodes[i][j].direction = 0;
      }
   }


   uint32_t current[2];
   //memcpy(current, start, sizeof(current));//because nothing works in c the way you want it to
   current[Y] = start[Y];
   current[X] = start[X];
   uint32_t totalIterationCounter = 0;
   uint32_t nextNodes[DEFAULT_ARRAY_SIZE][2] = {0};
   //uint32_t nextNodesDirection[DEFAULT_ARRAY_SIZE] = {0};
   uint32_t tentativeNode[2] = {0};//x and y coordinate of the next node
   uint32_t unreachable = 0;
   uint32_t corner_penalty = 0;
   uint32_t counter = 0;
   uint16 tmpCost = 0;
   uint32_t nextNode[2] = {0, 0};
   uint32_t nextNodeIndex = 0;
   uint32_t tmpNextNode[2] = {0};
   uint16 nextNodeCost = 0;
   uint32_t hasNext = 1;

   Nodes[current[Y]][current[X]].tentative_cost = 0;
   Nodes[current[Y]][current[X]].prevNode = &Nodes[current[Y]][current[X]];
   Nodes[current[Y]][current[X]].direction = robot_direction;

   //early exit, run until x and y are equal
   while(!((current[Y] == destination[Y]) && (current[X] == destination[X])) && hasNext == 1){
      counter = 1;
      Nodes[current[Y]][current[1]].visited = VISITED; // set visitetd to true
      //printf("main loop %d | X: %d | Y: %d\n", Nodes[current[0]][current[1]].visited, Nodes[current[0]][current[1]].tentative_cost, hasNext);
      while(counter <= 4){
         corner_penalty = 0;
         if(counter == 1){
            tentativeNode[Y] = current[Y] - 1;
            tentativeNode[X] = current[X];
         }else if(counter == 2){
            tentativeNode[Y] = current[Y];
            tentativeNode[X] = current[X] + 1;
         }else if(counter == 3){
            tentativeNode[Y] = current[Y] + 1;
            tentativeNode[X] = current[X];
         }else if(counter == 4){
            tentativeNode[Y] = current[Y];
            tentativeNode[X] = current[X] - 1;
         }
         if(counter != robot_direction){
            corner_penalty = CORNER_PENALTY;
         }

         if(tentativeNode[Y] >= 0 && tentativeNode[X] >= 0 && tentativeNode[Y] <= Y_SIZE && tentativeNode[X] <= X_SIZE){//check that the tentativeNode is on the map
            if(Nodes[tentativeNode[Y]][tentativeNode[X]].path == PATH){//check the node is a path
               //printf("3\n", hasNext);
               tmpCost = Nodes[current[Y]][current[X]].tentative_cost + Nodes[tentativeNode[Y]][tentativeNode[X]].cost + corner_penalty;
               if(tmpCost < Nodes[tentativeNode[Y]][tentativeNode[X]].tentative_cost){
                  //printf("5 %d\n", tmpCost);
                  Nodes[tentativeNode[Y]][tentativeNode[X]].tentative_cost = tmpCost;
                  //printf("6 currentX : %d, currentY : %d\n", current[0], current[1]);

                  //printf("Discovered node at X : %d, Y : %d\n", tentativeNode[0], tentativeNode[1]);
                  Nodes[tentativeNode[Y]][tentativeNode[X]].prevNode = &Nodes[current[Y]][current[1]];
                  nextNodes[totalIterationCounter][Y] = tentativeNode[Y];
                  nextNodes[totalIterationCounter][X] = tentativeNode[X];
                  Nodes[tentativeNode[Y]][tentativeNode[X]].direction = counter;
                  //nextNodesDirection[totalIterationCounter] = counter;
                  totalIterationCounter = 1 + totalIterationCounter;
               }
            }
         }
         counter++;
      }
      //set the default cost value so that the for loop will find the lowest unvisited node
      nextNodeCost = INF_16;
      //find the lowest unvisited node
      hasNext = 0;

      //find the next node to visit
      //printf("totalIterationCounter : %d\n", totalIterationCounter);
        int i;
      for(i = 0; i < totalIterationCounter; i++){
         //printf("i : %d\n", i);
         tmpNextNode[Y] = nextNodes[i][Y];
         tmpNextNode[X] = nextNodes[i][X];
         //printf("tentative_cost : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].tentative_cost);
         if(Nodes[nextNodes[i][Y]][nextNodes[i][X]].tentative_cost < nextNodeCost){
            //printf("1 : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].tentative_cost);
            if(Nodes[nextNodes[i][Y]][nextNodes[i][X]].visited == UNVISITED){

               //printf("2 : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].visited);
               nextNodeCost = Nodes[nextNodes[i][Y]][nextNodes[i][X]].tentative_cost;

               nextNodeIndex = i;
               hasNext = 1;
            }
         }
      }
      //printf("has next %d\n", hasNext);
      current[Y] = nextNodes[nextNodeIndex][Y];
      current[X] = nextNodes[nextNodeIndex][X];
      robot_direction = Nodes[current[Y]][current[X]].direction;

   }

   counter = 0;
   //printf("Node %d | X: %d | Y: %d\n", counter, current[0], current[1]);
   if((current[Y] == destination[Y]) && (current[X] == destination[X])){
      //printf("1 : startX: %d, startY: %d\n", start[0], start[1]);
      node* currentNode = &(Nodes[current[Y]][current[X]]);
      while(!((currentNode->y == start[Y]) && (currentNode->x == start[X]))){
         //printf("1 : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].tentative_cost);
         path[counter][Y] = currentNode->y;
         path[counter][X] = currentNode->x;
         path[counter][DIR] = Nodes[currentNode->y][currentNode->x].direction;
         //printf("direction2 %d\n", path[0][DIR]);
         currentNode = currentNode->prevNode;

         counter++;
      }
      path[counter][Y] = currentNode->y;
      path[counter][X] = currentNode->x;
      path[counter][DIR] = Nodes[currentNode->y][currentNode->x].direction;
      return counter;
   }else{
      return 0;
   }

   //return 0;
}


uint32_t DepthFirst(uint32_t map[Y_SIZE][X_SIZE], uint32_t food_list[6][2], uint32_t path[DEFAULT_ARRAY_SIZE][3], uint32_t start[], uint32_t destination[], uint32_t direction){
   //printf("Finding path\n");
   node Nodes[Y_SIZE][X_SIZE];
   //fill up the default information for each node
   uint32_t i, j;
   for(i = 0; i < Y_SIZE; i++){
      for(j = 0; j < X_SIZE; j++){
            Nodes[i][j].path = map[i][j];//map information
            //printf("%d\n", map[i][j]);
            Nodes[i][j].visited = UNVISITED; //set all unvisited
            Nodes[i][j].cost = DEFAULT_NODE_COST; // seet the cost of going to this node to the default cost of each node
            Nodes[i][j].y = i;
            Nodes[i][j].x = j;
            Nodes[i][j].prevNode = 0;
            Nodes[i][j].tentative_cost = 0;// set the current cost to infinity
            Nodes[i][j].direction = 0;
      }
   }


   uint32_t current[2];
   //memcpy(current, start, sizeof(current));//because nothing works in c the way you want it to
   current[Y] = start[Y];
   current[X] = start[X];
   uint32_t totalIterationCounter = 0;
   uint32_t nextNodes[DEFAULT_ARRAY_SIZE][2] = {0};
   //uint32_t nextNodesDirection[DEFAULT_ARRAY_SIZE] = {0};
   uint32_t tentativeNode[2] = {0};//x and y coordinate of the next node
   uint32_t unreachable = 0;
   uint32_t corner_penalty = 0;
   uint32_t counter = 0;
   uint16 tmpCost = 0;
   uint32_t nextNode[2] = {0, 0};
   uint32_t nextNodeIndex = 0;
   uint32_t tmpNextNode[2] = {0};
   uint32_t nextNodeCost = 0;
   uint32_t hasNext = 1;

   //set the initial variables
   Nodes[current[Y]][current[X]].tentative_cost = 0;
   Nodes[current[Y]][current[X]].prevNode = &Nodes[current[Y]][current[X]];
   Nodes[current[Y]][current[X]].direction = direction;//TODO: changed
   int path_couter = 0;

   //early exit, run until x and y are equal
   while(hasNext == 1){
      counter = 1;
      Nodes[current[Y]][current[1]].visited = VISITED; // set visited to true
      //printf("main loop %d | X: %d | Y: %d\n", Nodes[current[0]][current[1]].visited, Nodes[current[0]][current[1]].tentative_cost, hasNext);
      while(counter <= 4){
         corner_penalty = 0;
         if(counter == 1){
            tentativeNode[Y] = current[Y] - 1;
            tentativeNode[X] = current[X];
         }else if(counter == 2){
            tentativeNode[Y] = current[Y];
            tentativeNode[X] = current[X] + 1;
         }else if(counter == 3){
            tentativeNode[Y] = current[Y] + 1;
            tentativeNode[X] = current[X];
         }else if(counter == 4){
            tentativeNode[Y] = current[Y];
            tentativeNode[X] = current[X] - 1;
         }
         if(counter != direction){
            corner_penalty = CORNER_PENALTY;
         }

         if(tentativeNode[Y] >= 0 && tentativeNode[X] >= 0 && tentativeNode[Y] <= Y_SIZE && tentativeNode[X] <= X_SIZE){//check that the tentativeNode is on the map
            if(Nodes[tentativeNode[Y]][tentativeNode[X]].path == PATH){//check the node is a path
               //printf("3\n", hasNext);
               tmpCost = Nodes[current[Y]][current[X]].tentative_cost + Nodes[tentativeNode[Y]][tentativeNode[X]].cost + corner_penalty;
               if(tmpCost > Nodes[tentativeNode[Y]][tentativeNode[X]].tentative_cost){
                  //printf("5 %d\n", tmpCost);
                  Nodes[tentativeNode[Y]][tentativeNode[X]].tentative_cost = tmpCost;
                  //printf("6 currentX : %d, currentY : %d\n", current[0], current[1]);

                  //printf("Discovered node at X : %d, Y : %d\n", tentativeNode[0], tentativeNode[1]);
                  Nodes[tentativeNode[Y]][tentativeNode[X]].prevNode = &Nodes[current[Y]][current[1]];
                  nextNodes[totalIterationCounter][Y] = tentativeNode[Y];
                  nextNodes[totalIterationCounter][X] = tentativeNode[X];
                  Nodes[tentativeNode[Y]][tentativeNode[X]].direction = counter;
                  //nextNodesDirection[totalIterationCounter] = counter;
                  totalIterationCounter = 1 + totalIterationCounter;
               }
            }
         }
         counter++;
      }
      //set the default cost value so that the for loop will find the lowest unvisited node
      nextNodeCost = 0;
      //find the lowest unvisited node
      hasNext = 0;

      //find the next node to visit
      //printf("totalIterationCounter : %d\n", totalIterationCounter);
        int i;
      for(i = 0; i < totalIterationCounter; i++){
         //printf("i : %d\n", i);
         tmpNextNode[Y] = nextNodes[i][Y];
         tmpNextNode[X] = nextNodes[i][X];
         //printf("tentative_cost : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].tentative_cost);
         if(Nodes[nextNodes[i][Y]][nextNodes[i][X]].tentative_cost > nextNodeCost){
            //printf("1 : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].tentative_cost);
            if(Nodes[nextNodes[i][Y]][nextNodes[i][X]].visited == UNVISITED){


               //printf("2 : %d\n", Nodes[nextNodes[i][0]][nextNodes[i][1]].visited);
               nextNodeCost = Nodes[nextNodes[i][Y]][nextNodes[i][X]].tentative_cost;

               nextNodeIndex = i;
               hasNext = 1;
            }
         }
      }
      //printf("has next %d\n", hasNext);
      current[Y] = nextNodes[nextNodeIndex][Y];
      current[X] = nextNodes[nextNodeIndex][X];
      direction = Nodes[current[Y]][current[X]].direction;

      //printf("%d %d;", current[Y] + 1, current[X] + 1);

      //generate the path
      path[path_couter][Y] = current[Y];
      path[path_couter][X] = current[X];
      path[path_couter][DIR] = Nodes[current[Y]][current[X]].direction;
      path_couter++;
      //printf("tent_cost : %d || NODE(%d, %d) || visited: %d\n", Nodes[current[Y]][current[X]].tentative_cost, current[Y], current[X], Nodes[current[Y]][current[X]].visited);

   }

   return path_couter;
}

uint32_t generateEntireMapDirections(){
    int end = DepthFirst(map, food_list, path, start, destination, robot_direction);

   /*
   printf("hello\n");
   printf("end value : %d\n", end);
   printf("[");
   for(int i = 0; i <end; i++){
      printf("%d  %d;", path[i][Y] + 1, path[i][X] + 1);
   }
   printf("]\n");
   */

   uint16 counter = 0;
   //printf("here\n");
   //start from the end since that's the way the path has been stored in the the array
   //U/D stands for up down intersection L/R stands for left right internsection
    int i;
   for(i = 0; i < end; i++){
      //printf("%d %d;", path[i][Y] + 1, path[i][X] + 1);
      //if next direction is not possible from current direction then find the inter path (down, up, left, right)
      if(!((path[i + 1][Y] == path[i][Y] + 1 && path[i + 1][X] == path[i][X]) || (path[i + 1][Y] == path[i][Y] - 1 && path[i + 1][X] == path[i][X]) || (path[i + 1][X] == path[i][X] - 1 && path[i + 1][Y] == path[i][Y]) || (path[i + 1][X] == path[i][X] + 1 && path[i + 1][Y] == path[i][Y]))){
         uint32_t inter_path[DEFAULT_ARRAY_SIZE][3] = {0};
         uint32_t inter_start[2] = {path[i][Y], path[i][X]};//(y, x) array starts at 0
         uint32_t inter_destination[2] = {path[i + 1][Y], path[i + 1][X]};//(y, x)
            
        //change the global direction
        robot_direction = path[i][DIR];
         int inter_end = djikstras(map, food_list, inter_path, inter_start, inter_destination);

         /*
         printf("\nDiscontinuity found path:\n");
         printf("end value : %d\n", inter_end);
         printf("[");
         for(int tmpI = inter_end; tmpI >=0; tmpI--){//TODO: do you include the final value j>=1 or j>=0
            printf("%d  %d;", inter_path[tmpI][Y] + 1, inter_path[tmpI][X] + 1);
         }
         printf("]\n");
         */

         //stuff
         int j;
         for(j = inter_end; j >= 1; j--){//TODO: do you include the final value j>=1 or j>=0
            //printf("%d %d;", inter_path[j][Y] + 1, inter_path[j][X] + 1);
            if(inter_path[j][DIR] == 1 || inter_path[j][DIR] == 3){
                       //There should be a check that it is within the map
                       if(map[inter_path[j][Y]][inter_path[j][X] - 1] == PATH || map[inter_path[j][Y]][inter_path[j][X] + 1] == PATH){
                          if(inter_path[j][DIR] != inter_path[j - 1][DIR]){
                             //current direction , the next direction
                             if((inter_path[j][DIR] == 1 && inter_path[j - 1][DIR] == 4) || (inter_path[j][DIR] == 3 && inter_path[j - 1][DIR] == 2) || (((inter_path[j][DIR] == 1 && path[i + 1][DIR] == 4) || (inter_path[j][DIR] == 3 && path[i + 1][DIR] == 2)) && j == 1)){//changed
                                //printf("L/R intersection found (%d) [direction = %d] -- TURN LEFT\n", end - j + 1, inter_path[j][DIR]);
                                instructions[counter] = LEFT;
                                counter++;
                             }else if((inter_path[j][DIR] == 1 && inter_path[j - 1][DIR] == 2) || (inter_path[j][DIR] == 3 && inter_path[j - 1][DIR] == 4) || (((inter_path[j][DIR] == 1 && path[i + 1][DIR] == 2) || (inter_path[j][DIR] == 3 && path[i + 1][DIR] == 4)) && j == 1)){//changed
                                //printf("L/R intersection found (%d) [direction = %d] -- TURN RIGHT\n", end - j + 1, inter_path[j][DIR]);
                                instructions[counter] = RIGHT;
                                counter++;
                             }else if ((inter_path[j][DIR] == 1 && inter_path[j - 1][DIR] == 3) || (inter_path[j][DIR] == 3 && inter_path[j - 1][DIR] == 1) || (((inter_path[j][DIR] == 1 && path[i + 1][DIR] == 3) || (inter_path[j][DIR] == 3 && path[i + 1][DIR] == 1)) && j == 1)){//changed
                                //printf("L/R intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - j + 1, inter_path[j][DIR]);
                                instructions[counter] = UTURN;
                                counter++;
                             }else{
                                //printf("Prev %d, current %d\n",inter_path[j - 1][DIR], inter_path[j][DIR]);
                             }
                          }else{
                             //printf("L/R intersection found (%d) [direction = %d]\n", end - j + 1, inter_path[j][DIR]);
                             instructions[counter] = STRAIGHT;
                             counter++;
                          }
                       }else{//not an intersection
                          if ((inter_path[j][DIR] == 1 && inter_path[j - 1][DIR] == 3) || (inter_path[j][DIR] == 3 && inter_path[j - 1][DIR] == 1) || (((inter_path[j][DIR] == 1 && path[i + 1][DIR] == 3) || (inter_path[j][DIR] == 3 && path[i + 1][DIR] == 1)) && j == 1)){//changed
                             //printf("L/R intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - j + 1, inter_path[j][DIR]);
                             instructions[counter] = UTURN;
                             counter++;
                          }else{
                          //printf("[(%d), direction = %d]\n", end - j + 1, inter_path[j][DIR]);
                       }
                       }
                    }else{
                       if(map[inter_path[j][Y] - 1][inter_path[j][X]] == PATH || map[inter_path[j][Y] + 1][inter_path[j][X]] == PATH){
                          if(inter_path[j][DIR] != inter_path[j - 1][DIR]){
                             if((inter_path[j][DIR] == 4 && inter_path[j - 1][DIR] == 3) || (inter_path[j][DIR] == 2 && inter_path[j - 1][DIR] == 1) || (((inter_path[j][DIR] == 4 && path[i + 1][DIR] == 3) || (inter_path[j][DIR] == 2 && path[i + 1][DIR] == 1)) && j == 1)){//changed
                                //printf("U/D intersection found (%d) [direction = %d] -- TURN LEFT\n", end - j + 1, inter_path[j][DIR]);
                                instructions[counter] = LEFT;
                                counter++;
                             }else if((inter_path[j][DIR] == 4 && inter_path[j - 1][DIR] == 1) || (inter_path[j][DIR] == 2 && inter_path[j - 1][DIR] == 3) || (((inter_path[j][DIR] == 4 && path[i + 1][DIR] == 1) || (inter_path[j][DIR] == 2 && path[i + 1][DIR] == 3)) && j == 1)){//changed
                                //printf("U/D intersection found (%d) [direction = %d] -- TURN RIGHT\n", end - j + 1, inter_path[j][DIR]);
                                instructions[counter] = RIGHT;
                                counter++;
                             }else if ((inter_path[j][DIR] == 4 && inter_path[j - 1][DIR] == 2) || (inter_path[j][DIR] == 2 && inter_path[j - 1][DIR] == 4) || (((inter_path[j][DIR] == 4 && path[i + 1][DIR] == 2) || (inter_path[j][DIR] == 2 && path[i + 1][DIR] == 4)) && j == 1)){//changed
                                //printf("U/D intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - j + 1, inter_path[j][DIR]);
                                instructions[counter] = UTURN;
                                counter++;
                             }else{
                                //printf("Prev %d, current %d\n", inter_path[j - 1][DIR], inter_path[j][DIR]);
                             }
                          }else{
                             //printf("U/D intersection found (%d) [direction = %d]\n", end - j + 1, inter_path[j][DIR]);
                             instructions[counter] = STRAIGHT;
                             counter++;
                          }

                       }else{
                          if ((inter_path[j][DIR] == 4 && inter_path[j - 1][DIR] == 2) || (inter_path[j][DIR] == 2 && inter_path[j - 1][DIR] == 4) || (((inter_path[j][DIR] == 4 && path[i + 1][DIR] == 2) || (inter_path[j][DIR] == 2 && path[i + 1][DIR] == 4)) && j == 1)){//changed
                             //printf("U/D intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - j + 1, inter_path[j][DIR]);
                             instructions[counter] = UTURN;
                             counter++;
                          }else{
                          //printf("[(%d), direction = %d]\n", end - j + 1, inter_path[j][DIR]);
                       }
                       }
                    }
         }

         //stuff
         //printf("Discontinuity found at %d \n", i + 1);
        i++;
      }

      //printf("i: %d counter: %d\n", i, counter);
      if(path[i][DIR] == 1 || path[i][DIR] == 3){
         //There should be a check that it is within the map
         if(map[path[i][Y]][path[i][X] - 1] == PATH || map[path[i][Y]][path[i][X] + 1] == PATH){
            if(path[i][DIR] != path[i + 1][DIR]){
               //current direction , the next direction
               if((path[i][DIR] == 1 && path[i + 1][DIR] == 4) || (path[i][DIR] == 3 && path[i + 1][DIR] == 2)){//changed
                  //printf("L/R intersection found (%d) [direction = %d] -- TURN LEFT\n", i, path[i][DIR]);
                  instructions[counter] = LEFT;
                  counter++;
               }else if((path[i][DIR] == 1 && path[i + 1][DIR] == 2) || (path[i][DIR] == 3 && path[i + 1][DIR] == 4)){//changed
                  //printf("L/R intersection found (%d) [direction = %d] -- TURN RIGHT\n", i, path[i][DIR]);
                  instructions[counter] = RIGHT;
                  counter++;
               }else if ((path[i][DIR] == 1 && path[i + 1][DIR] == 3) || (path[i][DIR] == 3 && path[i + 1][DIR] == 1)){//changed
                  //printf("L/R intersection found (%d) [direction = %d] -- TURN U-TURN\n", i, path[i][DIR]);
                  instructions[counter] = UTURN;
                  counter++;
               }else{
                  //printf("Prev %d, current %d\n",path[i + 1][DIR], path[i][DIR]);
               }
            }else{
               //printf("L/R intersection found (%d) [direction = %d]\n", i, path[i][DIR]);
               instructions[counter] = STRAIGHT;
               counter++;
            }
         }else{//not an intersection
            if ((path[i][DIR] == 1 && path[i + 1][DIR] == 3) || (path[i][DIR] == 3 && path[i + 1][DIR] == 1)){//changed
               //printf("L/R intersection found (%d) [direction = %d] -- TURN U-TURN\n", i, path[i][DIR]);
               instructions[counter] = UTURN;
               counter++;
            }else{
            //printf("[(%d), direction = %d]\n", i, path[i][DIR]);
         }
         }
      }else{
         if(map[path[i][Y] - 1][path[i][X]] == PATH || map[path[i][Y] + 1][path[i][X]] == PATH){
            if(path[i][DIR] != path[i + 1][DIR]){
               if((path[i][DIR] == 4 && path[i + 1][DIR] == 3) || (path[i][DIR] == 2 && path[i + 1][DIR] == 1)){//changed
                  //printf("U/D intersection found (%d) [direction = %d] -- TURN LEFT\n", i, path[i][DIR]);
                  instructions[counter] = LEFT;
                  counter++;
               }else if((path[i][DIR] == 4 && path[i + 1][DIR] == 1) || (path[i][DIR] == 2 && path[i + 1][DIR] == 3)){//changed
                  //printf("U/D intersection found (%d) [direction = %d] -- TURN RIGHT\n", i, path[i][DIR]);
                  instructions[counter] = RIGHT;
                  counter++;
               }else if ((path[i][DIR] == 4 && path[i + 1][DIR] == 2) || (path[i][DIR] == 2 && path[i + 1][DIR] == 4)){//changed
                  //printf("U/D intersection found (%d) [direction = %d] -- TURN U-TURN\n", i, path[i][DIR]);
                  instructions[counter] = UTURN;
                  counter++;
               }else{
                  //printf("Prev %d, current %d\n", path[i + 1][DIR], path[i][DIR]);
               }
            }else{
               //printf("U/D intersection found (%d) [direction = %d]\n", i, path[i][DIR]);
               instructions[counter] = STRAIGHT;
               counter++;
            }

         }else{
            if ((path[i][DIR] == 4 && path[i + 1][DIR] == 2) || (path[i][DIR] == 2 && path[i + 1][DIR] == 4)){//changed
               //printf("U/D intersection found (%d) [direction = %d] -- TURN U-TURN\n", i, path[i][DIR]);
               instructions[counter] = UTURN;
               counter++;
            }else{
            //printf("[(%d), direction = %d]\n", i, path[i][DIR]);
         }
         }
      }
   }
   instructions[counter] = '\0';
   return 0;
}


uint32_t generateDirections(){
   uint32_t counter = 0;
   uint32_t prev_intersection = 0;
   int food_count;
    
   for(food_count = 0; food_count < food_length; food_count++)
{   
    prev_intersection = 0;
    if(counter != 0)
    {
        start[0] = destination[0];
        start[1] = destination[1];
        
//        if(robot_direction != tracked_direction)
//        {
//            if((tracked_direction == (robot_direction - 1)) || ((tracked_direction == 3) && (robot_direction == 0))) //do a right turn
//            {
//                instructions[counter] = RIGHT;
//                counter++;
//            }
//            else if((tracked_direction == (robot_direction + 1)) || ((tracked_direction == 0) && (robot_direction == 3))) //do a left turn
//            {
//                instructions[counter] = LEFT;
//                counter++;
//            }
//        }
    }
    
    destination[0] = food_list[food_count][0];
    destination[1] = food_list[food_count][1];
    
    char message[128];
    sprintf(message, "pathing from %d,%d to %d,%d from dir %d\r\n", start[0], start[1], destination[0], destination[1], robot_direction);
    UART_PutString(message);
    
   int end = djikstras(map, food_list, path, start, destination);

   int i;
   for(i = end; i >= 1; i--){
      if(path[i][DIR] == 1 || path[i][DIR] == 3){
         //There should be a check that it is within the map
         if(map[path[i][Y]][path[i][X] - 1] == PATH || map[path[i][Y]][path[i][X] + 1] == PATH){
            if(path[i][DIR] != path[i - 1][DIR]){
               //current direction - the next direction > 0 turn left otherwise turn right
               if((path[i][DIR] == 1 && path[i-1][DIR] == 4) || (path[i][DIR] == 3 && path[i-1][DIR] == 2)){//changed
                  //printf("L/R intersection found (%d) [direction = %d] -- TURN LEFT\n", end - i + 1, path[i][DIR]);
                  instructions[counter] = LEFT;
                  instructions[counter + 1] = (end - i + 1 )- prev_intersection;
                  counter += 2;
                  prev_intersection = end - i + 1;//save the number of blocks travelled previously
               }else if((path[i][DIR] == 1 && path[i-1][DIR] == 2) || (path[i][DIR] == 3 && path[i-1][DIR] == 4)){//changed
                  //printf("L/R intersection found (%d) [direction = %d] -- TURN RIGHT\n", end - i + 1, path[i][DIR]);
                  instructions[counter] = RIGHT;
                  instructions[counter + 1] = (end - i + 1 )- prev_intersection;
                  counter += 2;
                  prev_intersection = end - i + 1;
               }else if ((path[i][DIR] == 1 && path[i-1][DIR] == 3) || (path[i][DIR] == 3 && path[i-1][DIR] == 1)){//changed
                  //printf("L/R intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - i + 1, path[i][DIR]);
                  instructions[counter] = UTURN;
                  instructions[counter + 1] = (end - i + 1 )- prev_intersection;
                  counter += 2;
                  prev_intersection = end - i + 1;
               }else{
                  //printf("Prev %d, current %d\n",path[i-1][DIR], path[i][DIR]);
               }
            }else{
               //printf("L/R intersection found (%d) [direction = %d]\n", end - i + 1, path[i][DIR]);
               instructions[counter] = STRAIGHT;
               instructions[counter + 1] = (end - i + 1 )- prev_intersection;
               counter += 2;
               prev_intersection = end - i + 1;
            }
         }else{//not an intersection
            if ((path[i][DIR] == 1 && path[i-1][DIR] == 3) || (path[i][DIR] == 3 && path[i-1][DIR] == 1)){//changed
               //printf("L/R intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - i + 1, path[i][DIR]);
               instructions[counter] = UTURN;
               instructions[counter + 1] = (end - i + 1 )- prev_intersection;
               counter += 2;
               prev_intersection = end - i + 1;
            }else{
            //printf("[(%d), direction = %d]\n", end - i + 1, path[i][DIR]);
         }
         }
      }else{
         if(map[path[i][Y] - 1][path[i][X]] == PATH || map[path[i][Y] + 1][path[i][X]] == PATH){
            if(path[i][DIR] != path[i - 1][DIR]){
               if((path[i][DIR] == 4 && path[i-1][DIR] == 3) || (path[i][DIR] == 2 && path[i-1][DIR] == 1)){//changed
                  //printf("U/D intersection found (%d) [direction = %d] -- TURN LEFT\n", end - i + 1, path[i][DIR]);
                  instructions[counter] = LEFT;
                  instructions[counter + 1] = (end - i + 1 )- prev_intersection;
                  counter += 2;
                  prev_intersection = end - i + 1;
               }else if((path[i][DIR] == 4 && path[i-1][DIR] == 1) || (path[i][DIR] == 2 && path[i-1][DIR] == 3)){//changed
                  //printf("U/D intersection found (%d) [direction = %d] -- TURN RIGHT\n", end - i + 1, path[i][DIR]);
                  instructions[counter] = RIGHT;
                  instructions[counter + 1] = (end - i + 1 )- prev_intersection;
                  counter += 2;
                  prev_intersection = end - i + 1;
               }else if ((path[i][DIR] == 4 && path[i-1][DIR] == 2) || (path[i][DIR] == 2 && path[i-1][DIR] == 4)){//changed
                  //printf("U/D intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - i + 1, path[i][DIR]);
                  instructions[counter] = UTURN;
                  instructions[counter + 1] = (end - i + 1 )- prev_intersection;
                  counter += 2;
                  prev_intersection = end - i + 1;
               }else{
                  //printf("Prev %d, current %d\n", path[i-1][DIR], path[i][DIR]);
               }
            }else{
               //printf("U/D intersection found (%d) [direction = %d]\n", end - i + 1, path[i][DIR]);
               instructions[counter] = STRAIGHT;
               instructions[counter + 1] = (end - i + 1 )- prev_intersection;
               counter += 2;
               prev_intersection = end - i + 1;
            }

         }else{
            if ((path[i][DIR] == 4 && path[i-1][DIR] == 2) || (path[i][DIR] == 2 && path[i-1][DIR] == 4)){//changed
               //printf("U/D intersection found (%d) [direction = %d] -- TURN U-TURN\n", end - i + 1, path[i][DIR]);
               instructions[counter] = UTURN;
               instructions[counter + 1] = (end - i + 1 )- prev_intersection;
               counter += 2;
               prev_intersection = end - i + 1;
            }else{
           // printf("[(%d), direction = %d]\n", end - i + 1, path[i][DIR]);
         }
         }
      }
    
   }
   instructions[counter] = DRIVE;
   instructions[counter + 1] = end - prev_intersection;
   counter += 2;
   //instructions[counter] = '\0';
}
   return counter;
}

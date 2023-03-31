#ifndef PROPER_COURSEWORK_ROBOT_CONTROLLER_H
#define PROPER_COURSEWORK_ROBOT_CONTROLLER_H
#include "robot.h"
#include "../maze/maze.h"

typedef enum actions {
    moveForward = 0,
    turnRight = 1,
    turnLeft = 2
} actions;

void robotDo(struct canvas *maze, struct shape *character, struct robot *robot, const int* actions, int animTick);

int atDeadEnd(struct canvas *maze, struct robot *robot);
void reverseFunction(struct canvas *maze, struct shape *character, robot *robot, enum actions action, int animTick);

int checkDirection(struct canvas *maze, struct shape *character, struct robot *newRobot, int animTick, int direction, int isAnimated);
int depthFirstSearch(struct canvas *maze, struct shape *character, struct robot *robot, int animTick, int isAnimated);
void greedySearch(struct canvas *maze, struct shape *character, struct robot *robot, enum actions action, int animTick);

#endif

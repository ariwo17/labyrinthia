#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../maze/maze.h"
#include "robot_controller.h"

// Possibly try pre-increment/decrement rather than post-increment/decrement if it doesn't work
void forward(struct robot *robot)
{
    switch(robot->direction)
    {
        case north:
            robot->position[1]--;
            break;
        case west:
            robot->position[0]++;
            break;
        case south:
            robot->position[1]++;
            break;
        case east:
            robot->position[0]--;
            break;
    }
}

void left(struct robot *robot)
{
    direction newDir;
    switch(robot->direction)
    {
        case north:
            newDir = west;
            break;
        case west:
            newDir = south;
            break;
        case south:
            newDir = east;
            break;
        case east:
            newDir = north;
            break;
    }
    robot->direction = newDir;
}

void right(struct robot *robot)
{
    direction newDir;
    switch(robot->direction)
    {
        case north:
            newDir = east;
            break;
        case east:
            newDir = south;
            break;
        case south:
            newDir = west;
            break;
        case west:
            newDir = north;
            break;
    }
    robot->direction = newDir;
}
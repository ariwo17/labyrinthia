#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h"
#include "robot_controller.h"
#include "../maze/maze.h"
#include "../presets.h"

void robotDo(struct canvas *maze, struct shape *character, struct robot *robot, const int* actions, int animTick)
{
    for(int i=0; i<=sizeof(actions)/4; i++)
    {
        switch(actions[i])
        {
            case moveForward:
                forward(robot);
                refreshMaze(maze, character, robot, animTick);
                break;
            case turnRight:
                right(robot);
                refreshMaze(maze, character, robot, animTick);
                break;
            case turnLeft:
                left(robot);
                refreshMaze(maze, character, robot, animTick);
                break;
            default:
                break;
        }
        //printf("Robot at (%d, %d), facing %d", robot->position[0], robot->position[1], robot->direction);
    }
}

void reverseFunction(struct canvas *maze, struct shape *character, robot *robot, enum actions action, int animTick)
{
    int operations[3];
    switch(action)
    {
        case moveForward:
            operations[0] = turnRight;
            break;
        case turnRight:
            operations[0] = turnLeft;
            break;
        case turnLeft:
            operations[0] = turnRight;
            break;
        default:
            break;
    }
    robotDo(maze, character, robot, operations, animTick);
}

int atDeadEnd(struct canvas *maze, struct robot *robot)
{
    int x = robot->position[0];
    int y = robot->position[1];
    if(x-1 >= 0 && (maze->mazeMap[x-1][y] == emptyCell || maze->mazeMap[x-1][y] == marker)) return 0;
    else if(x+1 < maze->gridSize[0] && (maze->mazeMap[x+1][y] == emptyCell || maze->mazeMap[x+1][y] == marker)) return 0;
    else if(y+1 < maze->gridSize[1] && (maze->mazeMap[x][y+1] == emptyCell || maze->mazeMap[x][y+1] == marker)) return 0;
    else if(y-1 >= 0 && (maze->mazeMap[x][y-1] == emptyCell || maze->mazeMap[x][y-1] == marker)) return 0;
    return 1;
}

int checkDirection(struct canvas *maze, struct shape *character, struct robot *newRobot, int animTick, int direction, int isAnimated)
{
    if(direction == moveForward && canMoveForward(maze, newRobot))
    {
        forward(newRobot);
        if(isAnimated == 1) refreshMaze(maze, character, newRobot, animTick);
        int result = depthFirstSearch(maze, character, newRobot, animTick, isAnimated);
        if(result) return result;
    }
    else if (direction == turnRight) {
        right(newRobot);
        if(isAnimated == 1) refreshMaze(maze, character, newRobot, animTick);
        int result = depthFirstSearch(maze, character, newRobot, animTick, isAnimated);
        if(result) return result;
    }
    else if (direction == turnLeft) {
        left(newRobot);
        if(isAnimated == 1) refreshMaze(maze, character, newRobot, animTick);
        int result = depthFirstSearch(maze, character, newRobot, animTick, isAnimated);
        if(result) return result;
    }
    return 0;
}

int depthFirstSearch(struct canvas *maze, struct shape *character, struct robot *robot, int animTick, int isAnimated){
    int x = robot->position[0];
    int y = robot->position[1];
    if(atMarker(maze, robot))
    {
        if(isAnimated == 1) refreshMaze(maze, character, robot, animTick);
        return 1;
    }
    maze->mazeMap[x][y] = visited;
    if(atDeadEnd(maze, robot)) return 0;
    for(int i = moveForward; i<=turnLeft; i++)
    {
        struct robot *newRobot = malloc(sizeof(struct robot));
        *newRobot = *robot;
        int result = checkDirection(maze, character, newRobot, animTick, i, isAnimated);
        if(result) return result;
    }
    return 0;
}

void greedySearch(struct canvas *maze, struct shape *character, struct robot *robot, enum actions action, int animTick)
{
    while(!atMarker(maze, robot))
    {
        if(action == turnRight) right(robot);
        else if(action == turnLeft) left(robot);
        refreshMaze(maze, character, robot, animTick);
        if(canMoveForward(maze, robot))
        {
            forward(robot);
            refreshMaze(maze, character, robot, animTick);
        }
        else
        {
            while(!canMoveForward(maze, robot))
            {
                reverseFunction(maze, character, robot, action, animTick);
                refreshMaze(maze, character, robot, animTick);
            }
            forward(robot);
            refreshMaze(maze, character, robot, animTick);
        }
    }
}
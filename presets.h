#ifndef PROPER_COURSEWORK_PRESETS_H
#define PROPER_COURSEWORK_PRESETS_H
#include "robot/robot.h"
#include "robot/robot_controller.h"

typedef enum animTickSpeed {
    turtle = 1000,
    sluggish = 500,
    slow = 250,
    medium = 100,
    fast = 50,
    thunder = 10,
    lightning = 5
} animTickSpeed;

typedef enum algorithm {
    dfs = 0, //depthFirstSearch(),
    rightGreedy = 1, //greedySearch(maze, character, robot, turnRight, animTick),
    leftGreedy = 2 //greedySearch(maze, character, robot, turnLeft, animTick)
} algorithm;

typedef struct options {
    algorithm algorithm;
    animTickSpeed animTickSpeed;
} options;

#endif

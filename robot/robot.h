#ifndef PROPER_COURSEWORK_ROBOT_H
#define PROPER_COURSEWORK_ROBOT_H
#include "../graphics/graphics.h"

typedef enum direction {
    north = 0,
    west = 1,
    south = 2,
    east = 3
} direction;

typedef struct robot {
    int position[2];
    enum direction direction;
} robot;

void forward(struct robot *robot);
void left(struct robot *robot);
void right(struct robot *robot);





#endif
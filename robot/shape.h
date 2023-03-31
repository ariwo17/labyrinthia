#ifndef PROPER_COURSEWORK_SHAPE_H
#include "./robot.h"
#include "../maze/maze.h"
#define PROPER_COURSEWORK_SHAPE_H
#define MAX_SIDES 10

// See if I can merge robot and shape together at some point
struct shape {
    int x, y;
    int numberOfSides;
    double sideLength;
    double angle;
    colour backgroundColour;
    colour outlineColour;
    char* skin;
    int xCoords[MAX_SIDES];
    int yCoords[MAX_SIDES];
};

double convertToRadians(double angle);
char *concat(const char *a, const char *b, const char *c);

void setOffsetByDir(struct shape *character, struct robot *robot);

void pointRobotDir(struct shape *character, struct robot *robot);
void showSkin(struct shape *character, struct robot *robot);

#endif

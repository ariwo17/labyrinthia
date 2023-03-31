#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../maze/maze.h"

double convertToRadians(double angle)
{
    return (M_PI / 180) * angle;
}

char *concat(const char *a, const char *b, const char *c) {
    size_t aLen = strlen(a);
    size_t bLen = strlen(b);
    size_t cLen = strlen(c);
    char *res = malloc(aLen + bLen + cLen + 1);
    if (res) {
        memcpy(res, a, aLen);
        memcpy(res + aLen, b, bLen);
        memcpy(res + aLen + bLen, c, cLen + 1);
    }
    return res;
}

void setOffsetByDir(struct shape *character, struct robot *robot)
{
    switch(robot->direction){
        case north:
            character->x += (int)character->sideLength;
            character->y += (int)character->sideLength;
            break;
        case west:
            character->y += (int)character->sideLength;
            break;
        case south:
            break;
        case east:
            character->x += (int)character->sideLength;
            break;
    }
}

void pointRobotDir(struct shape *character, struct robot *robot)
{
    switch(robot->direction){
        case north:
            character->angle = 180;
            break;
        case west:
            character->angle = 270;
            break;
        case south:
            character->angle = 0;
            break;
        case east:
            character->angle = 90;
            break;
    }
}

void showSkin(struct shape *character, struct robot *robot)
{
    char* skin = character->skin;
    char* fileDirectory = concat("./robot/skins/", skin, ".png");
    displayImage(fileDirectory, character->x, character->y);
    //printf("Skin loaded at %s", fileDirectory);
}
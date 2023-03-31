#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./maze/maze.h"
#include "./maze/random.h"
#include "robot/robot_controller.h"
#include "presets.h"
#include <errno.h>
#include <time.h>

void defaultSettings(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings){
    maze->levelName = NULL;
    character->skin = "roby";
    character->numberOfSides = 3;
    settings->algorithm = dfs;
    settings->animTickSpeed = slow;
}

void retrieveUserInput(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings, int argc, char **argv)
{
    char* algorithm;
    maze->levelName = argv[1];
    character->skin = argv[2];
    algorithm = argv[3];
    if(strcmp(algorithm, "dfs") == 0) settings->algorithm = dfs;
    else if(strcmp(algorithm, "r-greedy") == 0) settings->algorithm = rightGreedy;
    else if(strcmp(algorithm, "l-greedy") == 0) settings->algorithm = leftGreedy;
    settings->animTickSpeed = atoi(argv[4]);
    loadMaze(maze, character, robot);
}

void runSearchAlgorithm(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings)
{
    switch(settings->algorithm)
    {
        case dfs:
            depthFirstSearch(maze, character, robot, settings->animTickSpeed, 1);
            break;
        case rightGreedy:
            greedySearch(maze, character, robot, turnRight, settings->animTickSpeed);
            break;
        case leftGreedy:
            greedySearch(maze, character, robot, turnLeft, settings->animTickSpeed);
            break;
    }
}

int main(int argc, char **argv)
{
    struct canvas maze;
    struct shape character;
    struct robot robot;
    struct options settings;
    defaultSettings(&maze, &character, &robot, &settings);
    srand(time(NULL));
    if (argc == 3) {
        retrieveUserInput(&maze, &character, &robot, &settings, argc, argv);
    }
    else generateRandomMaze(&maze, &character, &robot, &settings);
    runSearchAlgorithm(&maze, &character, &robot, &settings);
    return 0;
}
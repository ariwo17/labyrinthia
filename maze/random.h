#ifndef PROPER_COURSEWORK_RANDOM_H
#define PROPER_COURSEWORK_RANDOM_H
#include "maze.h"
#include "../robot/robot_controller.h"
#include "../presets.h"

typedef enum cellSize {
    tiny = 15,
    small = 25,
    normal = 50,
    large = 75,
    giant = 100
} cellSize;

int findMaxCells(struct canvas *maze, int constraint, int margin);

void defaultMazeSettings(struct canvas *maze, struct shape *character, struct robot *robot);

int randomNumber(int range);
void randomizeMazeSpecs(struct canvas *maze);
void randomizeColours(struct canvas *maze);
void randomizeExit(struct canvas *maze);
void randomizeEntrance(struct canvas *maze);

void loadBackgroundSettings(struct canvas *maze);
void loadSkinSettings(struct shape *character);
void loadDesignSettings(struct canvas *maze, struct shape *character);

// Functions relating to the custom random maze generation algorithm
void randomizeObstacles(struct canvas *maze, double probability);
int removeObstacle(struct canvas *maze, struct shape *character, struct options *settings, int x, int y);
int ensureMazeSolvable(struct canvas *maze, struct shape *character, struct options *settings, int x, int y);
void polishMaze(struct canvas *maze, struct shape *character, struct options *settings);
void randomMazeSettings(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings);

// Functions relating to the Randomized DFS maze generation algorithm
void createBlockCanvas(struct canvas *maze);
void randomizeEndpoints(struct canvas *maze);
void generateRandomPath(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings);
int randomDFS(struct canvas *maze, struct shape *character, struct robot *robot, int animTick);
void randomDfsSettings(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings);

void resetVisitTrace(struct canvas *maze);

void generateRandomMaze(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings);


#endif

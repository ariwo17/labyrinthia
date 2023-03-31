#ifndef PROPER_COURSEWORK_MAZE_H
#define PROPER_COURSEWORK_MAZE_H
#include "../robot/robot.h"
#include "../robot/shape.h"

#define MAXSIZE 100

struct canvas {
    char* levelName;
    int gridSize[2];
    int cellSideLength;
    int gridLineWidth;
    int gridOffset;
    colour gridLineColour;
    colour backgroundColour;
    char* backgroundImage;
    int spawnPoint[2];
    direction initDir;
    int markerPoint[2];
    colour robotColour;
    colour gridColour;
    colour obstacleColour;
    colour markerColour;
    int numObstacles;
    int mazeMap[MAXSIZE][MAXSIZE];
};

typedef enum objectType {
    emptyCell = 0,
    obstacle = 1,
    marker = 2,
    visited = 3
} objectType;

void loadBgImage(struct canvas *maze);
void initializeCanvas(struct canvas *maze);
void populateMaze(struct canvas *maze, FILE *filePointer);

int coordToPixels(struct canvas *maze, int coord);

int isObstacle(struct canvas *maze, int xCoord,int yCoord);
int isMarker(struct canvas *maze, int xCoord,int yCoord);
int isVisited(struct canvas *maze, int xCoord, int yCoord);

void tracePoint(struct canvas *maze, struct shape *character, int i);
void generateVertices(struct canvas *maze, struct shape *character, struct robot *robot);

void plotObject(enum objectType object, struct canvas *maze, int xCoord, int yCoord);
void mazeMapToObject(struct canvas *maze, int xCoord, int yCoord);
void createMazeMappings(struct canvas *maze);
void generateRobot(struct canvas *maze, struct shape *character, struct robot *robot);
void plotRobot(struct canvas *maze, struct shape *character, struct robot *robot);

int atMarker(struct canvas *maze, struct robot *robot);
int atEdge(struct canvas *maze, struct robot *robot);
int canMoveForward(struct canvas *maze, struct robot *robot);

int canCarveForward(struct canvas *maze, struct robot *robot);

void refreshMaze(struct canvas *maze, struct shape *character, struct robot *robot, int animTick);
void loadMaze(struct canvas *maze, struct shape *character, struct robot *robot);
void loadMazeLocally(struct canvas *maze, struct shape *character, struct robot *robot);

#endif

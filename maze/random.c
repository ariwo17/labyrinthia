#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "maze.h"
#include "../robot/robot.h"
#include <string.h>
#include "random.h"
#include "../robot/robot_controller.h"
#include "../presets.h"

#define MAX_PIXELS_X 2500
#define MAX_PIXELS_Y 1500
#define OUTPUT_BOX_Y 300
#define NUM_COLOURS 13

int findMaxCells(struct canvas *maze, int constraint, int margin)
{
    int pixelLimit = constraint - maze->gridOffset * 2 - margin ;
    return round(pixelLimit / maze->cellSideLength);
}

void defaultMazeSettings(struct canvas *maze, struct shape *character, struct robot *robot) {
    maze->gridSize[0] = 8;
    maze->gridSize[1] = 8;
    maze->cellSideLength = normal;
    maze->gridOffset = normal;
    maze->gridLineWidth = 1;
    maze->gridLineColour = black;
    maze->backgroundColour = blue;
    maze->backgroundImage = "aurora";
    maze->spawnPoint[0] = 2;
    maze->spawnPoint[1] = 2;
    maze->initDir = east;
    maze->markerPoint[0] = 7;
    maze->markerPoint[1] = 2;
    maze->robotColour = green;
    maze->gridColour = white;
    maze->obstacleColour = black;
    maze->markerColour = gray;
    maze->numObstacles = 25;
    memset(maze->mazeMap, emptyCell, sizeof maze->mazeMap);
    maze->mazeMap[maze->markerPoint[0]][maze->markerPoint[1]] = 2;
    maze->mazeMap[0][5] = 1;
    maze->mazeMap[1][1] = 1;
    maze->mazeMap[1][2] = 1;
    maze->mazeMap[1][3] = 1;
    maze->mazeMap[1][7] = 1;
    maze->mazeMap[2][3] = 1;
    maze->mazeMap[2][5] = 1;
    maze->mazeMap[2][6] = 1;
    maze->mazeMap[3][0] = 1;
    maze->mazeMap[3][1] = 1;
    maze->mazeMap[3][2] = 1;
    maze->mazeMap[3][3] = 1;
    maze->mazeMap[4][3] = 1;
    maze->mazeMap[4][4] = 1;
    maze->mazeMap[4][5] = 1;
    maze->mazeMap[4][6] = 1;
    maze->mazeMap[5][1] = 1;
    maze->mazeMap[5][4] = 1;
    maze->mazeMap[5][6] = 1;
    maze->mazeMap[6][2] = 1;
    maze->mazeMap[7][0] = 1;
    maze->mazeMap[7][3] = 1;
    maze->mazeMap[7][5] = 1;
    maze->mazeMap[7][6] = 1;
    maze->mazeMap[7][7] = 1;

}

int randomNumber(int range){
    return rand() % range;
}

void randomizeMazeSpecs(struct canvas *maze)
{
    maze->cellSideLength = normal;
    maze->gridOffset = normal;
    maze->gridLineWidth = 1;
    double adjustment = 0.40;
    double weightX = 0.70;
    double weightY = 0.25;
    int equalizer = (int)((1-adjustment) * abs(MAX_PIXELS_Y - MAX_PIXELS_X));
    int maxWidth = findMaxCells(maze, MAX_PIXELS_X, equalizer);
    int maxHeight = findMaxCells(maze, MAX_PIXELS_Y, OUTPUT_BOX_Y);
    int width = floor(maxWidth * adjustment);
    int height = floor(maxHeight * adjustment);
    int skewX = randomNumber(floor(width * weightX));
    int skewY = randomNumber(floor(height * weightY));
    maze->gridSize[0] = width - skewX;
    maze->gridSize[1] = height - skewY;
}

// Perhaps automate this using argc & **argv
void randomizeColours(struct canvas *maze)
{
    maze->backgroundColour = blue;
    maze->robotColour = green;
    maze->gridColour = white;
    maze->obstacleColour = black;
    maze->gridLineColour = black;
    maze->markerColour = gray;
//    maze->backgroundColour = randomNumber(NUM_COLOURS);
//    do {
//        maze->robotColour = randomNumber(NUM_COLOURS);
//    } while(maze->robotColour == maze->backgroundColour);
//    do {
//        maze->obstacleColour = randomNumber(NUM_COLOURS);
//        maze->gridColour = maze->obstacleColour;
//    } while(maze->obstacleColour == maze->backgroundColour || maze->obstacleColour == maze->robotColour);
//    do {
//        maze->markerColour = randomNumber(NUM_COLOURS);
//    } while(maze->markerColour == maze->backgroundColour || maze->markerColour == maze->robotColour || maze->markerColour == maze->obstacleColour);
}

void randomizeExit(struct canvas *maze)
{
    int xPoint;
    int yPoint;
    do {
        xPoint = randomNumber(maze->gridSize[0]);
        yPoint = randomNumber(maze->gridSize[1]);
    } while(isObstacle(maze, xPoint, yPoint));
    maze->spawnPoint[0] = xPoint;
    maze->spawnPoint[1] = yPoint;
}

void randomizeEntrance(struct canvas *maze)
{
    int xPoint;
    int yPoint;
    do {
        xPoint = randomNumber(maze->gridSize[0]);
        yPoint = randomNumber(maze->gridSize[1]);
    } while(isObstacle(maze, xPoint, yPoint) || isMarker(maze, xPoint, yPoint));
    maze->markerPoint[0] = xPoint;
    maze->markerPoint[1] = yPoint;
    maze->initDir = randomNumber(3);
}

void loadBackgroundSettings(struct canvas *maze)
{
    int randomImage = randomNumber(4);
    switch(randomImage){
        case 0:
            maze->backgroundImage = "portico";
            break;
        case 1:
            maze->backgroundImage = "mandelbrot";
            break;
        case 2:
            maze->backgroundImage = "aurora";
            break;
        default:
            maze->backgroundImage = NULL;
    }
}

void loadSkinSettings(struct shape *character)
{
    character->numberOfSides = 4;
    int randomSkin = randomNumber(6);
    switch(randomSkin){
        case 0:
            character->skin = "graham";
            break;
        case 1:
            character->skin = "sobhan";
            break;
        case 2:
            character->skin = "roby";
            break;
        default:
            character->skin = NULL;
            character->numberOfSides = 3;
    }
}

void loadDesignSettings(struct canvas *maze, struct shape *character)
{
    // If the maze cell side length is compatible with the skins, load one of them
    int length = maze->cellSideLength;
    int width = maze->gridSize[0];
    int height = maze->gridSize[1];
    if(length == normal) loadSkinSettings(character);
    // If the background images can fit comfortably, load one of them
    if(coordToPixels(maze, width) <= 500 && coordToPixels(maze, height) <= 500)
    {
        loadBackgroundSettings(maze);
    }

}

void randomizeObstacles(struct canvas *maze, double probability)
{
    for(int y = 0; y < maze->gridSize[1]; y++)
    {
        for(int x = 0; x < maze->gridSize[0]; x++)
        {
            int threshold = 100;
            int pickerWheel = randomNumber(threshold);
            if(pickerWheel < round(threshold * probability))
            {
                maze->mazeMap[x][y] = obstacle;
                maze->numObstacles++;
            }
        }
    }
}

int removeObstacle(struct canvas *maze, struct shape *character, struct options *settings, int x, int y)
{
    maze->mazeMap[x][y] = emptyCell;
    maze->numObstacles--;
    return 1;
}

//int ensureMazeSolvable(struct canvas *maze, struct shape *character, struct options *settings, int x, int y)
//{
//    struct robot scout;
//    scout.direction = north;
//    for(int i = 0; i < 4; i++)
//    {
//        scout.position[0] = x;
//        scout.position[1] = y;
//        if(!atEdge(maze, &scout))
//        {
//            forward(&scout);
//            if(isObstacle(maze, scout.position[0], scout.position[1]))
//            {
//                removeObstacle(maze, character, settings, scout.position[0], scout.position[1]);
//            }
//        }
//        right(&scout);
//    }
//    return 0;
//}

//void polishMaze(struct canvas *maze, struct shape *character, struct options *settings)
//{
//    for(int y = 0; y < maze->gridSize[1]; y++)
//    {
//        for(int x = 0; x < maze->gridSize[0]; x++)
//        {
//            struct robot rover;
//            if(depthFirstSearch(maze, character, &rover, settings->animTickSpeed) == 0)
//            {
//                ensureMazeSolvable(maze, character, settings, x, y);
//            }
//        }
//    }
//}

void randomMazeSettings(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings)
{
    randomizeMazeSpecs(maze);
    randomizeColours(maze);
    loadDesignSettings(maze, character);
    memset(maze->mazeMap, emptyCell, sizeof maze->mazeMap);
    randomizeObstacles(maze, 0.5);
    randomizeExit(maze);
    randomizeEntrance(maze);
    maze->mazeMap[maze->markerPoint[0]][maze->markerPoint[1]] = marker;
    //polishMaze(maze, character, settings);
}

void createBlockCanvas(struct canvas *maze)
{
    for(int y=0; y<maze->gridSize[1]; y++)
    {
        for(int x=0; x<maze->gridSize[0]; x++)
        {
            maze->mazeMap[x][y] = obstacle;
        }
    }
}

void randomizeEndpoints(struct canvas *maze)
{
    int width = maze->gridSize[0];
    int height = maze->gridSize[1];
    maze->spawnPoint[0] = randomNumber(width);
    maze->spawnPoint[1] = randomNumber(height);
    maze->markerPoint[0] = randomNumber(width);
    maze->markerPoint[1] = randomNumber(height);
    maze->initDir = randomNumber(4);
    maze->mazeMap[maze->spawnPoint[0]][maze->spawnPoint[1]] = emptyCell;
    maze->mazeMap[maze->markerPoint[0]][maze->markerPoint[1]] = marker;
}

void generateRandomPath(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings)
{
    int width = maze->gridSize[0];
    int height = maze->gridSize[1];
    int pathLimit = width * height;
    int k = 5;
    int x, y;
    for(int i = 0; i < randomNumber(pathLimit); i++)
    {
        x = robot->position[0];
        y = robot->position[1];
        int randomAction = randomNumber(k);
        switch(randomAction)
        {
            default:
                if(!isVisited(maze, x, y)) forward(robot);
                maze->mazeMap[x][y] = emptyCell;
                createMazeMappings(maze);
                break;
            case 1:
                right(robot);
                break;
            case 2:
                left(robot);
                break;
        }
        refreshMaze(maze, character, robot, settings->animTickSpeed);
    }
}

int randomDFS(struct canvas *maze, struct shape *character, struct robot *robot, int animTick){
    return 1;
}

void randomDfsSettings(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings)
{
    randomizeMazeSpecs(maze);
    randomizeColours(maze);
    loadDesignSettings(maze, character);
    // For testing purposes, I'm going to stick to no skin for now.
    character->sideLength = 3;
    character->skin = NULL;
    createBlockCanvas(maze);
    randomizeEndpoints(maze);

}

void resetVisitTrace(struct canvas *maze)
{
    for(int y=0; y<maze->gridSize[1]; y++)
    {
        for(int x=0; x<maze->gridSize[0]; x++)
        {
            if(maze->mazeMap[x][y] == visited)
            {
                maze->mazeMap[x][y] = emptyCell;
            }
        }
    }
}

void generateRandomMaze(struct canvas *maze, struct shape *character, struct robot *robot, struct options *settings)
{

//    randomMazeSettings(maze, character, robot, settings);
//    loadMazeLocally(maze, character, robot);
    while(depthFirstSearch(maze, character, robot, settings->animTickSpeed, 0) == 0)
    {
        randomMazeSettings(maze, character, robot, settings);
        //resetVisitTrace(maze);
        loadMazeLocally(maze, character, robot);
    }

}

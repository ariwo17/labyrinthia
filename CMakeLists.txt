cmake_minimum_required(VERSION 3.23)
project(Proper_Coursework C)

set(CMAKE_C_STANDARD 99)

add_executable(Proper_Coursework main.c maze/maze.c maze/random.c robot/shape.c robot/robot.c robot/robot_controller.c graphics/graphics.c)

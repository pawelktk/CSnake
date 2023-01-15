cmake_minimum_required(VERSION 3.9.1)

project(CSnake)

include_directories(${.})
add_executable(snake main.c board.c apple.c snake.c)


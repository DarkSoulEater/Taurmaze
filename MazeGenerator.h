//
// Created by asmekal on 01.05.2021.
//

//to create maze use GetMaze(length, width)

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#ifndef TAURMAZE_MAZE_GENERATOR_H
#define TAURMAZE_MAZE_GENERATOR_H

#endif //TAURMAZE_MAZE_GENERATOR_H

bool IsFree(std::vector<std::vector<int>>& maze, int x, int y) {
    return x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && !maze[x][y];
}

bool CanGo(std::vector<std::vector<int>>& maze, int x, int y) {
    return x < 0 || y < 0 || x >= maze.size() || y >= maze[0].size() || !maze[x][y];
}

bool ArePointAndBordersFree(std::vector<std::vector<int>>& maze, int x, int y, int px, int py) {
    //check point
    if (!IsFree(maze, x, y)) return false;
    //check borders
    if (!CanGo(maze, x - 1, y) && x - 1 != px) return false;
    if (!CanGo(maze, x, y - 1) && y - 1 != py) return false;
    if (!CanGo(maze, x + 1, y) && x + 1 != px) return false;
    if (!CanGo(maze, x, y + 1) && y + 1 != py) return false;
    return true;
}

void FillMaze(std::vector<std::vector<int>>& maze, int x, int y) {
    maze[x][y] = 1;
    std::vector<std::pair<int, int>> buffer;
    do {
        buffer.clear();
        //check if we can go
        if (ArePointAndBordersFree(maze, x - 1, y, x, y)) buffer.emplace_back(std::pair(x - 1, y));
        if (ArePointAndBordersFree(maze, x, y - 1, x, y)) buffer.emplace_back(std::pair(x, y - 1));
        if (ArePointAndBordersFree(maze, x + 1, y, x, y)) buffer.emplace_back(std::pair(x + 1, y));
        if (ArePointAndBordersFree(maze, x, y + 1, x, y)) buffer.emplace_back(std::pair(x, y + 1));
        if (buffer.empty()) continue;
        //choose random point
        int random_point = rand() % buffer.size();
        FillMaze(maze, buffer[random_point].first, buffer[random_point].second);
    } while (!buffer.empty());
}

void PrintMaze(std::vector<std::vector<int>>& maze) {
    for (auto& a : maze) {
        for (auto& elem : a) {
            if (elem) std::cout << '_';
            else std::cout << '*';
        }
        std::cout << '\n';
    }
}

std::vector<std::vector<int>> GetMaze(int length, int width) {
    std::vector<std::vector<int>> maze(length, std::vector<int>(width));
    FillMaze(maze, 0, 0);
    return maze;
}
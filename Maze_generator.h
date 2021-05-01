//
// Created by asmekal on 01.05.2021.
//

//to generate maze use fill_maze(0, 0)

#include<iostream>
#include<vector>

#ifndef TAURMAZE_MAZE_GENERATOR_H
#define TAURMAZE_MAZE_GENERATOR_H

#endif //TAURMAZE_MAZE_GENERATOR_H

bool is_free(std::vector<std::vector<int>>& maze, int x, int y) {
    return x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && !maze[x][y];
}

bool can_go(std::vector<std::vector<int>>& maze, int x, int y) {
    return x < 0 || y < 0 || x >= maze.size() || y >= maze[0].size() || !maze[x][y];
}

bool are_point_and_borders_free(std::vector<std::vector<int>>& maze, int x, int y, int px, int py) {
    //check point
    if (!is_free(maze, x, y)) return false;
    //check borders
    if (!can_go(maze, x - 1, y) && x - 1 != px) return false;
    if (!can_go(maze, x, y - 1) && y - 1 != py) return false;
    if (!can_go(maze, x + 1, y) && x + 1 != px) return false;
    if (!can_go(maze, x, y  + 1) && y + 1 != py) return false;
    return true;
}

void fill_maze(std::vector<std::vector<int>>& maze, int x, int y) {
    maze[x][y] = 1;
    std::vector<std::pair<int, int>> buffer;
    do {
        buffer.clear();
        //check if we can go
        if (are_point_and_borders_free(maze, x - 1, y, x, y)) buffer.emplace_back(std::pair(x - 1, y));
        if (are_point_and_borders_free(maze, x, y - 1, x, y)) buffer.emplace_back(std::pair(x, y - 1));
        if (are_point_and_borders_free(maze, x + 1, y, x, y)) buffer.emplace_back(std::pair(x + 1, y));
        if (are_point_and_borders_free(maze, x, y + 1, x, y)) buffer.emplace_back(std::pair(x, y + 1));
        if (buffer.empty()) continue;
        //choose random point
        int random_point = rand() % buffer.size();
        fill_maze(maze, buffer[random_point].first, buffer[random_point].second);
    } while (!buffer.empty());
}

void print_maze(std::vector<std::vector<int>>& maze) {
    for (auto& a : maze) {
        for (auto& elem : a) {
            if (elem) std::cout << '_';
            else std::cout << '*';
        }
        std::cout << '\n';
    }
}
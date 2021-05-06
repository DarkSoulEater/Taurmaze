//
// Created by Shuringan on 01.05.2021.
//
#pragma once

#ifndef TAURMAZE_MAZE_H
#define TAURMAZE_MAZE_H

#include <iostream>
#include <vector>
#include <random>

namespace Maze {
    std::vector<std::vector<int>> generate(int height, int width, int seed);

    void Print();

    bool IsFree(int x, int y);

    bool CanGo(int x, int y);

    bool ArePointAndBordersFree(int x, int y, int px, int py);

    void FillMaze(int x, int y);
};

#endif //TAURMAZE_MAZE_H
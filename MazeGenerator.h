//
// Created by asmekal on 01.05.2021.
//

//to create maze__ use GetMaze(length, width)

#include <iostream>
#include <vector>
#include <random>

#ifndef TAURMAZE_MAZE_GENERATOR_H
#define TAURMAZE_MAZE_GENERATOR_H

#endif //TAURMAZE_MAZE_GENERATOR_H

class Maze{
public:
    Maze(int height, int width){
        maze__.resize(height, std::vector<int>(width));
        gen__.seed(rng__());
        FillMaze(0, 0);
    }

    void Print(){
        for (auto& a : maze__) {
            for (auto& elem : a) {
                if (elem) std::cout << '_';
                else std::cout << '*';
            }
            std::cout << '\n';
        }
    }
private:
    std::vector<std::vector<int>> maze__;
    //for random
    std::random_device rng__;
    std::mt19937 gen__;
    std::uniform_int_distribution<> dist__;

    bool IsFree(int x, int y) {
        return x >= 0 && y >= 0 && x < maze__.size() && y < maze__[0].size() && !maze__[x][y];
    }

    bool CanGo(int x, int y) {
        return x < 0 || y < 0 || x >= maze__.size() || y >= maze__[0].size() || !maze__[x][y];
    }

    bool ArePointAndBordersFree(int x, int y, int px, int py) {
        //check point
        if (!IsFree(x, y)) return false;
        //check borders
        if (!CanGo(x - 1, y) && x - 1 != px) return false;
        if (!CanGo(x, y - 1) && y - 1 != py) return false;
        if (!CanGo(x + 1, y) && x + 1 != px) return false;
        if (!CanGo(x, y + 1) && y + 1 != py) return false;
        return true;
    }

    void FillMaze(int x, int y) {
        maze__[x][y] = 1;
        std::vector<std::pair<int, int>> buffer;
        do {
            buffer.clear();
            //check if we can go
            if (ArePointAndBordersFree(x - 1, y, x, y)) buffer.emplace_back(std::pair(x - 1, y));
            if (ArePointAndBordersFree(x, y - 1, x, y)) buffer.emplace_back(std::pair(x, y - 1));
            if (ArePointAndBordersFree(x + 1, y, x, y)) buffer.emplace_back(std::pair(x + 1, y));
            if (ArePointAndBordersFree(x, y + 1, x, y)) buffer.emplace_back(std::pair(x, y + 1));
            if (buffer.empty()) continue;
            //choose random point
            int random_point = dist__(gen__) % static_cast<int>(buffer.size());
            FillMaze(buffer[random_point].first, buffer[random_point].second);
        } while (!buffer.empty());
    }
};
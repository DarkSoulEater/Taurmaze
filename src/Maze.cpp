#include <iostream>
#include <vector>
#include "Maze.h"

namespace Maze{
    std::vector<std::vector<int>> maze_;

    std::vector<std::vector<int>> generate(int height, int width, unsigned int seed){
        maze_.clear();
        maze_.resize(height, std::vector<int>(width));
        srand(seed);
        FillMaze(0, 0);
        return maze_;
    }

    void Print(){
        for (auto& a : maze_) {
            for (auto& elem : a) {
                if (elem) std::cout << '_';
                else std::cout << '*';
            }
            std::cout << '\n';
        }
    }

    bool IsFree(int x, int y) {
        return x >= 0 && y >= 0 && x < maze_.size() && y < maze_[0].size() && !maze_[x][y];
    }

    bool CanGo(int x, int y) {
        return x < 0 || y < 0 || x >= maze_.size() || y >= maze_[0].size() || !maze_[x][y];
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
        maze_[x][y] = 1;
        std::vector<std::pair<int, int>> buffer;
        do {
            buffer.clear();
            // check if we can go
            if (ArePointAndBordersFree(x - 1, y, x, y)) buffer.emplace_back(std::pair(x - 1, y));
            if (ArePointAndBordersFree(x, y - 1, x, y)) buffer.emplace_back(std::pair(x, y - 1));
            if (ArePointAndBordersFree(x + 1, y, x, y)) buffer.emplace_back(std::pair(x + 1, y));
            if (ArePointAndBordersFree(x, y + 1, x, y)) buffer.emplace_back(std::pair(x, y + 1));
            if (buffer.empty()) continue;
            // choose random point
            int random_point = rand() % static_cast<int>(buffer.size());
            FillMaze(buffer[random_point].first, buffer[random_point].second);
        } while (!buffer.empty());
    }
}
//
// Created by Shuringan on 01.05.2021.
//

#include <iostream>
#include <vector>
#include <random>

#ifndef TAURMAZE_MAZE_H
#define TAURMAZE_MAZE_H

#endif //TAURMAZE_MAZE_H

class Maze{
public:
	Maze(int height, int width){ // NOLINT(cert-msc51-cpp)
		maze.resize(height, std::vector<int>(width));
		gen.seed(rng());
		FillMaze(0, 0);
	}

	void Print(){
		for (auto& a : maze) {
			for (auto& elem : a) {
				if (elem) std::cout << '_';
				else std::cout << '*';
			}
			std::cout << '\n';
		}
	}
private:
	[[maybe_unused]] std::vector<std::vector<int>> maze;
	//for random
	[[maybe_unused]] std::random_device rng;
	[[maybe_unused]] std::mt19937 gen;
	[[maybe_unused]] std::uniform_int_distribution<> dist;

	bool IsFree(int x, int y) {
		return x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && !maze[x][y];
	}

	bool CanGo(int x, int y) {
		return x < 0 || y < 0 || x >= maze.size() || y >= maze[0].size() || !maze[x][y];
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
		maze[x][y] = 1;
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
			int random_point = dist(gen) % static_cast<int>(buffer.size());
			FillMaze(buffer[random_point].first, buffer[random_point].second);
		} while (!buffer.empty());
	}
};
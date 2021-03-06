#include "maze.h"
#include <random>
#include <algorithm>

namespace maze {
static bool IsFree(std::vector<std::vector<int>>& maze_, int x, int y) {
  return x >= 0 && y >= 0 && x < maze_.size() && y < maze_[0].size() && !maze_[x][y];
}

static bool CanGo(std::vector<std::vector<int>>& maze_, int x, int y) {
  return x < 0 || y < 0 || x >= maze_.size() || y >= maze_[0].size() || !maze_[x][y];
}

static bool ArePointAndBordersFree(std::vector<std::vector<int>>& maze_, int x, int y, int px, int py) {
  //check point
  if (!IsFree(maze_, x, y)) return false;
  //check borders
  if (!CanGo(maze_, x - 1, y) && x - 1 != px) return false;
  if (!CanGo(maze_, x, y - 1) && y - 1 != py) return false;
  if (!CanGo(maze_, x + 1, y) && x + 1 != px) return false;
  if (!CanGo(maze_, x, y + 1) && y + 1 != py) return false;
  return true;
}

static std::vector<std::pair<int, int>> random_scale;

void AddItem(int item, int scale){
  if(!random_scale.empty()) {
    random_scale.emplace_back(std::make_pair(item, scale + random_scale.back().second));
  } else {
    random_scale.emplace_back(std::make_pair(item, scale));
  }
}

static int GetItem(int scale){
  int l = 0, r = static_cast<int>(random_scale.size());
  while(l + 1 < r){
    int m = l  + r >> 1;
    if(random_scale[m].second <= scale){
      l = m;
    } else{
      r = m;
    }
  }
  return random_scale[l].first;
}

static void FillMaze(std::vector<std::vector<int>>& maze_, int x, int y) {
  int scale = rand() % (random_scale.back().second + 1);
  int item = GetItem(scale);
  maze_[x][y] = item;
  std::vector<std::pair<int, int>> buffer;
  do {
    buffer.clear();
    // check if we can go
    if (ArePointAndBordersFree(maze_, x - 1, y, x, y)) buffer.emplace_back(std::pair(x - 1, y));
    if (ArePointAndBordersFree(maze_, x, y - 1, x, y)) buffer.emplace_back(std::pair(x, y - 1));
    if (ArePointAndBordersFree(maze_, x + 1, y, x, y)) buffer.emplace_back(std::pair(x + 1, y));
    if (ArePointAndBordersFree(maze_, x, y + 1, x, y)) buffer.emplace_back(std::pair(x, y + 1));
    if (buffer.empty()) continue;
    // choose random point
    int random_point = rand() % static_cast<int>(buffer.size());
    FillMaze(maze_, buffer[random_point].first, buffer[random_point].second);
  } while (!buffer.empty());
}

static void AddCycles(std::vector<std::vector<int>>& maze_, int cycle_regulator = 1){
  for(unsigned int i = 0; i < maze_.size(); ++i){
    for(unsigned int j = 0; j < maze_[i].size(); ++j){
      if(!maze_[i][j] && rand() % 10 <= cycle_regulator){
        int scale = rand() % (random_scale.back().second + 1);
        int item = GetItem(scale);
        maze_[i][j] = item;
      }
    }
  }
}

std::vector<std::vector<int>> Generate(int height, int width, unsigned int seed){
  srand(seed);
  std::vector<std::vector<int>> maze(height, std::vector<int>(width));
  FillMaze(maze, 0, 0);
  AddCycles(maze);
  return maze;
}
} // namespace
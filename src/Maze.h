#ifndef TAURMAZE_MAZE_H
#define TAURMAZE_MAZE_H

#include <vector>

namespace maze {
std::vector<std::vector<int>> Generate(int height, int width, unsigned int seed);

void AddItem(int item, int scale);
}; //namespace

#endif //TAURMAZE_MAZE_H
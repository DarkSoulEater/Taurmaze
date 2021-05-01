#include <iostream>
#include "MazeGenerator.h"

int main() {
    std::vector<std::vector<int>> maze = GetMaze(100, 100);
    PrintMaze(maze);
    return 0;
}

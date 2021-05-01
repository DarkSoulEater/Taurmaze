#include <iostream>
#include "MazeGenerator.h"

int main() {
    std::vector<std::vector<int>> maze = GetMaze(30, 30);
    PrintMaze(maze);
    return 0;
}

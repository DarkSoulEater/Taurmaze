#include <iostream>
#include "MazeGenerator.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<std::vector<int>> maze = GetMaze(30, 30);
    PrintMaze(maze);
    return 0;
}

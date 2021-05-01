#include <iostream>
#include "Maze_generator.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<std::vector<int>> maze(30, std::vector<int>(30));
    FillMaze(maze, 0, 0);
    PrintMaze(maze);
    return 0;
}

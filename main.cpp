#include "MazeGenerator.h"

int main() {
    std::vector<std::vector<int>> maze = GetMaze(69, 69);
    PrintMaze(maze);
    return 0;
}

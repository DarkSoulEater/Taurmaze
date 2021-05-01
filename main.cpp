#include "MazeGenerator.h"

int main() {
    std::vector<std::vector<int>> maze = GetMaze(17, 17);
    PrintMaze(maze);
    return 0;
}

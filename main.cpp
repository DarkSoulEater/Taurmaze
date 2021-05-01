#include <iostream>
#include "Maze_generator.h"

int main() {
    std::vector<std::vector<int>> maze(10, std::vector<int>(10));
    fill_maze(maze, 0, 0);
    print_maze(maze);
    return 0;
}

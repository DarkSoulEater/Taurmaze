//
// Created by Елизавета Манжула on 01.05.2021.
//

#pragma once
#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H
#include "Maze.h"

class Grid {
public:
    int Cx = 1000;
    int Cy = 800;
    int dx = 100;
    int dy = 100;
    int scale_velocity_x = 2;
    int scale_velocity_y = 2;
    int move_velocity_x = 10;
    int move_velocity_y = 10;
    int maze_size = 10;
    sf::Color grid_color = sf::Color::Blue;
    sf::Color cells_color = sf::Color::Black;
    float cells_thickness = 4.f;

    void Build(sf::RenderWindow& window);
    void BuildCells(sf::RenderWindow& window, Maze maze);

    sf::Vector2f GetPoint(sf::Vector2i node);
    sf::Vector2f GetSize(sf::Vector2i node);

    void MoveCenter(sf::Vector2i pos);
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void MoveUp();

    void ScaleBigger();
    void ScaleSmaller();

};

#endif //UNTITLED_GRID_H

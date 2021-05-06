//
// Created by Елизавета Манжула on 01.05.2021.
//

#pragma once

#ifndef TAURMAZE_GRID_H_
#define TAURMAZE_GRID_H_
#include "Maze.h"
#include "SFML/Graphics.hpp"
#include "core/Object.h"

class Cell : public Object {
public:
    Cell(int _i, int _j) {
        i = _i;
        j = _j;
    }
    int i;
    int j;
    int dx;
    int dy;
    sf::Vector2f pos;
    sf::Color color = sf::Color::Yellow;
    sf::Color selected = sf::Color::Green;

    Cell(int _i, int _j, int _dx, int _dy, sf::Vector2f _pos, sf::Color _color) {
        i = _i;
        j = _j;
        dx = _dx;
        dy = _dy;
        pos = _pos;
        color = _color;
    }

    bool IsClicked(sf::Vector2i mouse);

    void Build(sf::RenderWindow& window);

    void ChangeColor();

};

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
    int maze_size = 20;
    sf::Color grid_color = sf::Color::Blue;
    sf::Color cells_color = sf::Color::Black;
    float cells_thickness = 4.f;

    std::vector<std::vector<Cell> > cells;
    void SetCells(std::vector<std::vector<int>>& maze);
    void ChangeCells();

    void Build(sf::RenderWindow& window);
    void BuildCells();

    sf::Vector2f GetPoint(sf::Vector2i node);
    sf::Vector2f GetSize(sf::Vector2i node);

    void MoveCenter(sf::Vector2i pos);
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void MoveUp();

    void ScaleBigger();
    void ScaleSmaller();

    void ChangeColor(sf::Vector2i mouse);
};

#endif //UNTITLED_GRID_H

//
// Created by Елизавета Манжула on 01.05.2021.
//

#pragma once

#include <iostream>
#include "Grid.h"
#include "Maze.h"

void Cell::Build(sf::RenderWindow& window) {
    sf::RectangleShape cell(sf::Vector2f(dx, dy));
    cell.move(pos);
    cell.setFillColor(color);
    window.draw(cell);
}

bool Cell::IsClicked(sf::Vector2i mouse) {
    return (pos.x + dx >= mouse.x && pos.x <= mouse.x) && (pos.y + dy >= mouse.y && pos.y <= mouse.y);
}

void Cell::ChangeColor() {
    color = selected;
}

void Grid::Build(sf::RenderWindow& window) {
    for (int x = Cx; x > 50; x -= dx) {
        sf::RectangleShape line(sf::Vector2f(4.f, 1550.f));
        line.setFillColor(grid_color);
        line.move(x, 50);
        window.draw(line);

        std::string s = std::to_string((x - Cx) / dx);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(x - 8, 0);
        window.draw(num);
    }
    for (int x = Cx; x < 2000; x += dx) {
        sf::RectangleShape line(sf::Vector2f(4.f, 1550.f));
        line.setFillColor(grid_color);
        line.move(x, 50);
        window.draw(line);

        std::string s = std::to_string((x - Cx) / dx);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(x - 8, 0);
        window.draw(num);
    }
    for (int y = Cy; y > 50; y -= dy) {
        sf::RectangleShape line(sf::Vector2f(1950.f, 4.f));
        line.setFillColor(grid_color);
        line.move(50, y);
        window.draw(line);

        std::string s = std::to_string(-(y - Cy) / dy);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(9, y - 15);
        window.draw(num);
    }
    for (int y = Cy; y < 1600; y += dy) {
        sf::RectangleShape line(sf::Vector2f(1950.f, 4.f));
        line.setFillColor(grid_color);
        line.move(50, y);
        window.draw(line);

        std::string s = std::to_string(-(y - Cy) / dy);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(9, y - 15);
        window.draw(num);
    }
}

void Grid::SetCells(std::vector<std::vector<int>>& maze) {
    Cell c(0, 0, 0, 0, sf::Vector2f(0, 0), sf::Color::Black);
    cells.assign(maze_size, std::vector<Cell> (maze_size, c));
    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            sf::Color temp_col = sf::Color::Black;
            if (maze[i][j]) temp_col = sf::Color::Yellow;
            Cell cell(i, j, dx, dy, GetPoint({i, j}), temp_col);
            cells[i][j] = cell;

        }
    }
}


void Grid::ChangeCells() {
    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            cells[i][j].dx = dx;
            cells[i][j].dy = dy;
            cells[i][j].pos = GetPoint({i, j});
        }
    }
}


void Grid::BuildCells() {

    std::vector<std::vector<int> > cur_maze = Maze::generate(10, 10, 0);
    Maze::Print();
   int sz = cur_maze.size();
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j){
            Cell cur_cell(i, j);
            sf::Vector2f pos(i * dx, j * dy);
            cur_cell.SetSpritePosition(pos);
        }
    }
}


sf::Vector2f Grid::GetPoint(sf::Vector2i node) {
    int x = node.x;
    int y = node.y;
    float x_wind = x * dx + Cx - dx / 2.0;
    float y_wind = - y * dy + Cy - dy / 2.0;
    return {x_wind, y_wind};
}

sf::Vector2f Grid::GetSize(sf::Vector2i node) {
    return {float(dx), float(dy)};
}

void Grid::MoveCenter(sf::Vector2i pos) {
    Cx = pos.x;
    Cy = pos.y;
}

void Grid::MoveLeft() {
    Cx += move_velocity_x;
}

void Grid::MoveRight() {
    Cx -= move_velocity_x;
}

void Grid::MoveDown() {
    Cy -= move_velocity_y;
}

void Grid::MoveUp() {
    Cy += move_velocity_y;
}

void Grid::ScaleBigger() {
    dx += scale_velocity_x;
    dy += scale_velocity_y;
}

void Grid::ScaleSmaller() {
    dx -= scale_velocity_x;
    dy -= scale_velocity_y;
}

void Grid::ChangeColor(sf::Vector2i mouse) {
    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            if (cells[i][j].IsClicked(mouse)) {
                cells[i][j].ChangeColor();
                return;
            }
        }
    }

}
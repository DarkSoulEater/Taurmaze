//
// Created by Елизавета Манжула on 01.05.2021.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"

void Grid::Build(sf::RenderWindow& window) {
    for (int x = Cx; x > 50; x -= dx) {
        sf::RectangleShape line(sf::Vector2f(4.f, 1550.f));
        line.setFillColor(color);
        line.move(x, 50);
        window.draw(line);

        std::string s = std::to_string((x - Cx) / dx);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(color);
        num.move(x - 8, 0);
        window.draw(num);
    }
    for (int x = Cx; x < 2000; x += dx) {
        sf::RectangleShape line(sf::Vector2f(4.f, 1550.f));
        line.setFillColor(color);
        line.move(x, 50);
        window.draw(line);

        std::string s = std::to_string((x - Cx) / dx);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(color);
        num.move(x - 8, 0);
        window.draw(num);
    }
    for (int y = Cy; y > 50; y -= dy) {
        sf::RectangleShape line(sf::Vector2f(1950.f, 4.f));
        line.setFillColor(color);
        line.move(50, y);
        window.draw(line);

        std::string s = std::to_string(-(y - Cy) / dy);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(color);
        num.move(9, y - 15);
        window.draw(num);
    }
    for (int y = Cy; y < 1600; y += dy) {
        sf::RectangleShape line(sf::Vector2f(1950.f, 4.f));
        line.setFillColor(color);
        line.move(50, y);
        window.draw(line);

        std::string s = std::to_string(-(y - Cy) / dy);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(color);
        num.move(9, y - 15);
        window.draw(num);
    }
}

sf::Vector2f Grid::GetPoint(sf::Vector2i node) {
    int x = node.x;
    int y = node.y;
    float x_wind = x * dx + Cx;
    float y_wind = - y * dy + Cy;
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
    Cx -= move_velocity_x;
}

void Grid::MoveRight() {
    Cx += move_velocity_x;
}

void Grid::MoveDown() {
    Cy += move_velocity_y;
}

void Grid::MoveUp() {
    Cy -= move_velocity_y;
}

void Grid::ScaleBigger() {
    dx += scale_velocity_x;
    dy += scale_velocity_y;
}

void Grid::ScaleSmaller() {
    dx -= scale_velocity_x;
    dy -= scale_velocity_y;
}
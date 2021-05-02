//
// Created by Елизавета Манжула on 01.05.2021.
//

#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H

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
    sf::Color color = sf::Color::Black;
    void Build(sf::RenderWindow& window);
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

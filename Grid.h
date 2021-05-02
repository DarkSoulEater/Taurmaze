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
    sf::Color color = sf::Color::Black;
    void Build(sf::RenderWindow& window);
    sf::Vector2f GetPoint(sf::Vector2i node);
    void move(sf::Vector2i pos);
};

#endif //UNTITLED_GRID_H

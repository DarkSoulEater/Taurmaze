#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Grid.h"
#include "Maze.h"
#include "Core.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 1600), "SFML works!");

    Grid cur_grid;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pos = sf::Mouse::getPosition(window);
        cur_grid.move(pos);

        window.clear(sf::Color::White);

        cur_grid.Build(window);

        window.display();
    }

    return 0;
}
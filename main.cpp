#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Grid.h"
#include "Maze.h"
#include "Core.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 1600), "Taurmaze");

    Grid cur_grid;
    Maze cur_maze(cur_grid.maze_size, cur_grid.maze_size);
    cur_maze.Print();
    cur_grid.SetCells(cur_maze);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    cur_grid.ScaleBigger();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    cur_grid.ScaleSmaller();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    cur_grid.MoveLeft();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    cur_grid.MoveRight();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    cur_grid.MoveDown();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    cur_grid.MoveUp();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                cur_grid.ChangeColor(sf::Mouse::getPosition(window));
            }
        }

        sf::Vector2i pos = sf::Mouse::getPosition(window);
        //cur_grid.MoveCenter(pos);

        window.clear(sf::Color::White);

        cur_grid.Build(window);
        cur_grid.BuildCells(window);

        window.display();
    }

    return 0;
}
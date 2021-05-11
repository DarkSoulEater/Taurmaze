#ifndef TAURMAZE_GRID_H_
#define TAURMAZE_GRID_H_

#include "SFML/Graphics.hpp"
#include "core/Object.h"
#include "Player.h"

class Grid;

class Cell : public Object {
public:
  Cell(int x, int y, Grid &grid);

  sf::Vector2i position_;

  const Grid &grid_;
};

struct LevelOption {
  int width = 15;
  int height = 15;
  unsigned int seed = 0;

  uint32_t player_count = 1;
};

class Grid : public Object {
public:
  void Update() override;

  void Draw(sf::RenderWindow &) override;

  void CreateLevel(LevelOption);

  void DestroyLevel();

  sf::Vector2f ToWorldCoords(sf::Vector2i position);

  sf::Vector2i ToGridCoords(sf::Vector2f position);

 private:
  sf::Vector2i scale_ = {100, 100};
  std::vector<Cell*> cells_;
  std::vector<std::vector<int>> maze_;
  std::vector<Player*> players_;
};

#endif //UNTITLED_GRID_H

#ifndef TAURMAZE_GRID_H_
#define TAURMAZE_GRID_H_

#include "SFML/Graphics.hpp"
#include "core/Object.h"
#include "Player.h"
#include "settings.h"
#include <map>
#include "Buff.h"
#include <set>

class Grid;

class Cell : public Object {
public:
  Cell(int x, int y, Grid &grid);

  void Draw(sf::RenderWindow &) override;

  void SetPosition(const sf::Vector2f &position) override;

  void LastUpdate() override;

  void CreateBuff(BuffType type);

  sf::Vector2i position_;

  Buff* buff_ = nullptr;

  const Grid &grid_;

  struct {
    bool visibility = 0;
    bool on_way = 0;
    bool on_mouse = 0;
    std::set<int> undiscovered;
  } state_;

  int turn_ = 0;

 private:
  sf::RectangleShape shadow_shape_;
};

struct LevelOption {
  int width = 15;
  int height = 15;
  unsigned int seed = 0;

  uint32_t player_count = 2;
  uint32_t bot_count = 1;
};

class Grid : public Object {
public:
  void Update() override;

  void Draw(sf::RenderWindow &) override;

  void CreateLevel(LevelOption);

  void DestroyLevel();

  sf::Vector2f ToWorldCoords(sf::Vector2i position);

  sf::Vector2i ToGridCoords(sf::Vector2f position);

  Cell* GetCell(int x, int y);
  Cell* GetCell(sf::Vector2i coords);

  void NextTurn();

  void ToBattle(int first, int second);

  void KillPlayer(int i);

 private:
  sf::Vector2i scale_ = {int(settings::CellSize), int(settings::CellSize)};

  std::vector<Cell*> cells_;
  std::map<std::pair<int, int>, Cell*> cells_map_;
  std::vector<std::vector<int>> maze_;

  uint32_t turn_ = 0;
  std::vector<Player*> players_;
  std::vector<bool> is_bot_;

  std::vector<sf::Vector2i> GetWay(sf::Vector2i start, sf::Vector2i target);

  void Select();
};

#endif //UNTITLED_GRID_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include "Grid.h"
#include "maze.h"
#include "../util/input.h"
#include "../util/asset.h"

Cell::Cell(int x, int y, Grid& grid)
  : Object(asset::path::t_StoneCellTiles),
    position_({x, y}),
    grid_(grid),
    shadow_shape_({settings::CellSize, settings::CellSize}) {

  int texture_rect_id = rand() % 16;
  SetTextureRect(sf::Rect<int>(
       118 * (texture_rect_id % 4),
       118 * (texture_rect_id / 4),
      118, 118));
  sprite_.setScale({settings::CellSize / 118, settings::CellSize / 118});

  shadow_shape_.setOrigin(settings::CellSize / 2, settings::CellSize / 2);
  shadow_shape_.setPosition(sprite_.getPosition());
  shadow_shape_.setFillColor(sf::Color(0, 0, 0, 180));

  on_way.setTexture(asset::LoadTexture(asset::path::t_OnWayCell));
  on_way.setOrigin(settings::CellSize / 2, settings::CellSize / 2);
}

void Cell::Draw(sf::RenderWindow & window) {
  if (!settings::IsDebug && !state_.undiscovered.count(turn_)) return;
  Object::Draw(window);

  if (state_.visibility == 0) {
    window.draw(shadow_shape_);
  } else {
    if (buff_ && !settings::DAlwaysDrawBuffs) buff_->Draw(window);
    if (state_.on_way) {
      window.draw(on_way);
    }
    if (state_.on_mouse) {

    }
  }

  if (buff_ && settings::DAlwaysDrawBuffs) buff_->Draw(window);
}

void Cell::SetPosition(const sf::Vector2f &position) {
  Object::SetPosition(position);
  shadow_shape_.setPosition(position);
  on_way.setPosition(sprite_.getPosition());
}

void Cell::LastUpdate() {
  state_.visibility = false;
  state_.on_mouse = false;
  state_.on_way = false;
}

void Cell::CreateBuff(BuffType type) {
  buff_ = Buff::CreateBuff(type, 5.0f);
  buff_->SetPosition(sprite_.getPosition());
}

namespace sf {
bool operator<(sf::Vector2i a, sf::Vector2i b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}
}

void Grid::Update() {
  for (auto cell: cells_) {
    cell->turn_ = turn_;
  }

  // Apply Buff
  Cell* player_cell = GetCell(players_[turn_]->GetCoords());
  if (player_cell && player_cell->buff_) {
    player_cell->buff_->Apply(*players_[turn_]);
    delete player_cell->buff_;
    player_cell->buff_ = nullptr;
  }

  // Battle
  for (int i = 0; i < players_.size(); ++i) {
    if (!players_[i] || i == turn_) continue;
    if (players_[i]->GetCoords() == players_[turn_]->GetCoords()) {
      ToBattle(turn_, i);
      return;
    }
  }

  // Cell under mouse
  auto cell_mouse = GetCell(ToGridCoords(input::GetMouseWorldPosition()));
  if (cell_mouse) cell_mouse->state_.on_mouse = true;

  // Player logic
  if (!is_bot_[turn_]) {
    players_[turn_]->SetDrawable(true);
    Select();

    for (int i = 0; i < players_.size(); ++i) {
      if (!players_[i] || i == turn_) continue;
      auto pos = players_[i]->GetCoords();
      if (abs(pos.x - players_[turn_]->GetCoords().x) + abs(pos.y - players_[turn_]->GetCoords().y) <= players_[turn_]->GetVision()) {
        players_[i]->SetDrawable(true);
      }
    }

    if (!players_[turn_]->InMove()) {
      sf::Vector2i target = ToGridCoords(input::GetMouseWorldPosition());
      auto way = GetWay(players_[turn_]->GetCoords(), target);
      if (!way.empty() && way.size() <= move_range_) {
        for (auto& cell_coords : way) {
          auto cell = GetCell(cell_coords);
          if (cell) cell->state_.on_way = true;
        }
        if (input::GetKeyDown(input::KeyCode::MOUSE_0)) {
          move_range_ -= way.size();
          std::vector<sf::Vector2f> targets;
          for (auto point : way) {
            targets.push_back(ToWorldCoords(point));
          }
          players_[turn_]->SetTargets(targets);
        }
      }

      if (input::GetKeyDown(input::KeyCode::SPACE)) {
        NextTurn();
      }
    }
  } else {
    // Bot logic
    if (settings::DDrawBotTurn) {
      players_[turn_]->SetDrawable(true);
      Select();

      for (int i = 0; i < players_.size(); ++i) {
        if (!players_[i] || i == turn_) continue;
        auto pos = players_[i]->GetCoords();
        if (abs(pos.x - players_[turn_]->GetCoords().x) + abs(pos.y - players_[turn_]->GetCoords().y) <= players_[turn_]->GetVision()) {
          players_[i]->SetDrawable(true);
        }
      }
    }

    if (!players_[turn_]->InMove()) {
      if (move_range_ == 0) {
        NextTurn();
        return;
      }

      std::set<std::pair<int, sf::Vector2i>> targets;
      sf::Vector2i pl_pos = players_[turn_]->GetCoords();

      int buff_point = 10;
      int strong_player_point = -1000;
      int weak_player_point = 1000;
      int fear_range = 10;
      int undisc = 10;

      std::set<sf::Vector2i> strong_players;
      std::set<sf::Vector2i> weak_players;
      for (int i = 0; i < players_.size(); ++i) {
        if (!players_[i] || i == turn_) continue;
        auto pos = players_[i]->GetCoords();
        if (abs(pos.x - players_[turn_]->GetCoords().x) + abs(pos.y - players_[turn_]->GetCoords().y) <= players_[turn_]->GetVision()) {
          if (ToBattle(turn_, i, false) == i) weak_players.insert(pos);
          else strong_players.insert(pos);
        }
      }

      int view_range = players_[turn_]->GetVision() + 2;
      std::map<sf::Vector2i, int> points;

      for (int y = -view_range; y <= view_range; ++y) {
        for (int x = -view_range; x <= view_range; ++x) {
          auto way = GetWay(players_[turn_]->GetCoords(), pl_pos + sf::Vector2i(x, y));
          if (way.empty()) continue;

          int point = 0;

          auto cell = GetCell(pl_pos + sf::Vector2i(x, y));
          if (!cell) continue;

          if (cell->state_.undiscovered.count(turn_) == 0) {
            point += undisc;
          }

          if (cell->buff_) {
            point += buff_point - abs(x) - abs(y);
          }

          if (weak_players.count(pl_pos + sf::Vector2i(x, y))) {
            point += weak_player_point - abs(x) - abs(y);
          }

          if (strong_players.count(pl_pos + sf::Vector2i(x, y))) {
            point += strong_player_point;
          }

          if (!strong_players.empty()) {
            point += (abs(pl_pos.x + x - strong_players.begin()->x)
                + abs(pl_pos.y + y - strong_players.begin()->y))
                * fear_range;
          }

          for (auto p : way) {
            points[p] += point;
          }
        }
      }

      for (const auto& p : points) {
        if (p.first == pl_pos + sf::Vector2i(0, 1)
        || p.first == pl_pos + sf::Vector2i(0, -1)
        || p.first == pl_pos + sf::Vector2i(1, 0)
        || p.first == pl_pos + sf::Vector2i(-1, 0))
          targets.insert({p.second, p.first});
      }

      std::cout << targets.rbegin()->second.x << " " << targets.rbegin()->second.x << std::endl;
      auto way = GetWay(players_[turn_]->GetCoords(), targets.rbegin()->second);

      if (!way.empty() && way.size() <= move_range_) {
          move_range_ -= way.size();
          //if (move_range_ < 0) move_range_ = 0;
          std::vector<sf::Vector2f> targets;
          //for (int i = std::min(int(move_range_ - 1), int(targets.size() - 1)); i >= 0; --i) {
          //  targets.push_back(ToWorldCoords(way[i]));
          //}
          for (auto point : way) {
            targets.push_back(ToWorldCoords(point));
            //if (targets.size() == move_range_) break;
          }
          players_[turn_]->SetTargets(targets);
      } else {
        std::cerr << "Error: not corect target cell for bot\n";
      }
    }
  }
}

void Grid::Draw(sf::RenderWindow &window) {
  if (!settings::DDrawCoordsGrid) return;
  sf::VertexArray line(sf::Lines, 2);
  line[0].color = sf::Color::Green;
  line[1].color = sf::Color::Green;

  int window_width = window.getSize().x;
  int window_height = window.getSize().y;
  int grid_size = 50;

  for (int i = -grid_size; i <= grid_size; ++i) {
    line[0].position = ToWorldCoords({i, -grid_size});
    line[1].position = ToWorldCoords({i, grid_size});
    window.draw(line);

    line[0].position = ToWorldCoords({-grid_size, i});
    line[1].position = ToWorldCoords({grid_size, i});
    window.draw(line);
  }
}

void Grid::CreateLevel(LevelOption option) {
  // Create logic maze
  maze::AddItem(1, settings::BuffQuantity); //tile
  maze::AddItem(2, 10); //health buff
  maze::AddItem(3, 10); //attack buff
  maze::AddItem(4, 10); //defence buff
  maze::AddItem(5, 10); //move_range buff
  maze::AddItem(6, 10); //vision buff

  maze_ = maze::Generate(option.height, option.width, option.seed);

  // Create physics maze
  uint64_t maze_width = maze_[0].size();
  uint64_t maze_height = maze_.size();

  for (size_t y = 0; y < maze_height; ++y) {
    for (size_t x = 0; x < maze_width; ++x){
      std::cout << maze_[y][x] << " ";
      if (maze_[y][x] > 0) {
        Cell* cell = new Cell(x, y, *this);
        cells_.push_back(cell);
        cells_map_[{x, y}] = cell;
        cell->SetPosition({float(x * scale_.x), float(y * scale_.y) });

        switch (maze_[y][x]) {
          case 2:
            cell->CreateBuff(BuffType::Health);
            break;
          case 3:
            cell->CreateBuff(BuffType::Attack);
            break;
          case 4:
            cell->CreateBuff(BuffType::Defence);
            break;
          case 5:
            cell->CreateBuff(BuffType::MoveRange);
            break;
          case 6:
            cell->CreateBuff(BuffType::Vision);
            break;
        }
      }
    }
    std::cout << "\n";
  }

  // Create players
  for (size_t i = 0; i < option.player_count; ++i) {
    Player* player = new Player(*this);
    players_.push_back(player);
    is_bot_.push_back(false);
    player->SetPosition(ToWorldCoords({0, 0}));
  }

  // Create bot
  for (size_t i = 0; i < option.bot_count; ++i) {
    Player* player = new Player(*this);
    player->SetTexture(asset::path::t_Minotaur);
    player->SetTextureRect(sf::IntRect(0,0,130,100));
    player->SetSize(settings::HeroesSize, settings::HeroesSize);
    player->SetHealthPoints(10);
    players_.push_back(player);
    is_bot_.push_back(true);
    player->SetPosition(ToWorldCoords({0, 0}));
  }

  while(true){
    bool ch = true;
    for(int i = 0; i < players_.size() && ch; ++i){
      for(int j = 0; j < players_.size() && ch; ++j){
        if(i == j) continue;
        if(abs(players_[i]->GetCoords().x - players_[j]->GetCoords().x) < 4 ||
           abs(players_[i]->GetCoords().y - players_[j]->GetCoords().y) < 4){
          ch = false;
        }
      }
    }
    if(ch) break;
    for(auto& player : players_){
      do {
        player->SetPosition(ToWorldCoords({static_cast<int>(rand() % maze_width), static_cast<int>(rand() % maze_height)}));
      } while(maze_[player->GetCoords().y][player->GetCoords().x] == 0);
    }
  }

  move_range_ = players_[turn_]->GetMoveRange();
}

void Grid::DestroyLevel() {
  for (size_t i = 0; i < cells_.size(); ++i) {
    delete cells_[i];
  }
  cells_.clear();

  for (size_t i = 0; i < maze_.size(); ++i) {
    maze_[i].clear();
  }
  maze_.clear();
}

sf::Vector2f Grid::ToWorldCoords(sf::Vector2i position) {
  return sf::Vector2f(position.x * scale_.x, position.y * scale_.y);
}

sf::Vector2i Grid::ToGridCoords(sf::Vector2f position) {
  return sf::Vector2i(roundf(position.x / scale_.x), roundf(position.y / scale_.y));
}

Cell *Grid::GetCell(int x, int y) {
  if (cells_map_.count({x, y})) return cells_map_[{x, y}];
  return nullptr;
}

Cell *Grid::GetCell(sf::Vector2i coords) {
  if (cells_map_.count({coords.x, coords.y})) return cells_map_[{coords.x, coords.y}];
  return nullptr;
}

std::vector<sf::Vector2i> Grid::GetWay(sf::Vector2i start, sf::Vector2i target) {
  std::vector<sf::Vector2i> way;

  std::map<Cell*, Cell*> parent;
  std::queue<std::tuple<int, int, int>> q;

  q.push(std::make_tuple(start.x, start.y, 0));
  while (!q.empty()) {
    int x, y, dst;
    std::tie(x, y, dst) = q.front();
    q.pop();

    if (target.x == x && target.y == y) {
      break;
    }

    Cell* cell, *now_cell = GetCell(x, y);
    if ((cell = GetCell(x + 1, y)) && parent.count(cell) == 0) {
      parent[cell] = now_cell;
      q.push(std::make_tuple(x + 1, y, dst + 1));
    }

    if ((cell = GetCell(x - 1, y)) && parent.count(cell) == 0) {
      parent[cell] = now_cell;
      q.push(std::make_tuple(x - 1, y, dst + 1));
    }

    if ((cell = GetCell(x, y + 1)) && parent.count(cell) == 0) {
      parent[cell] = now_cell;
      q.push(std::make_tuple(x, y + 1, dst + 1));
    }

    if ((cell = GetCell(x, y - 1)) && parent.count(cell) == 0) {
      parent[cell] = now_cell;
      q.push(std::make_tuple(x, y - 1, dst + 1));
    }
  }

  if (parent.count(GetCell(target)) == 0) {
    return way;
  }

  Cell* cell = GetCell(target);
  while (cell->position_ != start) {
    way.push_back(cell->position_);
    cell = parent[cell];
  }

  return way;
}

void Grid::Select() {
  int dist = players_[turn_]->GetVision();
  auto position = players_[turn_]->GetCoords();
  for (int y = -dist - 1; y <= dist + 1; ++y) {
    for (int x = -dist - 1; x <= dist + 1; ++x) {
      Cell* cell = GetCell(x + position.x, y + position.y);
      if (cell) {
        if (x * x + y * y <= dist * dist) cell->state_.visibility = true;
        if (x * x + y * y <= (dist + 1) * (dist + 1)) cell->state_.undiscovered.insert(turn_);
      }
    }
  }
}

void Grid::NextTurn() {
  do {
    turn_ = (turn_ + 1) % players_.size();
  } while (!players_[turn_]);
  move_range_ = players_[turn_]->GetMoveRange();
}

int Grid::ToBattle(int first, int second, bool kill) {
  int first_health = players_[first]->GetHealthPoints();
  int second_health = players_[second]->GetHealthPoints();
  int first_attack = players_[first]->GetAttack();
  int second_attack = players_[second]->GetAttack();
  int kill_id = second;
  for (;;) {
    second_health -= first_attack;
    if (second_health <= 0) {
      kill_id = second;
      break;
    }

    first_health -= second_attack;
    if (first_health <= 0) {
      kill_id = first;
      break;
    }
  }
 if (kill) KillPlayer(kill_id);
 return kill_id;
}

void Grid::KillPlayer(int i) {
  delete players_[i];
  players_[i] = nullptr;
  if (i == turn_) NextTurn();
}

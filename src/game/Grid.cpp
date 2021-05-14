#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include "Grid.h"
#include "maze.h"
#include "../util/input.h"
#include "settings.h"

Cell::Cell(int x, int y, Grid& grid) : Object("../assets/texture/default_cell.png"), position_({x, y}), grid_(grid) {}

void Cell::Draw(sf::RenderWindow & window) {
  if (state_.visibility == 0) {
    SetTexture("../assets/texture/default_cell.png");
  } else {
    SetTexture("../assets/texture/default_near_cell.png");
    if (state_.on_way) {
      //SetTexture();
    }
    if (state_.on_mouse) {
      SetTexture("../assets/texture/default_select_cell.png");
    }
  }

  Object::Draw(window);

  if (buff_) buff_->Draw(window);
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

void Grid::Update() {
  if (!is_bot_[turn_]) {
    Select();

    Cell* player_cell = GetCell(players_[turn_]->GetCoords());
    if (player_cell->buff_) {
      player_cell->buff_->Apply(*players_[turn_]);
      delete player_cell->buff_;
      player_cell->buff_ = nullptr;
    }

    static bool Moved = false;
    if (!players_[turn_]->InMove()) {
      if (Moved) {
        Moved = false;
        NextTurn();
      }

      if (input::GetKeyDown(input::KeyCode::MOUSE_0)) {
        sf::Vector2i target = ToGridCoords(input::GetMouseWorldPosition());
        auto way = GetWay(players_[turn_]->GetCoords(), target);
        if (!way.empty() && way.size() <= players_[turn_]->GetVision()) {
          Moved = true;
          std::vector<sf::Vector2f> targets;
          for (auto point : way) {
            targets.push_back(ToWorldCoords(point));
          }
          players_[turn_]->SetTargets(targets);
        }
      }
    } else {

    }
  }

  // TMP
  auto cell = GetCell(ToGridCoords(input::GetMouseWorldPosition()));
  if (cell) cell->state_.on_mouse = true;
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
  maze::AddItem(1, 10);
  maze::AddItem(2, 10);
  //maze::AddItem(3, 10);
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
        cell->SetSpritePosition({float(x * scale_.x), float(y * scale_.y) });

        if (maze_[y][x] > 1) {
          cell->CreateBuff(BuffType::None);
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
  int dist = players_[turn_]->GetSpeed();
  auto position = players_[turn_]->GetCoords();
  for (int y = -dist; y <= dist; ++y) {
    for (int x = -dist; x <= dist; ++x) {
      if (x * x + y * y > dist * dist) continue;
      Cell* cell = GetCell(x + position.x, y + position.y);
      if (cell) {
        cell->state_.visibility = true;
      }
    }
  }
}

void Grid::NextTurn() {
  turn_ = (turn_ + 1) % players_.size(); // TODO: IF DEAD
}

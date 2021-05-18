#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
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
}

void Cell::Draw(sf::RenderWindow & window) {
  Object::Draw(window);

  if (state_.visibility == 0) {
    window.draw(shadow_shape_);
  } else {
    if (buff_ && !settings::DAlwaysDrawBuffs) buff_->Draw(window);
    if (state_.on_way) {
      //SetTexture();
    }
    if (state_.on_mouse) {
      //SetTexture("../assets/texture/default_select_cell.png");
    }
  }

  if (buff_ && settings::DAlwaysDrawBuffs) buff_->Draw(window);
}

void Cell::SetPosition(const sf::Vector2f &position) {
  Object::SetPosition(position);
  shadow_shape_.setPosition(position);
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
  // Apply Buff
  Cell* player_cell = GetCell(players_[turn_]->GetCoords());
  if (player_cell->buff_) {
    player_cell->buff_->Apply(*players_[turn_]);
    delete player_cell->buff_;
    player_cell->buff_ = nullptr;
  }


  if (!is_bot_[turn_]) {
    Select();

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

  while(true){
    bool ch = 1;
    for(int i = 0; i < players_.size() && ch; ++i){
      for(int j = 0; j < players_.size() && ch; ++j){
        if(i == j) continue;
        if(abs(players_[i]->GetCoords().x - players_[j]->GetCoords().x) < 4 ||
           abs(players_[i]->GetCoords().y - players_[j]->GetCoords().y) < 4){
          ch = 0;
        }
      }
    }
    if(ch) break;
    for(auto& player : players_){
      do {
        player->SetPosition(ToWorldCoords({static_cast<int>(rand() % maze_height), static_cast<int>(rand() % maze_width)}));
      } while(maze_[player->GetCoords().x][player->GetCoords().y] == 0);
    }
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
  int dist = players_[turn_]->GetMoveRange();
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

void Grid::ToBattle(int ind_first_pl, int ind_second_pl) {
  // TODO: ADD BATTLE // DELETE IN PLAYERS_!!!
  std::cout << "Battle\n";
}

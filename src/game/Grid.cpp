#include <iostream>
#include <vector>
#include "Grid.h"
#include "maze.h"
#include "../util/input.h"

Cell::Cell(int x, int y, Grid& grid) : Object("../assets/texture/default_cell.png"), position_({x, y}), grid_(grid) {}

void Grid::Update() {
  if (input::GetKeyDown(input::KeyCode::E)) {
    std::vector<sf::Vector2f> targets{
        ToWorldCoords({1, 0}),
        ToWorldCoords({2, 0}),
        ToWorldCoords({3, 0}),
        ToWorldCoords({4, 0}),
        ToWorldCoords({4, 1}),
        ToWorldCoords({4, 2}),
        ToWorldCoords({5, 2})
    };
    std::reverse(targets.begin(), targets.end());
    players_[0]->SetTargets(targets);
  }
}

void Grid::Draw(sf::RenderWindow &) {

}

void Grid::CreateLevel(LevelOption option) {
  // Create logic maze
  maze::AddItem(1, 10);
  maze_ = maze::Generate(option.height, option.width, option.seed);

  // Create physics maze
  uint64_t maze_width = maze_[0].size();
  uint64_t maze_height = maze_.size();

  for (size_t i = 0; i < maze_height; ++i) {
    for (size_t j = 0; j < maze_width; ++j){
      if (maze_[j][i] == 1) {
        Cell* cell = new Cell(i, j, *this);
        cells_.push_back(cell);
        cell->SetSpritePosition({float(i * scale_.x), float(j * scale_.y) });
      }
    }
  }

  // Create players
  for (size_t i = 0; i < option.player_count; ++i) {
    Player* player = new Player;
    players_.push_back(player);
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
  return sf::Vector2i(0, 0); // TODO:
}

/*

bool Cell::IsClicked(sf::Vector2i mouse) {
    return (pos.x + dx >= mouse.x && pos.x <= mouse.x) && (pos.y + dy >= mouse.y && pos.y <= mouse.y);
}

void Cell::ChangeColor() {
    color = selected;
}

void Grid::Build(sf::RenderWindow& window) {
    for (int x = Cx; x > 50; x -= dx) {
        sf::RectangleShape line(sf::Vector2f(4.f, 1550.f));
        line.setFillColor(grid_color);
        line.move(x, 50);
        window.draw(line);

        std::string s = std::to_string((x - Cx) / dx);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(x - 8, 0);
        window.draw(num);
    }
    for (int x = Cx; x < 2000; x += dx) {
        sf::RectangleShape line(sf::Vector2f(4.f, 1550.f));
        line.setFillColor(grid_color);
        line.move(x, 50);
        window.draw(line);

        std::string s = std::to_string((x - Cx) / dx);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(x - 8, 0);
        window.draw(num);
    }
    for (int y = Cy; y > 50; y -= dy) {
        sf::RectangleShape line(sf::Vector2f(1950.f, 4.f));
        line.setFillColor(grid_color);
        line.move(50, y);
        window.draw(line);

        std::string s = std::to_string(-(y - Cy) / dy);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(9, y - 15);
        window.draw(num);
    }
    for (int y = Cy; y < 1600; y += dy) {
        sf::RectangleShape line(sf::Vector2f(1950.f, 4.f));
        line.setFillColor(grid_color);
        line.move(50, y);
        window.draw(line);

        std::string s = std::to_string(-(y - Cy) / dy);
        sf::Font temp_font;
        temp_font.loadFromFile("../assets/texture/19676.ttf");
        sf::Text num(s, temp_font, 40);
        num.setColor(grid_color);
        num.move(9, y - 15);
        window.draw(num);
    }
}

void Grid::SetCells(std::vector<std::vector<int>>& maze) {
    Cell c(0, 0, 0, 0, sf::Vector2f(0, 0), sf::Color::Black);
    cells.assign(maze_size, std::vector<Cell> (maze_size, c));
    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            sf::Color temp_col = sf::Color::Black;
            if (maze[i][j]) temp_col = sf::Color::Yellow;
            Cell cell(i, j, dx, dy, GetPoint({i, j}), temp_col);
            cells[i][j] = cell;

        }
    }
}


void Grid::BuildCells() {
  maze::AddItem(1, 10);
  std::vector<std::vector<int>> cur_maze = maze::Generate(30, 30, 0);
  int sz = cur_maze.size();
    for (int i = 0; i < sz; ++i) {
      for (int j = 0; j < sz; ++j){
        if (cur_maze[j][i] == 1) {
          Cell *cur_cell = new Cell(i, j);
          sf::Vector2f pos(i * dx, j * dy);
          cur_cell->SetSpritePosition(pos);
        }
      }
    }
}


sf::Vector2f Grid::GetPoint(sf::Vector2i node) {
    int x = node.x;
    int y = node.y;
    float x_wind = x * dx + Cx - dx / 2.0;
    float y_wind = - y * dy + Cy - dy / 2.0;
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
    Cx += move_velocity_x;
}

void Grid::MoveRight() {
    Cx -= move_velocity_x;
}

void Grid::MoveDown() {
    Cy -= move_velocity_y;
}

void Grid::MoveUp() {
    Cy += move_velocity_y;
}

void Grid::ScaleBigger() {
    dx += scale_velocity_x;
    dy += scale_velocity_y;
}

void Grid::ScaleSmaller() {
    dx -= scale_velocity_x;
    dy -= scale_velocity_y;
}

void Grid::ChangeColor(sf::Vector2i mouse) {
    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            if (cells[i][j].IsClicked(mouse)) {
                cells[i][j].ChangeColor();
                return;
            }
        }
    }

}*/
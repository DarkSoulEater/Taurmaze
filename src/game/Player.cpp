#include "Player.h"
#include "Grid.h"
#include "../util/asset.h"

Player::Player(Grid& grid) : Object("../assets/texture/purple_slime.png", 5), grid_(grid) {
  coords_ = grid_.ToGridCoords(sprite_.getPosition());

  //int texture_rect_id = 0;
  int texture_size = 100;
  //SetTextureRect(sf::Rect<int>(
  //    118 * (texture_rect_id % 10),
  //118 * (texture_rect_id / 10),
  //    118, 118));
  sprite_.setScale({settings::HeroesSize / texture_size, settings::HeroesSize / texture_size});
}

void Player::Update() {
  if (InMove()) {
    auto dir = *targets_.rbegin() - sprite_.getPosition();
    auto dir_len = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (dir_len <= 0.001f) {
      targets_.pop_back();
      return;
    }
    dir.x /= dir_len, dir.y /= dir_len;

    SetPosition(sprite_.getPosition() + dir * move_speed);
  }
  coords_ = grid_.ToGridCoords(sprite_.getPosition());
}

void Player::Draw(sf::RenderWindow &window) {
  /*
  sf::Texture tex(asset::LoadTexture("../assets/texture/perl.png"));
  sf::Image im = tex.copyToImage();
  auto sz = im.getSize();
  for (size_t j = 0; j < sz.y; ++j) {
    for (size_t i = 0; i < sz.x; ++i) {
      sf::Color col(im.getPixel(i, j));
      col.a = 100;
      im.setPixel(i, j, col * sf::Color(255, 238, 204));
    }
  }
  sf::Texture tex1;
  tex1.loadFromImage(im);
  sf::Sprite sp(tex1);
  sp.setPosition(100, 100);
  window.draw(sp);*/

  Object::Draw(window);

  if (settings::DDrawPlayerOrigin) {
    sf::CircleShape circle_shape;
    circle_shape.setRadius(10);
    circle_shape.setOrigin({5, 5});
    circle_shape.setFillColor(sf::Color::Red);
    circle_shape.setPosition(grid_.ToWorldCoords(coords_));
    window.draw(circle_shape);
  }
}

void Player::SetTargets(const std::vector<sf::Vector2f>& targets) {
  targets_ = targets;
}

bool Player::InMove() const {
  return !targets_.empty();
}

void Player::EndTurn() {
  // TODO:
}

int Player::GetHealthPoints() const {
  return health_points_;
}

void Player::SetHealthPoints(int new_health) {
  health_points_ = new_health;
}

int Player::GetAttack() const {
  return attack_;
};

void Player::SetAttack(int new_attack) {
  attack_ = new_attack;
}

int Player::GetDefence() const {
  return defence_;
}

void Player::SetDefence(int new_defence) {
  defence_ = new_defence;
}

int Player::GetSpeed() const {
  return move_range_;
}

void Player::SetSpeed(int new_speed) {
  move_range_ = new_speed;
}

int Player::GetVision() const {
  return vision_range_;
}

void Player::SetVision(int new_vision) {
  vision_range_ = new_vision;
}

sf::Vector2i Player::GetCoords() {
  return coords_;
}

#include "Player.h"
#include "Grid.h"

Player::Player(Grid& grid) : Object("../assets/texture/default_player.png", 5), grid_(grid) {
  coords_ = grid_.ToGridCoords(sprite_.getPosition());
}
#include "iostream"
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
    coords_ = grid_.ToGridCoords(sprite_.getPosition());
  }
}

void Player::Draw(sf::RenderWindow &window) {
  Object::Draw(window);

  sf::CircleShape circle_shape;
  circle_shape.setRadius(10);
  circle_shape.setFillColor(sf::Color::Red);
  circle_shape.setPosition(grid_.ToWorldCoords(coords_));
  window.draw(circle_shape);
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
  return health_points;
}

void Player::SetHealthPoints(int new_health) {
  health_points = new_health;
}

int Player::GetAttack() const {
  return attack;
};

void Player::SetAttack(int new_attack) {
  attack = new_attack;
}

int Player::GetDefence() const {
  return defence;
}

void Player::SetDefence(int new_defence) {
  defence = new_defence;
}

int Player::GetSpeed() const {
  return speed;
}

void Player::SetSpeed(int new_speed) {
  speed = new_speed;
}

int Player::GetVision() const {
  return vision;
}

void Player::SetVision(int new_vision) {
  vision = new_vision;
}

sf::Vector2i Player::GetCoords() {
  return coords_;
}

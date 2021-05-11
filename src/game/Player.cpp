#include "Player.h"

Player::Player() : Object("../assets/texture/default_player.png", 5) {

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
}

void Player::SetTargets(const std::vector<sf::Vector2f>& targets) {
  targets_ = targets;
}

bool Player::InMove() const {
  return !targets_.empty();
}

int Player::get_health_points() {
  return health_points;
}

int& Player::set_health_points() {
  return health_points;
}

int Player::get_defence() {
  return defence;
}

int& Player::set_defence() {
  return defence;
}

float Player::get_speed() {
  return speed;
}

float& Player::set_speed() {
  return speed;
}

int Player::get_vision() {
  return vision;
}

int& Player::set_vision() {
  return vision;
}

//void Player::Draw(sf::RenderWindow &) {

//}

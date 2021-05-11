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

int Player::GetHealthPoints() const {
  return health_points;
}

void Player::SetHealthPoints(int new_health) {
  health_points = new_health;
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

//void Player::Draw(sf::RenderWindow &) {

//}

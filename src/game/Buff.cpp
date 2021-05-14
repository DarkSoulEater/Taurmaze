#include "Buff.h"
#include "../util/asset.h"

void bf_DefaultEffect(Player& obj) {}
void bf_DefaultRollback(Player& obj) {}

Buff::Buff(const char *path) : sprite_(asset::LoadTexture(path)) {
  sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);
}

Buff* Buff::CreateBuff(BuffType type, float effect_time) {
  return new Buff(); // TODO
}


void Buff::Draw(sf::RenderWindow &window) {
  window.draw(sprite_);
}

void Buff::SetPosition(sf::Vector2f position) {
  sprite_.setPosition(position);
}

void Buff::Apply(Player& obj) {
  // TODO:
}

void Buff::SetEffect(std::function<void(Player &)> function) {
  effect_ = function;
}

void Buff::SetRollback(std::function<void(Player &)> function) {
  rollback_ = function;
}

void Buff::SetEffectTime(float time) {
  effect_time_ = time;
}

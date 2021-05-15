#include "Buff.h"
#include "../util/asset.h"

void bf_DefaultEffect(Player& obj) {}
void bf_DefaultRollback(Player& obj) {}

void bf_Health(Player& obj) {   //we need to discuss numbers of each effect
  obj.SetHealthPoints(obj.GetHealthPoints() + 1);
}

void bf_HealthRollback(Player& obj) {}

void bf_Attack(Player& obj){
  obj.SetAttack(obj.GetAttack() + 1);
}

void bf_AttackRollback(Player& obj){
  obj.SetAttack(obj.GetAttack() - 1);
}

void bf_Defence(Player& obj){
  obj.SetDefence(obj.GetDefence() + 1);
}

void bf_DefenceRollback(Player& obj){
  obj.SetDefence(obj.GetDefence() - 1);
}

void bf_Speed(Player& obj){
  obj.SetSpeed(obj.GetSpeed() + 1);
}

void bf_SpeedRollback(Player& obj){
  obj.SetSpeed(obj.GetSpeed() - 1);
}

void bf_Vision(Player& obj){
  obj.SetVision(obj.GetVision() + 1);
}

void bf_VisionRollback(Player& obj){
  obj.SetVision(obj.GetVision() - 1);
}


Buff::Buff(const char *path) : sprite_(asset::LoadTexture(path)) {
  sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);
}

Buff* Buff::CreateBuff(BuffType type, float effect_time) {
  Buff* buff;
  switch(type){
    case BuffType::None:
      buff = new Buff();
      break;
    case BuffType::Health:
      buff = new Buff("");  //path to health
      buff->effect_ = bf_Health;
      buff->rollback_ = bf_HealthRollback;
      break;
    case BuffType::Attack:
      buff = new Buff("");  //path to attack
      buff->effect_ = bf_Attack;
      buff->rollback_ = bf_AttackRollback;
      break;
    case BuffType::Defence:
      buff = new Buff(""); //path to defence
      buff->effect_ = bf_Defence;
      buff->rollback_ = bf_DefenceRollback;
      break;
    case BuffType::Speed:
      buff = new Buff("");  //path to speed
      buff->effect_ = bf_Speed;
      buff->rollback_ = bf_SpeedRollback;
      break;
    case BuffType::Vision:
      buff = new Buff("");  //path to vision
      buff->effect_ = bf_Vision;
      buff->rollback_ = bf_VisionRollback;
      break;
  }
  return buff;
}


void Buff::Draw(sf::RenderWindow &window) {
  window.draw(sprite_);
}

void Buff::SetPosition(sf::Vector2f position) {
  sprite_.setPosition(position);
}

void Buff::Apply(Player& obj) {
  bf_DefaultEffect(obj);
  // TODO CALLBACK
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

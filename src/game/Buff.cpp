#include "Buff.h"
#include "../util/asset.h"
#include "settings.h"

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

void bf_MoveRange(Player& obj){
  obj.SetMoveRange(obj.GetMoveRange() + 1);
}

void bf_MoveRangeRollback(Player& obj){
  obj.SetMoveRange(obj.GetMoveRange() - 1);
}

void bf_Vision(Player& obj){
  obj.SetVision(obj.GetVision() + 1);
}

void bf_VisionRollback(Player& obj){
  obj.SetVision(obj.GetVision() - 1);
}

Buff::Buff(const char *path) : sprite_(asset::LoadTexture(path)) {
  int texture_rect_id = rand() % 100;
  int texture_size = 50;

  sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);
  sprite_.setScale({settings::BuffSize / texture_size, settings::BuffSize / texture_size});
}

Buff* Buff::CreateBuff(BuffType type, float effect_time) {
  Buff* buff;
  switch(type){
    case BuffType::None:
      buff = new Buff("../assets/texture/buff-tiles-1.png");
      break;
    case BuffType::Health:
      buff = new Buff("../assets/texture/health_buff.png");
      buff->effect_ = bf_Health;
      buff->rollback_ = bf_HealthRollback;
      break;
    case BuffType::Attack:
      buff = new Buff("../assets/texture/attack_buff.png");
      buff->effect_ = bf_Attack;
      buff->rollback_ = bf_AttackRollback;
      break;
    case BuffType::Defence:
      buff = new Buff("../assets/texture/defence_buff.png"); //path to defence_
      buff->effect_ = bf_Defence;
      buff->rollback_ = bf_DefenceRollback;
      break;
    case BuffType::MoveRange:
      buff = new Buff("../assets/texture/move_range_buff.png");  //path to move_range_
      buff->effect_ = bf_MoveRange;
      buff->rollback_ = bf_MoveRangeRollback;
      break;
    case BuffType::Vision:
      buff = new Buff("../assets/texture/vision_buff.png");  //path to vision_range_
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

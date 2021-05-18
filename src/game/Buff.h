#ifndef TAURMAZE_SRC_GAME_BUFF_H_
#define TAURMAZE_SRC_GAME_BUFF_H_

#include <functional>
#include "../game/Player.h"

void bf_DefaultEffect(Player& obj);
void bf_DefaultRollback(Player& obj);
void bf_Health(Player& obj);
void bf_HealthRollback(Player& obj);
void bf_Attack(Player& obj);
void bf_AttackRollback(Player& obj);
void bf_Defence(Player& obj);
void bf_DefenceRollback(Player& obj);
void bf_Speed(Player& obj);
void bf_SpeedRollback(Player& obj);
void bf_Vision(Player& obj);
void bf_VisionRollback(Player& obj);

enum class BuffType {
  None,
  Health,
  Attack,
  Defence,
  Speed,
  Vision
};

class Buff {
 public:
  Buff(const char *path = "../assets/texture/buff-tiles-1.png");

  static Buff* CreateBuff(BuffType type, float effect_time);

  void Draw(sf::RenderWindow& window);

  void SetPosition(sf::Vector2f position);

  void Apply(Player&);

  void SetEffect(std::function<void(Player&)> function);

  void SetRollback(std::function<void(Player&)> function);

  void SetEffectTime(float time);

 private:
  sf::Sprite sprite_;

  std::function<void(Player&)> effect_ = bf_DefaultEffect;
  std::function<void(Player&)> rollback_ = bf_DefaultRollback;

  float effect_time_ = 1;
};

#endif //TAURMAZE_SRC_GAME_BUFF_H_

#ifndef TAURMAZE_SRC_GAME_PLAYER_H_
#define TAURMAZE_SRC_GAME_PLAYER_H_

#include "../core/Object.h"

class Player : public Object {
 public:
  Player();

  void Update() override;

    //void Draw(sf::RenderWindow &) override;
 private:
  /*
   * Attribute - health, speed...
   */

  std::vector<sf::Vector2f> targets_;
  float move_speed = 1.0f;
};

#endif //TAURMAZE_SRC_GAME_PLAYER_H_

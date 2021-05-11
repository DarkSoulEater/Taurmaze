#ifndef TAURMAZE_SRC_GAME_PLAYER_H_
#define TAURMAZE_SRC_GAME_PLAYER_H_

#include "../core/Object.h"

class Player : public Object {
 public:
  Player();

  void Update() override;

  void SetTargets(const std::vector<sf::Vector2f>&);

  bool InMove() const;

  int get_health_points();

  int& set_health_points();

  int get_defence();

  int& set_defence();

  float get_speed();

  float& set_speed();

  int get_vision();

  int& set_vision();

    //void Draw(sf::RenderWindow &) override;
 private:
  /*
   * Attribute - health, speed...
   */

  std::vector<sf::Vector2f> targets_;
  float move_speed = 0.5f;

  int health_points = 10;
  int defence = 10;
  int speed = 3;
  int vision = 3;
};

#endif //TAURMAZE_SRC_GAME_PLAYER_H_

#ifndef TAURMAZE_SRC_GAME_PLAYER_H_
#define TAURMAZE_SRC_GAME_PLAYER_H_

#include "../core/Object.h"

class Player : public Object {
 public:
  Player();

  void Update() override;

  void SetTargets(const std::vector<sf::Vector2f>&);

  bool InMove() const;

  int GetHealthPoints() const;

  void SetHealthPoints(int new_health);

  int GetDefence() const;

  void SetDefence(int new_defence);

  int GetSpeed() const;

  void SetSpeed(int new_speed);

  int GetVision() const;

  void SetVision(int new_vision);

    //void Draw(sf::RenderWindow &) override;
 private:
  int health_points = 10;
  int defence = 10;
  int speed = 3;
  int vision = 3;

  std::vector<sf::Vector2f> targets_;
  float move_speed = 0.5f;

};

#endif //TAURMAZE_SRC_GAME_PLAYER_H_

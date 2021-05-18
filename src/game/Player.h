#ifndef TAURMAZE_SRC_GAME_PLAYER_H_
#define TAURMAZE_SRC_GAME_PLAYER_H_

#include "../core/Object.h"

class Grid;

class Player : public Object {
 public:
  Player(Grid& grid);

  void Update() override;

  void Draw(sf::RenderWindow &) override;

  void SetPosition(const sf::Vector2f &position) override;

  void SetTargets(const std::vector<sf::Vector2f>&);

  bool InMove() const;

  void EndTurn();

  int GetHealthPoints() const;

  void SetHealthPoints(int new_health);

  int GetAttack() const;

  void SetAttack(int new_attack);

  int GetDefence() const;

  void SetDefence(int new_defence);

  int GetMoveRange() const;

  void SetMoveRange(int new_move_range);

  int GetVision() const;

  void SetVision(int new_vision);

  sf::Vector2i GetCoords();
 private:
  int health_points_ = 10;
  int attack_ = 10;
  int defence_ = 5;
  int move_range_ = 3;
  int vision_range_ = 3;

  Grid& grid_;

  std::vector<sf::Vector2f> targets_;
  float move_speed = 0.5f;
  sf::Vector2i coords_ = {0, 0 };
};

#endif //TAURMAZE_SRC_GAME_PLAYER_H_

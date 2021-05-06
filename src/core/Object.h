//
// Created by eleno on 03.05.2021.
//

#ifndef TAURMAZE__OBJECT_H_
#define TAURMAZE__OBJECT_H_

#include <set>
#include <SFML/Graphics.hpp>

class Object {
 public:
  friend class Core;
  explicit Object(int level = 0);

  explicit Object(const char* path, int level = 0);

  virtual ~Object();


  virtual void PreUpdate();

  virtual void Update();


  virtual void Draw(sf::RenderWindow &window);


  virtual void SetSpritePosition(const sf::Vector2f& position);
 private:
  sf::Texture texture_;
  sf::Sprite sprite_;

  static std::set<std::pair<int, Object*>> buffer_;
  std::set<std::pair<int, Object*>>::const_iterator buffer_iterator_;
  int level_;
};

#endif //TAURMAZE__OBJECT_H_
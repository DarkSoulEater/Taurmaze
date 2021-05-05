//
// Created by eleno on 03.05.2021.
//

#ifndef TAURMAZE__OBJECT_H_
#define TAURMAZE__OBJECT_H_

#include <SFML/Graphics.hpp>
#include "Clickable.h"
#include "Drawable.h"


class Object : public Drawable, public Clickable {
 public:
  Object();
  Object(const char* path);

  bool MouseBound(sf::Vector2i mouse_pos) const override;
  void isClick() override;

  void Draw(sf::RenderWindow &window) override;
 private:
  sf::Texture texture_;
  sf::Sprite sprite_;
};

#endif //TAURMAZE__OBJECT_H_

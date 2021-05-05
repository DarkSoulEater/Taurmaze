//
// Created by eleno on 03.05.2021.
//

#include "Object.h"
#include <iostream>

Object::Object() {
  sf::Image image;
  image.loadFromFile("../assets/texture/box.png");
  texture_.loadFromImage(image);
  sprite_ = sf::Sprite(texture_);
  sprite_.setPosition(100.f, 100.f);
}

Object::Object(const char *path) {

}

bool Object::MouseBound(sf::Vector2i mouse_pos) const {
  return sprite_.getGlobalBounds().contains(sf::Vector2f(mouse_pos));
}

void Object::isClick() {
  std::cout << "CLICK!!!\n";
}

void Object::Draw(sf::RenderWindow &window) {
  window.draw(sprite_);
}
//
// Created by eleno on 03.05.2021.
//

#include "Object.h"

std::set<std::pair<int, Object*>> Object::buffer_ = std::set<std::pair<int, Object*>>();

Object::Object(int level) {
  level_ = level;
  buffer_iterator_ = buffer_.insert({level_, this}).first;

  sf::Image image;
  image.loadFromFile("../assets/texture/box.png");
  texture_.loadFromImage(image);
  sprite_ = sf::Sprite(texture_);
}

Object::Object(const char *path, int level) {
  level_ = level;
  buffer_iterator_ = buffer_.insert({level_, this}).first;

  sf::Image image;
  image.loadFromFile(path);
  texture_.loadFromImage(image);
  sprite_ = sf::Sprite(texture_);
}

Object::~Object() {
  buffer_.erase(buffer_iterator_);
}

void Object::PreUpdate() {return;}

void Object::Update() {return;}

void Object::Draw(sf::RenderWindow &window) {
  window.draw(sprite_);
}

void Object::SetSpritePosition(const sf::Vector2f &position) {
  sprite_.setPosition(position);
}
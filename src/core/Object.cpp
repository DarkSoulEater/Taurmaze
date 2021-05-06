#include "Object.h"
#include "util/asset.h"

std::set<std::pair<int, Object*>> Object::buffer_ = std::set<std::pair<int, Object*>>();

Object::Object(int level) {
  level_ = level;
  buffer_iterator_ = buffer_.insert({level_, this}).first;

  sprite_ = sf::Sprite(asset::LoadTexture("../assets/texture/default_obj.png"));
}

Object::Object(const char *path, int level) {
  level_ = level;
  buffer_iterator_ = buffer_.insert({level_, this}).first;

  sprite_ = sf::Sprite(asset::LoadTexture(path));
}

Object::~Object() {
  buffer_.erase(buffer_iterator_);
}

void Object::PreUpdate() {}

void Object::Update() {}

void Object::LastUpdate() {}


void Object::OnMouseEnter() {}

void Object::OnMouseOver() {}

void Object::OnMouseExit() {}

void Object::OnClick() {}


void Object::SetPosition(const sf::Vector2f &position) {
  sprite_.setPosition(position);
}

void Object::SetTexture(const char* path) {
  sprite_.setTexture(asset::LoadTexture(path));
}

void Object::SetTextureRect(const sf::IntRect& rect) {
  sprite_.setTextureRect(rect);
}

void Object::Draw(sf::RenderWindow &window) {
  window.draw(sprite_);
}

void Object::SetSpritePosition(const sf::Vector2f &position) {
  sprite_.setPosition(position);
}


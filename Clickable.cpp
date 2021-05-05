//
// Created by eleno on 03.05.2021.
//

#include "Clickable.h"
#include <iostream>

std::vector<std::vector<int>> Clickable::free_id_ = std::vector<std::vector<int>> (15, std::vector<int>());
std::vector<std::vector<Clickable*>> Clickable::buffer_ = std::vector<std::vector<Clickable*>>(15, std::vector<Clickable*>());

Clickable::Clickable(int level) : level_(level) {
  if (free_id_[level].empty()) {
    buffer_[level].push_back(this);
    buffer_id_ = buffer_[level].size() - 1;
  } else {
    buffer_id_ = free_id_[level][free_id_[level].size() - 1];
    buffer_[level_][buffer_id_] = this;
    free_id_.pop_back();
  }
}

Clickable::~Clickable() {
  buffer_[level_][buffer_id_] = nullptr;
  free_id_[level_].push_back(buffer_id_);
}

bool Clickable::MouseBound(sf::Vector2i mouse_pos) const { return false; }

void Clickable::isClick() {}

void Clickable::isPointer() {}

int Clickable::Activate() {
  if (MouseBound(input::GetMousePosition())) {
    if (isPointerable) isPointer();
    if (isClickable && input::GetKeyDown(clickable_key_code_)) {
      isClick();
      return 2;
    }
    return 1;
  }
  return 0;
}


void Clickable::SetKeyCode(input::KeyCode key_code) {
  clickable_key_code_ = key_code;
}

void Clickable::SetClickable(bool f) { isClickable = f; }

void Clickable::SetPointerable(bool f) { isPointerable = f; }


input::KeyCode Clickable::GetKeyCode() const {return clickable_key_code_;}

bool Clickable::GetClickable() const {return isClickable;}

bool Clickable::GetPointerable() const {return isPointerable;}

std::vector<Clickable*> Clickable::GetBuffer(int level) {
  return buffer_[level];
}

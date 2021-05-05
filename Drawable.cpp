//
// Created by eleno on 03.05.2021.
//

#include "Drawable.h"

std::vector<std::vector<int>> Drawable::free_id_ = std::vector<std::vector<int>> (15, std::vector<int>());
std::vector<std::vector<Drawable*>> Drawable::buffer_ = std::vector<std::vector<Drawable*>>(15, std::vector<Drawable*>());

Drawable::Drawable(int level) : level_(level) {
  if (free_id_[level].empty()) {
    buffer_[level].push_back(this);
    buffer_id_ = buffer_[level].size() - 1;
  } else {
    buffer_id_ = free_id_[level][free_id_[level].size() - 1];
    buffer_[level_][buffer_id_] = this;
    free_id_.pop_back();
  }
}

Drawable::~Drawable() {
  buffer_[level_][buffer_id_] = nullptr;
  free_id_[level_].push_back(buffer_id_);
}

std::vector<Drawable *> Drawable::GetBuffer(int level) {
  return buffer_[level];
}


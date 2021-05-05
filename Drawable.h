//
// Created by eleno on 03.05.2021.
//

#ifndef TAURMAZE__DRAWABLE_H_
#define TAURMAZE__DRAWABLE_H_

#include <SFML/Graphics.hpp>

class Drawable {
 public:
  friend class Core;
  explicit Drawable(int level = 0);

  virtual ~Drawable();

  virtual void Draw(sf::RenderWindow& window) = 0;

 private:
  static std::vector<std::vector<int>> free_id_;
  static std::vector<std::vector<Drawable*>> buffer_;
  int level_;
  int buffer_id_;

  static std::vector<Drawable*> GetBuffer(int level);
};

#endif //TAURMAZE__DRAWABLE_H_

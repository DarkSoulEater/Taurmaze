//
// Created by eleno on 03.05.2021.
//

#ifndef TAURMAZE__CLICKABLE_H_
#define TAURMAZE__CLICKABLE_H_

#include <SFML/Graphics.hpp>
#include "Buffer.h"
#include "input.h"

class Clickable {
 public:
  friend class Core;
  explicit Clickable(int level = 0);

  virtual ~Clickable();


  virtual bool MouseBound(sf::Vector2i mouse_pos) const;

  virtual void isClick();

  virtual void isPointer();

  virtual int Activate();


  void SetKeyCode(input::KeyCode key_code);

  void SetClickable(bool);

  void SetPointerable(bool);


  input::KeyCode GetKeyCode() const;

  bool GetClickable() const;

  bool GetPointerable() const;

 private:
  static std::vector<std::vector<int>> free_id_;
  static std::vector<std::vector<Clickable*>> buffer_;
  int level_;
  int buffer_id_;

  input::KeyCode clickable_key_code_ = input::KeyCode::MOUSE_0;
  bool isClickable = true;
  bool isPointerable = false;

  static std::vector<Clickable*> GetBuffer(int level);
};

#endif //TAURMAZE__CLICKABLE_H_

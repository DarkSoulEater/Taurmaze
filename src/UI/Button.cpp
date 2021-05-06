#include "Button.h"

#include <iostream>
void b_DefaultFunction() {
  std::cout << "You do not set function!\n";
}

Button::Button() {
  function_ = b_DefaultFunction;
}
void Button::OnClick() {
  // Object::OnClick();
  function_();
}

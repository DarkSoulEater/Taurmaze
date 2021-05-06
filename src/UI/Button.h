#ifndef TAURMAZE_SRC_UI_BUTTON_H_
#define TAURMAZE_SRC_UI_BUTTON_H_

#include "core/Object.h"
#include <functional>

class Button : public Object {
 public:
  Button();

  void OnClick() override;

 private:
  std::function<void()> function_;
};

#endif //TAURMAZE_SRC_UI_BUTTON_H_

//
// Created by eleno on 02.05.2021.```
//

#ifndef TAURMAZE__CORE_H_
#define TAURMAZE__CORE_H_

#include <SFML/Graphics.hpp>
#include "Object.h"

class Core {
 public:
  Core();

  void Run();


 private:
  const int kWidth_ = 600;
  const int kHeight_ = 600;
  const char* kAppName = "Tourmaze";
  sf::RenderWindow window_;

  void MainLoop();

  bool GameOpen();

  void PollEvent();

  void DrawFrame();
};

#endif //TAURMAZE__CORE_H_

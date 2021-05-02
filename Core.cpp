//
// Created by eleno on 02.05.2021.
//

#include <iostream>
#include "Core.h"

Core::Core() : window_(sf::VideoMode(kWidth_, kHeight_), kAppName) {}

void Core::Run() {
  try {
    MainLoop();
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
  }
}

void Core::MainLoop() {
  while (GameOpen()) {
    PollEvent();
    DrawFrame();
  }
}

bool Core::GameOpen() {
  return window_.isOpen();
}

void Core::PollEvent() {
  sf::Event event;
  while (window_.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      window_.close();
  }
}

void Core::DrawFrame() {
  window_.clear();
  window_.display();
}
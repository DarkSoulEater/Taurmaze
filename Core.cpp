//
// Created by eleno on 02.05.2021.
//

#include <iostream>
#include "Core.h"
#include "input.h"

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


namespace input {
void ResetKeyCall();
void KeyCallback(sf::Event&, int);
void MouseButtonCallback(sf::Event&, int);
void MousePositionCallback(sf::Vector2i);
void MouseScrollCallback(sf::Event&);
}
void Core::PollEvent() {
  input::ResetKeyCall();
  input::MousePositionCallback(sf::Mouse::getPosition(window_));

  sf::Event event;
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed: window_.close(); break;

      case sf::Event::KeyPressed: input::KeyCallback(event, 1); break;
      case sf::Event::KeyReleased: input::KeyCallback(event, 0); break;
      case sf::Event::MouseButtonPressed: input::MouseButtonCallback(event, 1); break;
      case sf::Event::MouseButtonReleased: input::MouseButtonCallback(event, 0); break;
      case sf::Event::MouseMoved: break;
      case sf::Event::MouseWheelMoved: input::MouseScrollCallback(event); break;
    }
  }

  for (int level = 14; level >= 0; --level) {
    auto buffer = Clickable::GetBuffer(level);

    for (auto obj : buffer) {
      if (obj == nullptr) continue;
      if (obj->Activate()) {
        break;
      }
    }
  }
}

void Core::DrawFrame() {
  window_.clear(sf::Color::White);

  for (int level = 0; level <= 14; ++level) {
    auto buffer = Drawable::GetBuffer(level);

    for (auto obj : buffer) {
      if (obj == nullptr) continue;
      obj->Draw(window_);
    }
  }

  window_.display();
}
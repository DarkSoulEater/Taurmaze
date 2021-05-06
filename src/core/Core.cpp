//
// Created by eleno on 02.05.2021.
//

#include <iostream>
#include "Core.h"
#include "util/input.h"

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
    HandleEvent();

    /*
    if (input::GetKeyDown(input::KeyCode::A)) {
      for (int i = 0; i < 10; ++i) {
        auto obj = new Object();
        obj->SetSpritePosition(sf::Vector2f(50 + i * 50, 50 + i * 50));
      }
    }
    */

    DrawFrame();
  }
}

bool Core::GameOpen() {
  return window_.isOpen();
}

void Core::HandleEvent() {
  PollEvent();
  CameraUpdate();
  CallPreUpdate();
  CallUpdate();
}

void Core::DrawFrame() {
  window_.clear(sf::Color::White);

  window_.setView(main_camera);
  bool view_flag = true;

  for (auto obj: Object::buffer_) {
    if (view_flag && obj.first >= 10) {
      view_flag = false;
      window_.setView(window_.getDefaultView());
    }
    obj.second->Draw(window_);
  }

  window_.display();
}

namespace input {
void ResetKeyCall();
void KeyCallback(sf::Event&, int);
void MouseButtonCallback(sf::Event&, int);
void MousePositionCallback(sf::Vector2i, sf::Vector2f);
void MouseScrollCallback(sf::Event&);
}
void Core::PollEvent() {
  input::ResetKeyCall();

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
}

void Core::CameraUpdate() {
  /*
   * Move, scale camera
   * */



  auto mouse_position = sf::Mouse::getPosition(window_);
  input::MousePositionCallback(mouse_position, window_.mapPixelToCoords(mouse_position, main_camera));
}

void Core::CallPreUpdate() {
  for (auto obj: Object::buffer_) {
    obj.second->PreUpdate();
  }
}

void Core::CallUpdate() {
  for (auto obj : Object::buffer_) {
    obj.second->Update();
  }
}
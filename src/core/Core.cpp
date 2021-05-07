#include <iostream>
#include "Core.h"
#include "Grid.h"
#include "util/input.h"

Core::Core() : window_(sf::VideoMode(kWidth_, kHeight_), kAppName), main_camera(window_.getDefaultView()) {}

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
    if (input::GetKeyDown(input::KeyCode::M)) {
      Grid* grid = new Grid;
      grid->BuildCells();
    }
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
  CallOnMouse();
  CallOnClick();
  CallUpdate();
  CallLastUpdate();
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
  float camera_move_velocity = 5.0f;
  if (input::GetKey(input::KeyCode::W)) {
    main_camera.move(0.0f, -camera_move_velocity);
  } else if (input::GetKey(input::KeyCode::S)) {
    main_camera.move(0.0f, +camera_move_velocity);
  }

  if (input::GetKey(input::KeyCode::A)) {
    main_camera.move(-camera_move_velocity, 0.0f);
  } else if (input::GetKey(input::KeyCode::D)) {
    main_camera.move(camera_move_velocity, 0.0f);
  }

  float camera_zoom_velocity = 1.02f;
  if (input::GetKey(input::KeyCode::Z)) {
    main_camera.zoom(1 / camera_zoom_velocity);
  } else if (input::GetKey(input::KeyCode::X)) {
    main_camera.zoom(camera_zoom_velocity);
  }

  auto mouse_position = sf::Mouse::getPosition(window_);
  input::MousePositionCallback(mouse_position, window_.mapPixelToCoords(mouse_position, main_camera));
}

void Core::CallOnMouse() {
  auto mouse_world_position = input::GetMouseWorldPosition();
  for (auto& obj: Object::buffer_) {
    if (obj.second->sprite_.getGlobalBounds().contains(mouse_world_position)) {
      if (obj.second->is_mouse_over_ == 0) {
        obj.second->OnMouseEnter();
        obj.second->is_mouse_over_ = true;
      } else {
        obj.second->OnMouseOver();
      }
    } else {
      if (obj.second->is_mouse_over_) {
        obj.second->OnMouseExit();
        obj.second->is_mouse_over_ = false;
      }
    }
  }
}

void Core::CallOnClick() {
  if (input::GetMouseButtonDown(0) == 0) return;

  for (auto& obj : Object::buffer_) {
    if (obj.second->is_mouse_over_) {
      obj.second->OnClick();
    }
  }
}

void Core::CallPreUpdate() {
  for (auto& obj: Object::buffer_) {
    obj.second->PreUpdate();
  }
}

void Core::CallUpdate() {
  for (auto& obj : Object::buffer_) {
    obj.second->Update();
  }
}

void Core::CallLastUpdate() {
  for (auto& obj : Object::buffer_) {
    obj.second->LastUpdate();
  }
}

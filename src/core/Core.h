#ifndef TAURMAZE__CORE_H_
#define TAURMAZE__CORE_H_

#include <SFML/Graphics.hpp>
#include "Object.h"

class Core {
 public:
  Core();

  ~Core();

  void Run();


 private:
  const int kWidth_ = 1920;
  const int kHeight_ = 1080;
  const char* kAppName = "Taurmaze";
  sf::RenderWindow window_;
  sf::View main_camera;

  void MainLoop();

  bool GameOpen();

  void HandleEvent();

  void DrawFrame();

  void PollEvent();

  void UpdateScene();

  void CameraUpdate();

  void CallOnMouse();

  void CallOnClick();

  void CallPreUpdate();

  void CallUpdate();

  void CallLastUpdate();
};

#endif //TAURMAZE__CORE_H_

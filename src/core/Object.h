#ifndef TAURMAZE__OBJECT_H_
#define TAURMAZE__OBJECT_H_

#include <set>
#include <SFML/Graphics.hpp>
#include <iterator>

class Object {
 public:
  friend class Core;
  explicit Object(int level = 0);

  explicit Object(const char* path, int level = 0);

  virtual ~Object();


  virtual void PreUpdate();

  virtual void Update();

  virtual void LastUpdate();


  virtual void OnMouseEnter();

  virtual void OnMouseOver();

  virtual void OnMouseExit();

  virtual void OnClick();


  virtual void SetPosition(const sf::Vector2f& position);

  virtual void SetTexture(const char* path);

  virtual void SetTextureRect(const sf::IntRect&);

  virtual void Draw(sf::RenderWindow&);

  virtual void SetSpritePosition(const sf::Vector2f& position);

protected:
  int level_;
  sf::Sprite sprite_;

private:
  static std::set<std::pair<int, Object*>> buffer_;
  std::set<std::pair<int, Object*>>::const_iterator buffer_iterator_;
  bool mouse_over_ = 0;
};

#endif //TAURMAZE__OBJECT_H_

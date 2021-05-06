#include <map>
#include "asset.h"

namespace asset {
static std::map<const char*, sf::Texture> textures_library;

sf::Texture& LoadTexture(const char* path) {
  if(textures_library.find(path) != textures_library.end()) {
      return textures_library[path];
  }
  sf::Texture texture;
  texture.loadFromFile(path);
  return textures_library[path] = texture;
}
} // namespace
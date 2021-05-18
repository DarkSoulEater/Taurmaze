#include <map>
#include "asset.h"

namespace asset {
namespace path {
  const char* t_StoneCellTiles = "../assets/texture/dungeon-tiles.jpg";

} // namespace

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
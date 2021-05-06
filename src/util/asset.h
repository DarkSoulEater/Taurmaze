//
// Created by asmekal on 06.05.2021.
//

#ifndef TAURMAZE_ASSET_H
#define TAURMAZE_ASSET_H

#include <SFML/Graphics.hpp>
#include <map>

namespace asset {
    std::map<const char*, sf::Texture> get_texture;

    sf::Texture& LoadTexture(const char* path);
}


#endif //TAURMAZE_ASSET_H

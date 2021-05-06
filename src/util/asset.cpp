//
// Created by asmekal on 06.05.2021.
//

#include "asset.h"

namespace asset {
    sf::Texture& LoadTexture(const char* path) {
        if(get_texture.find(path) != get_texture.end()) {
            return get_texture[path];
        }
        sf::Texture texture;
        texture.loadFromFile(path);
        return get_texture[path] = texture;
    }
}
#include <iostream>
#include "sprites.hpp"

using sprite::Sprite;

void print_sprite(Sprite const & s) {
    for     (int y{0}; y < Sprite::HEIGHT; y++) {
        for (int x{0}; x < Sprite::WIDTH;  x++) {
            std::cout << (s.get(x, y) ? "##" : "  ");
        }
        std::cout << '\n';
    }
}

int main() {
    std::cout << "\n\n";
    print_sprite(sprite::ALIEN);
    std::cout << "\n\n\n";
    print_sprite(sprite::PLAYER);
    std::cout << "\n\n";
    return 0;
}

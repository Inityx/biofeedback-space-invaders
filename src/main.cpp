#include <iostream>
#include <array>

#include "sprite.hpp"
#include "display/framebuffer.hpp"

using sprite::Sprite;

void print_sprites() {
    std::array<char, 201> buffer;

    std::cout << "\n\n";

    sprite::ALIEN.print_ascii(buffer);
    std::cout << &buffer[0];
    std::cout << "\n\n\n";

    sprite::PLAYER.print_ascii(buffer);
    std::cout << &buffer[0];
    std::cout << "\n\n";
}

void framebuffer_test() {
    display::Framebuffer fb{"/dev/fb0"};
    display::Pixel const white { 255, 255, 255, 255 };

    for (size_t i{0}; i < 480; i++) {
        fb.write_pixel(i, 0, white);
        fb.write_pixel(i, 319, white);
    }
    for (size_t i{0}; i < 320; i++) {
        fb.write_pixel(0, i, white);
        fb.write_pixel(479, i, white);
    }
}

int main() {
    framebuffer_test();
    return 0;
}

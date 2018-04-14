#include <iostream>
#include <array>

#include "sprite.hpp"
#include "display/framebuffer.hpp"

using sprite::Sprite;

void framebuffer_test() {
    display::Framebuffer fb{"/dev/fb0"};
    
    fb.write_sprite(20, 40, sprite::ALIEN);
    fb.write_sprite(20, 65, sprite::PLAYER);
    
    fb.refresh();
}

int main() {
    framebuffer_test();
    return 0;
}

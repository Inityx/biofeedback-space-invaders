#include <iostream>
#include <array>

#include "sprite.hpp"
#include "display/framebuffer.hpp"
#include "game/engine.hpp"
#include "game/interface.hpp"

char const * const FB_FILENAME{"/dev/fb0"};

using namespace game;
using namespace display;

int main() {
    Engine engine;
    Framebuffer fb{FB_FILENAME};

    Interface{engine, fb}.play();
    return 0;
}


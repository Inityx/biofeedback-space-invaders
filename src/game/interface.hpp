#ifndef GAME_INTERFACE_HPP
#define GAME_INTERFACE_HPP

#include <chrono>
#include <thread>

#include "../display/framebuffer.hpp"
#include "engine.hpp"

namespace game {
    struct Interface {
    private:
        Engine & engine;
        display::Framebuffer & fb;
        std::chrono::milliseconds delay{800};

    public:
        Interface(Engine & engine, display::Framebuffer & fb)
            : engine{engine}, fb{fb} {}

        void play() {
            render();
            while(true) {
                std::this_thread::sleep_for(delay);
                engine.step();
                render();

            }
        }

        void render() {
            for (auto sprite_view : engine.render()) {
                fb.write_sprite_view(sprite_view);
            }
            fb.refresh();
        }
    };
}

#endif
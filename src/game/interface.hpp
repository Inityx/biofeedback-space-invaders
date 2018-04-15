#ifndef GAME_INTERFACE_HPP
#define GAME_INTERFACE_HPP

#include <chrono>
#include <thread>

#include "../display/framebuffer.hpp"
#include "engine.hpp"

namespace game {
    struct Interface {
    private:
        static const size_t
            TARGET_WIDTH{480},
            TARGET_HEIGHT{320};
        
        Engine & engine;
        display::Framebuffer & fb;
        std::chrono::milliseconds delay{200};

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
            if (fb.get_x_res() > TARGET_WIDTH)
                fb.write_line_v(TARGET_WIDTH + 1, 0, TARGET_HEIGHT);

            if (fb.get_y_res() > TARGET_HEIGHT)
                fb.write_line_h(0, TARGET_HEIGHT + 1, TARGET_WIDTH);

            for (auto sprite_view : engine.render()) {
                fb.write_sprite_view(sprite_view);
            }
            fb.refresh();
        }
    };
}

#endif
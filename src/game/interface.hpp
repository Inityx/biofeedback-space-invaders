#ifndef GAME_INTERFACE_HPP
#define GAME_INTERFACE_HPP

#include <chrono>
#include <thread>
#include <atomic>
#include <cstdio>
#include <curses.h>

#include "../display/framebuffer.hpp"
#include "engine.hpp"

namespace game {
    namespace Key {
        char const
            LEFT{75},
            RIGHT{77},
            UP{72};
    }

    struct Interface {
    private:
        Engine & engine;
        display::Framebuffer & fb;
        std::chrono::milliseconds 
            frame_delay{36},
            enemy_delay{200};
        std::atomic<uint8_t> lose{0};

    public:
        Interface(Engine & engine, display::Framebuffer & fb)
            : engine{engine}, fb{fb} {}

        static void enemy_step_loop(Interface * self) {
            while(!self->lose.load()) {
                std::this_thread::sleep_for(self->enemy_delay);
                bool enemy_step_lose = !self->engine.enemy_step();
                self->lose.fetch_or(static_cast<uint8_t>(enemy_step_lose));
            }
        }
        
        static void render_loop(Interface * self) {
            while(!self->lose.load()) {
                std::this_thread::sleep_for(self->frame_delay);
                self->render();
            }
        }

        void play() {
            // ncurses setup
            initscr();
            noecho();
            curs_set(0);

            // Slave threads
            std::thread
                renderer     {render_loop,     this},
                enemy_stepper{enemy_step_loop, this};

            while(!lose.load()) {
                int const input{getch()};
                switch (input) {
                    case 'a': engine.move_player(Engine::Direction::Left ); break;
                    case 'd': engine.move_player(Engine::Direction::Right); break;
                    case 'w': engine.fire(); break;
                    default: break;
                }
            }

            renderer.join();
            enemy_stepper.join();
        }

        void render() {
            if (fb.get_x_res() > Engine::TARGET_WIDTH)
                fb.write_line_v(Engine::TARGET_WIDTH + 1, 0, Engine::TARGET_HEIGHT);

            if (fb.get_y_res() > Engine::TARGET_HEIGHT)
                fb.write_line_h(0, Engine::TARGET_HEIGHT + 1, Engine::TARGET_WIDTH);

            for (auto sprite_view : engine.render()) {
                fb.write_sprite_view(sprite_view);
            }
            fb.refresh();
        }
    };
}

#endif

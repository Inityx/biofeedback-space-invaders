#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <vector>
#include "../sprite.hpp"

namespace game {
    struct Engine {
        struct Enemy {
            enum struct State { Up, Down, Dead };

            size_t x, y;
            State state{State::Down};
            sprite::Sprite const
                & up,
                & down,
                & dead;

            constexpr Enemy(
                size_t const x,
                size_t const y,
                sprite::Sprite const & up,
                sprite::Sprite const & down,
                sprite::Sprite const & dead
            ) :
                x{x}, y{y}, up{up}, down{down}, dead{dead}
            {}

            sprite::Sprite const & current_sprite() const {
                switch (state) {
                    case State::Up:   return up;
                    case State::Down: return down;
                    case State::Dead: return dead;
                }
            }

            sprite::SpriteView as_sprite_view() const {
                return sprite::SpriteView { current_sprite(), x, y };
            }

            void flap() {
                switch (state) {
                    case State::Up:   state = State::Down; break;
                    case State::Down: state = State::Up;   break;
                    default: break;
                }
            }
        };

        static size_t const
            COLUMNS{10},
            MARGIN_H{40},
            SPACING_H{20};

        std::vector<Enemy> enemies;

        Engine() {
            for (size_t i{0}; i < COLUMNS; i++) {
                enemies.push_back(
                    Enemy {
                        MARGIN_H + (i * SPACING_H),
                        200,
                        sprite::ALIEN3_UP,
                        sprite::ALIEN3_DOWN,
                        sprite::EXPLOSION
                    }
                );
            }
        }

        void step() {
            for (auto & enemy : enemies) enemy.flap();
        }

        std::vector<sprite::SpriteView> render() {
            std::vector<sprite::SpriteView> sprites;
            for (auto & enemy : enemies)
                sprites.push_back(enemy.as_sprite_view());
            return sprites;
        }
    };
}

#endif
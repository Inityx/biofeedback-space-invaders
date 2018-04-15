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
            COLUMNS{14},
            MARGIN_H{20},
            SPACING_H{sprite::WIDTH * 2},
            SPACING_V{sprite::HEIGHT * 3};

        std::vector<Enemy> enemies;

        Engine() {
            for (size_t col{0}; col < COLUMNS; col++) {
                enemies.push_back(
                    Enemy {
                        MARGIN_H + (col * SPACING_H),
                        SPACING_V,
                        sprite::ALIEN2_UP,
                        sprite::ALIEN2_DOWN,
                        sprite::EXPLOSION
                    }
                );
            }

            for (size_t row{0}; row < 2; row++) {
                for (size_t col{0}; col < COLUMNS; col++) {
                    enemies.push_back(
                        Enemy {
                            MARGIN_H + (col * SPACING_H),
                            (SPACING_V * 2) + (row * SPACING_V),
                            sprite::ALIEN1_UP,
                            sprite::ALIEN1_DOWN,
                            sprite::EXPLOSION
                        }
                    );
                }
            }

            for (size_t row{0}; row < 2; row++) {
                for (size_t col{0}; col < COLUMNS; col++) {
                    enemies.push_back(
                        Enemy {
                            MARGIN_H + (col * SPACING_H),
                            (SPACING_V * 4) + (row * SPACING_V),
                            sprite::ALIEN3_UP,
                            sprite::ALIEN3_DOWN,
                            sprite::EXPLOSION
                        }
                    );
                }
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
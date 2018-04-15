#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <vector>
#include "../sprite.hpp"

namespace game {
    struct Engine {
        enum struct Direction { Left, Right };

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

            void nudge(Direction direction) {
                switch (direction) {
                    case Direction::Left:  x -= 1; break;
                    case Direction::Right: x += 1; break;
                }
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
        Direction direction{Direction::Right};

        void add_enemy_rows(
            size_t num_rows,
            size_t start_row,
            sprite::Sprite const & up,
            sprite::Sprite const & down
        ) {
            for (size_t row{0}; row < num_rows; row++) {
                for (size_t col{0}; col < COLUMNS; col++) {
                    size_t const
                        x{MARGIN_H + (col * SPACING_H)},
                        y{(SPACING_V * (start_row + 1)) + (row * SPACING_V)};
                    
                    enemies.push_back(
                        Enemy { x, y, up, down, sprite::EXPLOSION }
                    );
                }
            }
        }

        Engine() {
            add_enemy_rows(1, 0, sprite::ALIEN2_UP, sprite::ALIEN2_DOWN);
            add_enemy_rows(2, 1, sprite::ALIEN1_UP, sprite::ALIEN1_DOWN);
            add_enemy_rows(2, 3, sprite::ALIEN3_UP, sprite::ALIEN3_DOWN);
        }

        void reverse() {
            switch (direction) {
                case Direction::Left:  direction = Direction::Right; break;
                case Direction::Right: direction = Direction::Left;  break;
            }
        }

        void step() {
            // TODO If <direction>-most enemy is at edge, reverse
            
            // if (at_edge) reverse();

            for (auto & enemy : enemies) {
                enemy.nudge(direction);
                enemy.flap();
            }

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
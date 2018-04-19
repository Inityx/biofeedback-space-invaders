#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <vector>
#include "../sprite.hpp"

namespace game {
    struct Engine {
        static const size_t
            TARGET_WIDTH{480},
            TARGET_HEIGHT{320};
        
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

            void drop(size_t amount) { y += amount; }

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

    private:
        static size_t const
            COLUMNS{14},
            MARGIN_H{40},
            SPACING_H{sprite::WIDTH * 2},
            SPACING_V{sprite::HEIGHT * 3},
            PLAYER_HEIGHT{TARGET_HEIGHT - (SPACING_V * 2) },
            PLAYER_SPEED{4};

        std::vector<Enemy> enemies;
        size_t player_x{(TARGET_WIDTH / 2) - 1};
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

        bool edge_bounce() {
            if (direction == Direction::Right) {
                size_t max{0};

                for (auto & enemy : enemies)
                    if (enemy.x > max)
                        max = enemy.x;
                
                if (max >= (TARGET_WIDTH - MARGIN_H - sprite::WIDTH)) {
                    direction = Direction::Left;
                    return true;
                }
                return false;
                
            } else {
                size_t min{SIZE_MAX};

                for (auto & enemy : enemies)
                    if (enemy.x < min)
                        min = enemy.x;
                
                if (min <= MARGIN_H) {
                    direction = Direction::Right;
                    return true;
                }
                return false;
            }
        }

    public:
        Engine() {
            add_enemy_rows(1, 0, sprite::ALIEN2_UP, sprite::ALIEN2_DOWN);
            add_enemy_rows(2, 1, sprite::ALIEN1_UP, sprite::ALIEN1_DOWN);
            add_enemy_rows(2, 3, sprite::ALIEN3_UP, sprite::ALIEN3_DOWN);
        }

        bool enemy_step() {
            bool const bounced = edge_bounce();
            for (auto & enemy : enemies) {
                if (bounced)
                    enemy.drop(SPACING_V);
                enemy.nudge(direction);
                enemy.flap();

                if (enemy.y >= PLAYER_HEIGHT)
                    return false;
            }

            return true;
        }

        void move_player(Direction const direction) {
            switch (direction) {
                case Direction::Left:
                    if (player_x > MARGIN_H)
                        player_x -= PLAYER_SPEED;
                    break;
                
                case Direction::Right:
                    if (player_x < TARGET_WIDTH - MARGIN_H)
                        player_x += PLAYER_SPEED;
                    break;
            }
        }

        void fire() {
            
        }

        std::vector<sprite::SpriteView> render() {
            std::vector<sprite::SpriteView> sprites;
            for (auto & enemy : enemies)
                sprites.push_back(enemy.as_sprite_view());

            sprites.push_back(
                sprite::SpriteView {
                    sprite::PLAYER,
                    player_x,
                    PLAYER_HEIGHT
                }
            );

            return sprites;
        }
    };
}

#endif
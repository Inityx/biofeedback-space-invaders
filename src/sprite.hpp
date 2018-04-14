#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>

namespace sprite {
    static constexpr size_t
        HEIGHT{8},
        WIDTH{12};
    using Image = std::array<bool, HEIGHT * WIDTH>;

    struct Sprite {
    private:
        Image image;

    public:
        constexpr Sprite(Image const & image) : image(image) {}

        constexpr bool get(size_t const x, size_t const y) const {
            size_t const index{(y * WIDTH) + x};
            return image[index];
        }
    };

    constexpr Sprite PLAYER {{
        0,0,0,0,0,1,1,0,0,0,0,0,
        0,0,0,0,0,1,1,0,0,0,0,0,
        0,0,0,0,0,1,1,0,0,0,0,0,
        0,0,0,0,1,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,
        0,1,0,1,0,1,1,0,1,0,1,0
    }};

    constexpr Sprite ALIEN1_F1 {{
        0,0,1,0,0,0,0,0,0,1,0,0,
        0,0,0,1,0,0,0,0,1,0,0,0,
        0,0,1,1,1,1,1,1,1,1,0,0,
        0,1,1,0,1,1,1,1,0,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,1,1,1,1,1,1,1,1,0,1,
        1,0,1,0,0,0,0,0,0,1,0,1,
        0,0,0,1,1,0,0,1,1,0,0,0
    }};

    constexpr Sprite ALIEN1_F2 {{
        0,0,1,0,0,0,0,0,0,1,0,0,
        1,0,0,1,0,0,0,0,1,0,0,1,
        1,0,1,1,1,1,1,1,1,1,0,1,
        1,1,1,0,1,1,1,1,0,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,
        0,1,1,1,1,1,1,1,1,1,1,0,
        0,0,1,0,0,0,0,0,0,1,0,0,
        0,1,0,0,0,0,0,0,0,0,1,0
    }};

    constexpr Sprite ALIEN2_F1 {{
        0,0,0,0,0,1,1,0,0,0,0,0,
        0,0,0,0,1,1,1,1,0,0,0,0,
        0,0,0,1,1,1,1,1,1,0,0,0,
        0,0,1,1,0,1,1,0,1,1,0,0,
        0,0,1,1,1,1,1,1,1,1,0,0,
        0,0,0,0,1,0,0,1,0,0,0,0,
        0,0,0,1,0,1,1,0,1,0,0,0,
        0,0,1,0,1,0,0,1,0,1,0,0
    }};

    constexpr Sprite ALIEN2_F2 {{
        0,0,0,0,0,1,1,0,0,0,0,0,
        0,0,0,0,1,1,1,1,0,0,0,0,
        0,0,0,1,1,1,1,1,1,0,0,0,
        0,0,1,1,0,1,1,0,1,1,0,0,
        0,0,1,1,1,1,1,1,1,1,0,0,
        0,0,0,0,1,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,1,0,0,0,
        0,0,0,0,1,0,0,1,0,0,0,0
    }};

    constexpr Sprite ALIEN3_F1 {{
        0,0,0,0,1,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,0,0,1,1,0,0,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,
        0,0,1,1,1,0,0,1,1,1,0,0,
        0,1,1,0,0,1,1,0,0,1,1,0,
        0,0,1,1,0,0,0,0,1,1,0,0
    }};

    constexpr Sprite ALIEN3_F2 {{
        0,0,0,0,1,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,0,0,1,1,0,0,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,
        0,0,0,1,1,0,0,1,1,0,0,0,
        0,0,1,1,0,1,1,0,1,1,0,0,
        1,1,0,0,0,0,0,0,0,0,1,1
    }};
}

#endif
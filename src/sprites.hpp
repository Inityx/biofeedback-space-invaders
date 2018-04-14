#include <array>

namespace sprite {
    struct Sprite {
        static constexpr size_t
            HEIGHT{8},
            WIDTH{12};

        using Image = std::array<bool, HEIGHT * WIDTH>;
        
    private:
        Image image;

    public:
        constexpr Sprite(Image image) : image(image) {}

        bool get(size_t const x, size_t const y) const {
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

    constexpr Sprite ALIEN {{
        0,0,1,0,0,0,0,0,0,1,0,0,
        0,0,0,1,0,0,0,0,1,0,0,0,
        0,0,1,1,1,1,1,1,1,1,0,0,
        0,1,1,0,1,1,1,1,0,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,1,1,1,1,1,1,1,1,0,1,
        1,0,1,0,0,0,0,0,0,1,0,1,
        0,0,0,1,1,0,0,1,1,0,0,0
    }};
}

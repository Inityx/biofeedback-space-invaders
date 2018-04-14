#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdint>

namespace display {
    struct Pixel {
        uint8_t b, g, r, a;

        constexpr uint32_t as_32bit() const {
            return (
                (a << (3 * 8)) |
                (r << (2 * 8)) |
                (g << (1 * 8)) |
                (b << (0 * 8))
            );
        }

        constexpr uint16_t as_16bit() const {
            return (
                ((r >> 3) << 11) | // 5 bits red
                ((g >> 2) <<  5) | // 6 bits green
                ((b >> 3) <<  0)   // 5 bits blue
            );
        }
    };
}

#endif
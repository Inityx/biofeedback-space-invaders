#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <memory>

#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "pixel.hpp"
#include "../sprite.hpp"

namespace display {
    struct Framebuffer {
    private:
        int file;
        struct fb_fix_screeninfo info_fix;
        struct fb_var_screeninfo info_var;
        size_t size;
        uint8_t * frame_buffer{0};
        std::unique_ptr<uint8_t[]> backing_buffer;

        uint8_t * buffer_location(size_t const x, size_t const y) const {
            return backing_buffer.get() +
                (info_var.xoffset + x) * (info_var.bits_per_pixel / 8) +
                (info_var.yoffset + y) * (info_fix.line_length);
        }

    public:
        void update_metadata() {
            if (ioctl(file, FBIOGET_VSCREENINFO, &info_var))
                throw std::runtime_error(std::strerror(errno));
        }

        Framebuffer(char const * const filename) {
            file = open(filename, O_RDWR);
            if (file == 0)
                throw std::runtime_error(std::strerror(errno));

            if (ioctl(file, FBIOGET_FSCREENINFO, &info_fix)) {
                throw std::runtime_error(std::strerror(errno));
            }
            
            update_metadata();

            size = (
                info_var.xres *
                info_var.yres *
                (info_var.bits_per_pixel / 8)
            );
            
            frame_buffer = reinterpret_cast<uint8_t *>(
                mmap(
                    0, size,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    file, 0
                )
            );
            if (reinterpret_cast<long>(frame_buffer) == -1)
                throw std::runtime_error("Error mapping device to memory");
            
            backing_buffer = decltype(backing_buffer){new uint8_t[size]};
        }

        ~Framebuffer() {
            if (frame_buffer) munmap(frame_buffer, size);
            close(file);
        }

        uint32_t get_x_res()     const { return info_var.xres;           }
        uint32_t get_y_res()     const { return info_var.yres;           }
        uint32_t get_bit_depth() const { return info_var.bits_per_pixel; }

        void print_info() const {
            printf(
                "Framebuffer: [ %dx%d ], %d bits per pixel\n",
                info_var.xres, info_var.yres,
                info_var.bits_per_pixel
            );
        }

        void refresh() {
            memcpy(frame_buffer, backing_buffer.get(), size);
            memset(backing_buffer.get(), 0, size);
        }

        void write_pixel(size_t const x, size_t const y, Pixel const color) {
            auto const location = buffer_location(x, y);
            auto const pixel32 = reinterpret_cast<uint32_t *>(location);
            auto const pixel16 = reinterpret_cast<uint16_t*>(location);
        
            switch(info_var.bits_per_pixel) {
            case 32: 
                *pixel32 = color.as_32bit();
                break;

            case 16:
            default:
                *pixel16 = color.as_16bit();
                break;   
            }
        }

        void write_sprite(
            size_t const x,
            size_t const y,
            sprite::Sprite const & sprite
        ) {
            Pixel const white { 255, 255, 255, 255 };
            for     (size_t sprite_y{0}; sprite_y < sprite::HEIGHT; sprite_y++) {
                for (size_t sprite_x{0}; sprite_x < sprite::WIDTH;  sprite_x++) {
                    if (sprite.get(sprite_x, sprite_y))
                        write_pixel(
                            x + sprite_x,
                            y + sprite_y,
                            white
                        );
                }
            }
        }
    };
}
#endif
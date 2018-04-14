#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <cstring>
#include <stdexcept>

#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "pixel.hpp"

namespace display {
    struct Framebuffer {
    private:
        int file;
        struct fb_fix_screeninfo info_fix;
        struct fb_var_screeninfo info_var;
        size_t size;
        uint8_t * buffer;

        uint8_t * buffer_location(size_t const x, size_t const y) const {
            return buffer +
                (info_var.xoffset + x) * (info_var.bits_per_pixel / 8) +
                (info_var.yoffset + y) * (info_fix.line_length);
        }

    public:
        void update_info_var() {
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
            
            update_info_var();

            size = (
                info_var.xres *
                info_var.yres *
                (info_var.bits_per_pixel / 8)
            );
            
            buffer = reinterpret_cast<uint8_t *>(
                mmap(
                    0, size,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    file, 0
                )
            );
            if (reinterpret_cast<long>(buffer) == -1)
                throw std::runtime_error("Error mapping device to memory");
        }

        ~Framebuffer() {
            munmap(buffer, size);
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
    };
}
#endif
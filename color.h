#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    // get rgb values
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // translate rgb values into byte range [0, 255]
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // write out colors to ostream
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif

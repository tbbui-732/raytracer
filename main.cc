#include <iostream>
#include "vec3.h"
#include "color.h"

int main(void) {
    // image
    float image_width = 255.0;
    float image_height = 255.0;

    // render
    std::cout << "P3\n" << image_width << ' ' << image_width << "\n255\n";

    for (int height = 0; height < image_height; ++height) {
        // progress bar
        std::clog << "\rScanlines remaining: " << (image_height - height) << ' ' << std::flush;

        for (int width = 0; width < image_width; ++width) {
            color pixel = color( 
                            double(width)/(image_width-1), 
                            double(height)/(image_height-1), 
                            0 );
            write_color(std::cout, pixel);
        }
    }
    std::clog << "\rFinished rendering\n";
    return 0;
}

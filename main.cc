#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

/* NOTE: ray will return a black pixel for now */
color ray_color(const ray& r) {
    return color(0, 0, 0);
}

int main(void) {

    // image dimensions
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // ensure image_height is >= 1

    // camera/viewport dimensions
    auto viewport_height = 2.0; // NOTE; arbitrary value
    auto viewport_width = viewport_height * ( double(image_width)/image_height );
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    // calculate vectors for horizontal and vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // calculate horizontal and vertical delta vectors
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // calculate location of upper left pixel
    auto viewport_upper_left = camera_center 
                             - vec3(0, 0, focal_length)     // move back focal_length
                             - (viewport_u/2)               // move left by half the viewport
                             - (viewport_v/2);              // move up by half the viewport
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // 0.5 for half a pixel's distance to ensure even pixel distancing



    // render
    std::cout << "P3\n" << image_width << ' ' << image_width << "\n255\n";

    for (int height = 0; height < image_height; ++height) {
        // progress bar
        std::clog << "\rScanlines remaining: " << (image_height - height) << ' ' << std::flush;

        for (int width = 0; width < image_width; ++width) {
            auto pixel_center = pixel00_loc                 // p_(0,0)
                              + (width * pixel_delta_u)     // move to right by current width * size of horizontal pixel delta
                              + (height * pixel_delta_v);   // move down by current height * size of vertical pixel delta

            // calculate ray direction
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            // get and write color
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rFinished rendering\n";
    return 0;
}

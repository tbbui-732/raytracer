#include <iostream>
#include "../include/vec3.h"
#include "../include/color.h"
#include "../include/ray.h"

color ray_color(const ray& r) {                                                 // NOTE: creates an arbitrary blue to white gradient
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));
}

int main(void) {
    auto aspect_ratio = 16.0 / 9.0;                                             // image dimensions
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;                       // ensure image_height is >= 1

    auto viewport_height = 2.0;                                                 // camera/viewport dimensions
    auto viewport_width = viewport_height *                                     // NOTE; arbitrary value
                            ( double(image_width)/image_height );
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    auto viewport_u = vec3(viewport_width, 0, 0);                               // calculate vectors for horizontal and vertical viewport edges
    auto viewport_v = vec3(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;                              // calculate horizontal and vertical delta vectors
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center                                    // calculate location of upper left pixel
                             - vec3(0, 0, focal_length)                         // move back focal_length
                             - (viewport_u/2)                                   // move left by half the viewport
                             - (viewport_v/2);                                  // move up by half the viewport
    auto pixel00_loc = viewport_upper_left + 0.5                                // 0.5 for half a pixel's distance to ensure even pixel distancing
                        * (pixel_delta_u + pixel_delta_v); 

   
    ////////////
    // RENDER //
    ////////////
    std::cout << "P3\n" << image_width << ' ' << image_width << "\n255\n";

    for (int height = 0; height < image_height; ++height) {
        std::clog << "\rScanlines remaining: "                                  // progress bar
                  << (image_height - height) 
                  << ' ' 
                  << std::flush;

        for (int width = 0; width < image_width; ++width) {
            auto pixel_center = pixel00_loc                                     // p_(0,0)
                              + (width * pixel_delta_u)                         // move to right by current width * size of horizontal pixel delta
                              + (height * pixel_delta_v);                       // move down by current height * size of vertical pixel delta

            auto ray_direction = pixel_center - camera_center;                  // calculate ray direction
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);                                   // calculate color of current pixel
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rFinished rendering\n";
    return 0;
}

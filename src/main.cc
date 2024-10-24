#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

// NOTE: creates an arbitrary blue to white gradient
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));
}


int main(void) {
    // image dimensions
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // ensure image_height is >= 1

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // calculate viewport height and width
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ( double(image_width)/image_height );
    double focal_length = 1.0;
    point3 camera_center = point3(0, 0, 0);

    // calculate vectors for horizontal and vertical viewport edges
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // calculate horizontal and vertical delta vectors
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // calculate location of upper left pixel
    point3 viewport_upper_left = camera_center
                               - vec3(0, 0, focal_length) // move back focal_length
                               - (viewport_u/2)           // move left by half the viewport
                               - (viewport_v/2);          // move up by half the viewport

    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); 

   
    ////////////
    // RENDER //
    ////////////
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";


    for (int height = 0; height < image_height; ++height) {
        std::clog << "\rScanlines remaining: " << (image_height - height) << ' ' << std::flush;

        for (int width = 0; width < image_width; ++width) {
            auto pixel_center = pixel00_loc
                              + (width * pixel_delta_u)   // move to right by current width * size of horizontal pixel delta
                              + (height * pixel_delta_v); // move down by current height * size of vertical pixel delta

            auto ray_direction = pixel_center - camera_center; // calculate ray direction
            ray r = ray(camera_center, ray_direction);

            color pixel_color = ray_color(r, world); // calculate color of current pixel
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rFinished rendering\n";
    return 0;
}

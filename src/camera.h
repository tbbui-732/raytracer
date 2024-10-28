#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "vec3.h"
#include "material.h"

class camera {
    private:
        int    image_height;   // Rendered image height
        point3 center;         // Camera center
        point3 pixel00_loc;    // Location of pixel 0, 0
        vec3   pixel_delta_u;  // Offset to pixel to the right
        vec3   pixel_delta_v;  // Offset to pixel below
        double pixel_samples_scale;  // Color scale factor for a sum of pixel samples

        void initialize() {
            // Set height of rendered image.
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            // Used to average the accumulated pixel color (anti-aliasing)
            pixel_samples_scale = 1.0 / samples_per_pixel;

            // Where rays are casted from
            center = point3(0, 0, 0);

            // Determine viewport dimensions.
            auto focal_length = 1.0;
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            auto viewport_height = 2 * h * focal_length;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = center 
                                     - vec3(0, 0, focal_length) // push viewport back
                                     - viewport_u/2  // move all the way left
                                     - viewport_v/2; // move all the way up

            // Center of the top left pixel of the viewport
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        vec3 sample_square() const {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        ray get_ray(int i, int j) const {
            // Get the point _around_ pixel(i, j)
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc
                              + ((i + offset.x()) * pixel_delta_u)
                              + ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            if (depth <= 0)
                return color(0,0,0);

            hit_record rec;

            if (world.hit(r, interval(0.001, infinity), rec)) { // 0.001 reduces shadow acne; prevents ray hitting itself or backwards
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth-1, world); // Successive scatters accumulate a new, blended color.
                return color(0,0,0); // no hit
            }

            // No object is hit. (Background color).
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));
        }

    public:
        double aspect_ratio      = 1.0;  // Ratio of image width over height
        int    image_width       = 100;  // Rendered image width in pixel count
        int    samples_per_pixel = 10;   // Count of random samples for each pixel
        int    max_depth         = 10;   // Max number of times a ray can bounce in a scene

        double vfov = 90;                   // Vertical fov
        point3 lookfrom = point3(0, 0, 0);  // Camera origin
        point3 lookat = point3(0, 0, -1);   // Camera point of where to look at
        vec3 vup = vec3(0, 1, 0);           // Camera's relative up direction

        void render(const hittable& world) {
            initialize();

            // header for ppm file format
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            // content of ppm file
            // NOTE: image scans left to right, top to bottom
            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0,0,0);
                    // anti-aliasing
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                }
            }

            std::clog << "\rDone.                 \n";
        }
};

#endif

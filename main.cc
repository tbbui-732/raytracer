#include <iostream>

int main(void) {
    // image
    float image_width = 255.0;
    float image_height = 255.0;

    // render
    std::cout << "P3\n" << image_width << ' ' << image_width << "\n255\n";

    for (int height = 0; height < image_height; ++height) {
        for (int width = 0; width < image_width; ++width) {
            float r = double(width) / (image_width-1);
            float g = double(height) / (image_height-1);
            float b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}

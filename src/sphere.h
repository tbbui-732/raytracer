#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;

    public:
        sphere(const point3& center, double radius, shared_ptr<material> mat) 
            : center(center), radius(std::fmax(0, radius)), mat(mat) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            // Simplified calculation for a circle.
            vec3 oc = center - r.origin(); // creates a vector from circle center to ray's origin.
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;


            // Discriminant determines if the ray hit the sphere.
            auto discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false;
            }

            // Sqrt of discriminant (the roots) will be used to find-
            //  the potential intersection points.
            auto sqrt_discriminant = std::sqrt(discriminant);
            auto root = (h - sqrt_discriminant) / a;

            // Check if the root(s) are within the valid range.
            if (!ray_t.surrounds(root)) {
                // Recalculate second root if first root is invalid.
                root = (h + sqrt_discriminant) / a;
                if (!ray_t.surrounds(root)) {
                    // No hit if neither roots are valid.
                    return false;
                }
            }

            // Store intersection details.
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }
};

#endif

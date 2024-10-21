#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
};

class hittable {
    public:
        virtual ~hittable() = default;                                          // default destructor
        virtual bool hit(const ray& r, double ray_tmin,                         // pure virtual function
                            double ray_tmax, hit_record& rec) const = 0;
};

#endif

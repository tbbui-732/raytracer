#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    private: 
        point3  orig;
        vec3    dir;

    public:
        ray() {}
        ray(const point3& origin, const vec3& direction) : 
            orig(origin), dir(direction) {}

        const point3& origin() const { return orig; }
        const vec3& direction() const { return dir; }
        point3 at(double t) const { return orig + dir*t; }                  // P(t) = orig + (direction * t);
};                                                                              // RECALL: P is the 3D position along a line

#endif

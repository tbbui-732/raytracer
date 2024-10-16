#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    private: 
        point3  orig;
        vec3    dir;

    public:
        // ctor
        ray() {}
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        // methods
        const point3& getOrigin() { return orig; }
        const vec3& getDirection() { return dir; }
        point3 at(double t) {
            return orig + (dir * t);
        }
};

#endif

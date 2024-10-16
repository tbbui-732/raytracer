#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    public: 
        double e[3];

        // ctor
        vec3() : e{0., 0., 0.} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // accessing x, y, z variables
        double x() { return e[0]; }
        double y() { return e[1]; }
        double z() { return e[2]; }

        // overloading operators
        vec3 operator-() const { 
            return vec3(-e[0], -e[1], -e[2]); 
        } 
        double operator[](int i) const { 
            return e[i];
        } 
        double& operator[](int i) { 
            return e[i];
        } 
        


};

#endif

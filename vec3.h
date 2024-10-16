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

        vec3 operator-() const {                    // vector negation
            return vec3(-e[0], -e[1], -e[2]); 
        } 

        double operator[](int i) const {            // copy of ith value
            return e[i];
        } 

        double& operator[](int i) {                 // reference of ith value
            return e[i];
        } 

        vec3& operator+=(const vec3& newVec) {      // addition assignment
            e[0] += newVec.e[0];
            e[1] += newVec.e[1];
            e[2] += newVec.e[2];
            return *this;
        }

        vec3& operator*=(const int multiplier) {    // multiplication assignment
            e[0] *= multiplier;
            e[1] *= multiplier;
            e[2] *= multiplier;
            return *this;
        }

        vec3& operator/=(const int divisor) {       // division assignment
            return (*this *= (1 / divisor));
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const {
            return std::sqrt(length_squared());
        }
};

#endif

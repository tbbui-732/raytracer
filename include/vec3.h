#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

///////////////////
// VECTOR  CLASS //
///////////////////
class vec3 {
    public: 
        double e[3];                                                            // 3d vector

        vec3() : e{0.0, 0.0, 0.0} {}                                            // ctor
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }                                       // accessing x, y, z variables
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const {                                                // vector negation
            return vec3(-e[0], -e[1], -e[2]); 
        } 

        double operator[](int i) const {                                        // copy of ith value
            return e[i];
        } 

        double& operator[](int i) {                                             // reference of ith value
            return e[i];
        } 

        vec3& operator+=(const vec3& newVec) {                                  // addition assignment
            e[0] += newVec.e[0];
            e[1] += newVec.e[1];
            e[2] += newVec.e[2];
            return *this;
        }

        vec3& operator*=(const float multiplier) {                                // multiplication assignment
            e[0] *= multiplier;
            e[1] *= multiplier;
            e[2] *= multiplier;
            return *this;
        }

        vec3& operator/=(const float divisor) {                                   // division assignment
            return (*this *= (1 / divisor));
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const {
            return std::sqrt(length_squared());
        }
};

using point3 = vec3;


//////////////////////////////
// VECTOR UTILITY FUNCTIONS //
//////////////////////////////
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {             // example: std::cout << v << " is the vector.";
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {                           // example: u + v
    return vec3(u.e[0]+v.e[0], 
                u.e[1]+v.e[1], 
                u.e[2]+v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {                           // example: u - v
    return vec3(u.e[0]-v.e[0], 
                u.e[1]-v.e[1], 
                u.e[2]-v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {                           // example: u * v
    return vec3(u.e[0]*v.e[0], 
                u.e[1]*v.e[1], 
                u.e[2]*v.e[2]);
}

inline vec3 operator*(const float multiplier, const vec3& v) {                    // example: 2 * vector
    return vec3(multiplier*v.e[0], 
                multiplier*v.e[1], 
                multiplier*v.e[2]);
}

inline vec3 operator*(const vec3& vector, const float multiplier) {               // example: vector * 2
    return multiplier * vector;
}

inline vec3 operator/(const vec3& vector, const float divisor) {                  // example: vector * 2
    return vector * (1 / divisor);
}

inline double dot(const vec3& u, const vec3& v) {                               // dot product
    return (u.e[0] * v.e[0]) + (u.e[1] * v.e[1]) + (u.e[2] * v.e[2]);
}

inline vec3 cross(const vec3& u, const vec3& v) {                               // cross product
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1],
                u.e[2]*v.e[0] - u.e[0]*v.e[2],
                u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit_vector(const vec3& v) { return v / v.length(); }

#endif

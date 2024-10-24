#ifndef VEC3_H
#define VEC3_H

///////////////////
// VECTOR  CLASS //
///////////////////
class vec3 {
    public: 
        double e[3];

        vec3() : e{0.0, 0.0, 0.0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // vector negation
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

        // copy of ith value
        double operator[](int i) const { return e[i]; }

        // reference of ith value
        double& operator[](int i) { return e[i]; }

        // addition assignment
        vec3& operator+=(const vec3& newVec) {
            e[0] += newVec.e[0];
            e[1] += newVec.e[1];
            e[2] += newVec.e[2];
            return *this;
        }

        // multiplication assignment
        vec3& operator*=(double multiplier) {
            e[0] *= multiplier;
            e[1] *= multiplier;
            e[2] *= multiplier;
            return *this;
        }

        // division assignment
        vec3& operator/=(const double divisor) {
            return (*this *= (1 / divisor));
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

using point3 = vec3;


//////////////////////////////
// VECTOR UTILITY FUNCTIONS //
//////////////////////////////

// example: std::cout << v << " is the vector.";
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// example: u + v
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0]+v.e[0], 
                u.e[1]+v.e[1], 
                u.e[2]+v.e[2]);
}

// example: u - v
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0]-v.e[0], 
                u.e[1]-v.e[1], 
                u.e[2]-v.e[2]);
}

// example: u * v
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0]*v.e[0], 
                u.e[1]*v.e[1], 
                u.e[2]*v.e[2]);
}

// example: 2 * vector
inline vec3 operator*(const double multiplier, const vec3& v) {
    return vec3(multiplier*v.e[0], 
                multiplier*v.e[1], 
                multiplier*v.e[2]);
}

// example: vector * 2
inline vec3 operator*(const vec3& vector, const double multiplier) {
    return multiplier * vector;
}

// example: vector / 2
inline vec3 operator/(const vec3& vector, const double divisor) {
    return vector * (1 / divisor);
}

// dot product
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// cross product
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1],
                u.e[2]*v.e[0] - u.e[0]*v.e[2],
                u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit_vector(const vec3& v) { return v / v.length(); }

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

#endif

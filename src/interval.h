#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
        double min, max;
        interval() : min(+infinity), max(-infinity) {}
        interval(double min, double max) : min(min), max(max) {}

        double size() const { return max - min; }

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const {
            return min < x && x < max;
        }

        double clamp(double x) {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static const interval empty, universe;
};


// no real number can fall within this interval
const interval interval::empty = interval(+infinity, -infinity);

// contains all real numbers
const interval interval::universe = interval(-infinity, +infinity);

#endif
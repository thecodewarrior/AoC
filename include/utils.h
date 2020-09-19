#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace aoc {

template <typename T> struct point {
public:
    T x, y;

    point(T x, T y) : x(x), y(y) {}

    point() : x(0), y(0) {}

    point operator+(const point &other) const { return point(x + other.x, y + other.y); }

    point operator-(const point &other) const { return point(x - other.x, y - other.y); }

    point operator*(const point &other) const { return point(x * other.x, y * other.y); }

    point operator*(const T &other) const { return point(x * other, y * other); }

    bool operator==(const point &rhs) const { return x == rhs.x && y == rhs.y; }

    bool operator!=(const point &rhs) const { return !(rhs == *this); }

    T manhattan_distance(const point &other) const {
        T distance_x = x < other.x ? other.x - x : x - other.x;
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        T distance_y = y < other.y ? other.y - y : y - other.y;
        if (distance_y < 0) {
            distance_y = -distance_y;
        }
        return distance_x + distance_y;
    }
};

} // namespace utils

#endif // AOC_UTILS_H

//
//
//
#ifndef BEZIERMK2_H
#define BEZIERMK2_H

#include <vector>
#include <string>
#include <tuple>

class point2d_t : public std::tuple<double, double>
{
public:
    typedef std::tuple<double, double> papa_t;
    point2d_t(double d0, double d1) : papa_t(d0, d1) {}

    virtual std::string to_string() const {
        return "{" + std::to_string(std::get<0>(*this)) + "," + std::to_string(std::get<1>(*this)) + "}";
    }
};

inline point2d_t operator *(double d, point2d_t const &p)
{
    return point2d_t(d * std::get<0>(p), d * std::get<1>(p));
}

inline point2d_t operator +(point2d_t a, point2d_t const &b)
{
    return point2d_t(std::get<0>(a) + std::get<0>(b), std::get<1>(a) + std::get<1>(b));
}

point2d_t bezierMk2(double u, std::vector<point2d_t> const &points);

#endif // BEZIERMK2_H

//
//
//

#ifndef COORDINATETRANSFORMATOR_H
#define COORDINATETRANSFORMATOR_H

#include <tuple>

class CoordinateTransformator {
private:
    double a11, a12, a13;
    double a21, a22, a23;

public:
    CoordinateTransformator() :
        a11(1), a12(0), a13(0),
        a21(0), a22(1), a23(0)
    {}

    CoordinateTransformator(double a1, double a2, double a3, double a4, double a5, double a6) :
        a11(a1), a12(a2), a13(a3),
        a21(a4), a22(a5), a23(a6)
    {}

    std::tuple<double, double> operator() (std::tuple<double, double> const &p) const
    {
        return std::make_tuple(a11 * std::get<0>(p) + a12 * std::get<1>(p) + a13,
            a21 * std::get<0>(p) + a22 * std::get<1>(p) + a23);
    }
};

#endif
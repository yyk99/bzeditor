//
//
//

#include "bezierMk2.h"

#include <stdexcept>

point2d_t bezierMk2(double u, std::vector<point2d_t> const &points)
{
    if (points.size() < 2)
        throw std::runtime_error("points size less than 2");

    std::vector<point2d_t> Q = points;
    for(int k = 0 ; k != Q.size() - 1 ; ++k) {
        for (int i = 0; i != Q.size() - k - 1; ++i) {
            Q[i] = (1.0 - u) * Q[i] + u * Q[i + 1];
        }
    }

    return Q[0];
}

// end of file
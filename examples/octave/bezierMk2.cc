//
//
//

#include "bezierMk2.h"

#include <stdexcept>

point2d_t bezierMk2(double u, std::vector<point2d_t> const &points)
{
//function B = bezierMk2 (u, varargin)
//  if nargin < 2
//    error("usage: bezier(t, points...)");
//  endif
//%  B = bezier_var(t, varargin);
//  n = length(varargin);
//  Q = zeros(n, 2);
//  for i = 1:n
//    Q(i,:) = varargin{i};
//  endfor
//  
//  for k = 1:n-1
//    for i = 1:n-k
//      Q(i,:) = (1.0 - u)*Q(i,:) + u * Q(i+1,:);
//    endfor
//  endfor
//  
//  B = Q(1,:);
//endfunction

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
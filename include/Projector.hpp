#ifndef PROJECTOR_H
#define PROJECTOR_H

#ifdef Success
  #undef Success
#endif
#include "Eigen/Dense"
using Eigen::Matrix4d;
using Eigen::Vector4d;

#include <array>
using std::array;

#include <cmath>

#include <vector>
template <typename T>
using dyn_array = std::vector<T>;


namespace projector {

    struct triangle;
    struct mesh;

    struct triangle {
        array< Vector4d, 3 > points;
    };


    struct mesh {
        dyn_array< triangle > triangles;

        size_t size();
    };

    /*
    *   Creates a projection matrix
    * 
    *   Parameters:
    *       aspectRatio: aspect ratio of the window
    *       fov: player's field of view
    *       zNear: closest point from the player
    *       zFar: furthest point from the player
    * 
    *   Returns:
    *       Matrix4d: projection matrix
    */
    const Matrix4d createProjectionMatrix(const double&, const double&, const double&, const double&);
    const Vector4d projectPoint(const Vector4d&, const Matrix4d&); 

    extern const double PI;
    extern const mesh CUBE;
}

#endif
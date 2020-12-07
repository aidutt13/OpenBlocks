#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <array>
using std::array;

#include <cmath>

#include <exception>

#include <iostream>

#include <vector>
template <typename T>
using dyn_array = std::vector<T>;


namespace projector {

    struct vector4d;
    struct matrix4d;
    struct triangle;
    struct mesh;

    struct vector4d {
        array< double, 4 > p;

        constexpr double& operator[](size_t);

        int32_t round(size_t);
    };

    struct matrix4d {
        array< array< double, 4 >, 4 > p;

        const array< double, 4 >& operator[](size_t);

        void fill(
            double, double, double, double,
            double, double, double, double,
            double, double, double, double,
            double, double, double, double
        );

        vector4d operator*(vector4d&);
    };

    struct triangle {
        array< vector4d, 3 > points;
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
    const matrix4d createProjectionMatrix(const double&, const double&, const double&, const double&);
    const vector4d projectPoint(vector4d&, matrix4d&); 

    extern const double PI;
    extern const mesh CUBE;
}

#endif
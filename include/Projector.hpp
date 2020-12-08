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
        array< float, 4 > p;

        vector4d operator+(vector4d&);
        vector4d operator-(vector4d&);
        float& operator[](size_t);

        float& at(size_t);
        int32_t round(size_t);
    };

    struct matrix4d {
        array< array< float, 4 >, 4 > p;

        array< float, 4 >& operator[](size_t);

        /*
        *   Fill matrix with specific values
        */
        void fill(
            float, float, float, float,
            float, float, float, float,
            float, float, float, float,
            float, float, float, float
        );

        /*
        *   Fill matrix with one specific value
        */
        void fillAll(float);

        vector4d operator*(vector4d);
        matrix4d operator*(matrix4d);

        /*
        *   Master method for matrix by matrix multiplication
        */
        matrix4d multiplyByMatrix(matrix4d&);

        /*
        *   Master method for matrix by vector multiplication
        */
        vector4d multiplyByVector(vector4d&);
    };

    struct triangle {
        array< vector4d, 3 > points;
    };


    struct mesh {
        dyn_array< triangle > triangles;

        /*
        *   Return the count of the triangles in the mesh
        */
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
    matrix4d createProjectionMatrix(const float&, const float&, const float&, const float&);

    /*
    *   Creates an X rotation matrix with specified angle Theta
    */
    matrix4d createXRotationMatrix(float); 

    /*
    *   Creates a Y rotation matrix with specified angle Theta
    */
    matrix4d createYRotationMatrix(float); 

    /*
    *   Creates a Z rotation matrix with specified angle Theta
    */
    matrix4d createZRotationMatrix(float); 

    /*
    *   Translates point by a vector
    */
    vector4d translatePoint(vector4d&, vector4d&);
    vector4d translatePoint(vector4d&, vector4d&, matrix4d&);

    /*
    *   Implementation of dot product of two vectors
    */
    float dotProduct(vector4d&, vector4d&);

    /*
    *   Implementation of cross product of two vectors
    */
    vector4d crossProduct(vector4d&, vector4d&);

    /*
    *   Computes the triangle's normal
    */
    vector4d getNormalOfTriangle(triangle&);

    /*
    *   Divides vector by its length
    */
    vector4d normalize(vector4d&);

    /*
    *   Projects a 3D point to 2D display
    */
    vector4d projectPoint(vector4d&, matrix4d&); 

    extern const float PI;
    extern const mesh CUBE;
}

#endif
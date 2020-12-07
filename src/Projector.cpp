#include "Projector.hpp"

constexpr double& projector::vector4d::operator[](size_t index) {
    if (index < this->p.size() && index >= 0)
        return this->p[index];
        
    else
        throw std::out_of_range("");
    
}

int32_t projector::vector4d::round(size_t index) {

    return static_cast<int32_t>( std::round(this->operator[](index)) );
}

const array< double, 4 >& projector::matrix4d::operator[](size_t index) {
    return this->p[index];
}

void projector::matrix4d::fill(
    double p00, double p01, double p02, double p03,
    double p10, double p11, double p12, double p13,
    double p20, double p21, double p22, double p23,
    double p30, double p31, double p32, double p33
) {
    this->p = {
        p00, p01, p02, p03,
        p10, p11, p12, p13,
        p20, p21, p22, p23,
        p30, p31, p32, p33
    };
}

projector::vector4d projector::matrix4d::operator*(vector4d& r) {
    vector4d v;
    for (size_t i = 1; i < 4; ++i)
        v[i] = r[0] * p[0][i] + r[1] * p[1][i] + r[2] * p[2][i] + r[3] * p[3][i];
    return v;
}

size_t projector::mesh::size() {
    return triangles.size();
}

const projector::matrix4d projector::createProjectionMatrix(
    const double& _aspectRatio,
    const double& _fov,
    const double& _zNear,
    const double& _zFar
) {
    const double q = _zFar / (_zFar - _zNear);

    matrix4d m;

    m.fill(
        _aspectRatio * _fov,    0,      0,              0,
        0,                      _fov,   0,              0,
        0,                      0,      q,              1,
        0,                      0,      -_zNear * q,    0
    );

    return m;
}

const projector::vector4d projector::projectPoint(vector4d& _point, matrix4d& _projectionMatrix) {
    vector4d v = _projectionMatrix * _point;
    std::cout << v[0] << v[1] << v[2] << v[3] << std::endl;
    const double& w = v[3];
    if (w != 0) {
        v[0] /= w;
        v[1] /= w;
        v[2] /= w;
        v[3] /= w;
    }
    std::cout << v[0] << v[1] << v[2] << v[3] << std::endl;
    return v;
}

const double projector::PI = 3.14159265359;

const projector::mesh projector::CUBE {
    mesh{{
        // SOUTH
        triangle{ 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0 },
        triangle{ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0 }, 

        // EAST
        triangle{ 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
        triangle{ 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 }, 

        // NORTH
        triangle{ 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0 },
        triangle{ 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0 },

        // WEST
        triangle{ 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0 },
        triangle{ 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0 },

        // TOP
        triangle{ 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
        triangle{ 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

        // BOTTOM
        triangle{ 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0 },
        triangle{ 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 }
    }}
};

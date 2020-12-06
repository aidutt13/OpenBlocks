#include "Projector.hpp"

size_t projector::mesh::size() {
    return triangles.size();
}

const Eigen::Matrix4d projector::createProjectionMatrix(
    const double& _aspectRatio,
    const double& _fov,
    const double& _zNear,
    const double& _zFar
) {
    const double f = 1 / std::tan(_fov / 2.0f);
    const double q = _zFar / (_zFar - _zNear);

    Matrix4d m;
    m <<    _aspectRatio * f, 0,            0,              0,
            0,                f,            0,              0,
            0,                0,            q,              1,
            0,                0,            -_zNear * q,    0;

    return m;
}

const Eigen::Vector4d projector::projectPoint(const Vector4d& _point, const Matrix4d& _projectionMatrix) {
    Vector4d v = _projectionMatrix * _point;
    double w = v[3];
    if (w != 0) {
        v[0] /= w;
        v[1] /= w;
        v[2] /= w;
        v[3] /= w;
    }

    return v;
}

const double projector::PI = 3.14159265359;

const projector::mesh projector::CUBE {
    mesh{{
        // SOUTH
        triangle{ Vector4d(0.0, 0.0, 0.0, 1.0), Vector4d(0.0, 1.0, 0.0, 1.0), Vector4d(1.0, 1.0, 0.0, 1.0) },
        triangle{ Vector4d(1.0, 0.0, 0.0, 1.0), Vector4d(0.0, 0.0, 0.0, 1.0), Vector4d(1.0, 1.0, 0.0, 1.0) }, 

        // EAST
        triangle{ Vector4d(1.0, 0.0, 0.0, 1.0), Vector4d(1.0, 1.0, 0.0, 1.0), Vector4d(1.0, 1.0, 1.0, 1.0) },
        triangle{ Vector4d(1.0, 0.0, 1.0, 1.0), Vector4d(1.0, 0.0, 0.0, 1.0), Vector4d(1.0, 1.0, 1.0, 1.0) }, 

        // NORTH
        triangle{ Vector4d(1.0, 0.0, 1.0, 1.0), Vector4d(1.0, 1.0, 1.0, 1.0), Vector4d(0.0, 1.0, 1.0, 1.0) },
        triangle{ Vector4d(0.0, 0.0, 1.0, 1.0), Vector4d(1.0, 0.0, 1.0, 1.0), Vector4d(0.0, 1.0, 1.0, 1.0) },

        // WEST
        triangle{ Vector4d(0.0, 0.0, 1.0, 1.0), Vector4d(0.0, 1.0, 1.0, 1.0), Vector4d(0.0, 1.0, 0.0, 1.0) },
        triangle{ Vector4d(0.0, 0.0, 0.0, 1.0), Vector4d(0.0, 0.0, 1.0, 1.0), Vector4d(0.0, 1.0, 0.0, 1.0) },

        // TOP
        triangle{ Vector4d(0.0, 1.0, 0.0, 1.0), Vector4d(0.0, 1.0, 1.0, 1.0), Vector4d(1.0, 1.0, 1.0, 1.0) },
        triangle{ Vector4d(1.0, 1.0, 0.0, 1.0), Vector4d(0.0, 1.0, 0.0, 1.0), Vector4d(1.0, 1.0, 1.0, 1.0) },

        // BOTTOM
        triangle{ Vector4d(0.0, 0.0, 1.0, 1.0), Vector4d(0.0, 0.0, 0.0, 1.0), Vector4d(1.0, 0.0, 0.0, 1.0) },
        triangle{ Vector4d(1.0, 0.0, 1.0, 1.0), Vector4d(0.0, 0.0, 1.0, 1.0), Vector4d(1.0, 0.0, 0.0, 1.0) }
    }}
};

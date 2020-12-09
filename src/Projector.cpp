#include "Projector.hpp"

const float projector::PI = 3.14159f;

projector::vector4d projector::vector4d::operator+(vector4d _vector) {
    vector4d v = *this;

    for (size_t i = 0; i < 4; ++i)
        v[i] += _vector[i];

    return v;
}

projector::vector4d projector::vector4d::operator-(vector4d _vector) {
    vector4d v = *this;

    for (size_t i = 0; i < 4; ++i)
        v[i] -= _vector[i];

    return v;
}

float& projector::vector4d::operator[](size_t index) {

    if (index < this->p.size() && index >= 0)
        return this->p[index];
        
    else
        throw std::out_of_range("");
}

float& projector::vector4d::at(size_t index) {
    
    return this->operator[](index);
}

int32_t projector::vector4d::round(size_t index) {

    return static_cast<int32_t>( std::round(this->at(index)) );
}

array< float, 4 >& projector::matrix4d::operator[](size_t index) {
    return this->p[index];
}

void projector::matrix4d::fill(
    float p00, float p01, float p02, float p03,
    float p10, float p11, float p12, float p13,
    float p20, float p21, float p22, float p23,
    float p30, float p31, float p32, float p33
) {

    this->p = {
        p00, p01, p02, p03,
        p10, p11, p12, p13,
        p20, p21, p22, p23,
        p30, p31, p32, p33
    };
}

void projector::matrix4d::fillAll(float p0) {

    this->p = {
        p0, p0, p0, p0,
        p0, p0, p0, p0,
        p0, p0, p0, p0,
        p0, p0, p0, p0
    };
}

projector::vector4d projector::matrix4d::operator*(vector4d r) {

    return this->multiplyByVector(r);
}

projector::matrix4d projector::matrix4d::operator*(matrix4d r) {

    return this->multiplyByMatrix(r);
}

projector::matrix4d projector::matrix4d::multiplyByMatrix(matrix4d& r) {

    matrix4d m;

    m.fillAll(0.0f);

    matrix4d& t = *this;

    for(size_t i = 0; i < 4; ++i)
        for(size_t j = 0; j < 4; ++j)
            for(size_t k = 0; k < 4; ++k)

                m[i][j] += t[i][k] * r[k][j];

    return m;
}

projector::vector4d projector::matrix4d::multiplyByVector(vector4d& r) {

    vector4d v{ 0.0f, 0.0f, 0.0f, 0.0f };

    for (size_t i = 0; i < 4; ++i)
        for (size_t k = 0; k < 4; ++k)

            v[i] += r[k] * p[k][i];

    return v;
}

size_t projector::mesh::size() {
    return triangles.size();
}

projector::mesh projector::mesh::loadFromFile(std::string& path) {

    std::ifstream f(path);

    if (!f.is_open())
        throw std::exception();

    dyn_array< vector4d > points;

    while (!f.eof()) {
        
    }

}

projector::matrix4d projector::createProjectionMatrix(
    const float& _aspectRatio,
    const float& _fov,
    const float& _zNear,
    const float& _zFar
) {
    const float q = _zFar / (_zFar - _zNear);

    matrix4d m;

    m.fillAll(0.0f);

    // _aspectRatio * _fov,        0.0f,          0.0f,                0.0f,
    // 0.0f,                       _fov,          0.0f,                0.0f,
    // 0.0f,                       0.0f,          q,                   1.0f,
    // 0.0f,                       0.0f,          -_zNear * q,         0.0f

    m[0][0] = _aspectRatio * _fov;
    m[1][1] = _fov;
    m[2][2] = q;
    m[3][2] = -_zNear * q;
    m[2][3] = 1.0f;

    return m;
}

projector::matrix4d projector::createXRotationMatrix(float _theta) {
    matrix4d rotationX;

    rotationX.fillAll(0.0f);

    rotationX[0][0] = 1;
    rotationX[1][1] = std::cos(_theta);
    rotationX[1][2] = std::sin(_theta);
    rotationX[2][1] = -std::sin(_theta);
    rotationX[2][2] = std::cos(_theta);
    rotationX[3][3] = 1;

    return rotationX;
}

projector::matrix4d projector::createYRotationMatrix(float _theta) {
    matrix4d rotationY;

    rotationY.fillAll(0.0f);

    rotationY[0][0] = std::cos(_theta);
    rotationY[0][2] = -std::sin(_theta);
    rotationY[1][1] = 1;
    rotationY[2][0] = std::sin(_theta);
    rotationY[2][2] = std::cos(_theta);
    rotationY[3][3] = 1;

    return rotationY;
}

projector::matrix4d projector::createZRotationMatrix(float _theta) {
    matrix4d rotationZ;

    rotationZ.fillAll(0.0f);

    rotationZ[0][0] = std::cos(_theta);
    rotationZ[0][1] = std::sin(_theta);
    rotationZ[1][0] = -std::sin(_theta);
    rotationZ[1][1] = std::cos(_theta);
    rotationZ[2][2] = 1;
    rotationZ[3][3] = 1;

    return rotationZ;
}

projector::vector4d projector::translatePoint(vector4d& _point, vector4d& _vector) {

    return _point + _vector;
}

projector::vector4d projector::translatePoint(vector4d& _point, vector4d& _vector, matrix4d& rotation) {

    return (rotation * _point) + _vector;
}

float projector::dotProduct(vector4d& a, vector4d& b) {

    return ( a[0] * b[0] ) + ( a[1] * b[1] ) + ( a[2] * b[2] );
}

projector::vector4d projector::crossProduct(vector4d& a, vector4d& b) {
    vector4d cross{ 0.0f, 0.0f, 0.0f, 1.0f };
    
    cross[0] = a[1] * b[2] - a[2] * b[1];
    cross[1] = a[2] * b[0] - a[0] * b[2];
    cross[2] = a[0] * b[1] - a[1] * b[0];

    return cross;
}

projector::vector4d projector::getNormalOfTriangle(triangle& t) {

    vector4d line1, line2, normal;
    normal = { 0.0f, 0.0f, 0.0f, 1.0f };
    line1 = normal, line2 = normal;         // Set all to zero

    for (size_t i = 0; i < 3; ++i) {
        line1[i] = t.points[1].at(i) - t.points[0].at(i);
        line2[i] = t.points[2].at(i) - t.points[0].at(i);
    }

    return crossProduct(line1, line2);
}

projector::vector4d projector::normalize(vector4d& n) {

    float length = std::sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

    n[0] /= length;
    n[1] /= length;
    n[2] /= length;

    return n;
}

projector::vector4d projector::projectPoint(vector4d& _point, matrix4d& _projectionMatrix) {
    
    vector4d v;

    v = _projectionMatrix * _point;

    const float& w = v[3];
    if (w != 0) {
        v[0] /= w;
        v[1] /= w;
        v[2] /= w;
        v[3] /= w;
    }
    return v;
}

projector::mesh projector::projectObjectToScreen(object::Object* obj, projection_variables& vars) {

    mesh _mesh = obj->getObjectMesh();
    mesh ret;
    matrix4d projectionMatrix = createProjectionMatrix(
        vars.aspectRatio,
        vars.fov,
        vars.zNear,
        vars.zFar
    );

    matrix4d translation = obj->getRotationMatrix() * obj->getScaleMatrix();

    for (triangle& t : _mesh.triangles) {
        
        for (size_t i = 0; i < 3; ++i) {
            vector4d position = obj->getWorldPosition();
            t.points[i] = translatePoint(t.points[i], position, translation);
        }

        vector4d triangleNormal = getNormalOfTriangle(t);
        normalize(triangleNormal);

        vector4d trianglePoint = t.points[0] - vars.camera_pos;

        if (dotProduct(triangleNormal, trianglePoint) < 0.0f) {
            ret.triangles.push_back({0.0f, 0.0f, 0.0f, 1.0f});
            triangle& retTriangle = ret.triangles.back();
            for (size_t i = 0; i < 3; ++i) {
                retTriangle.points[i] = 
                    projectPoint(t.points[i], projectionMatrix);
            }
        }
    }

    return ret;
}

const projector::mesh projector::CUBE {
    mesh{{
        // SOUTH
        triangle{ 0.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f, 0.0f, 1.0f },
        triangle{ 1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f, 0.0f, 1.0f }, 

        // EAST
        triangle{ 1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f },
        triangle{ 1.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, 

        // NORTH
        triangle{ 1.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 1.0f, 1.0f },
        triangle{ 0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 1.0f, 1.0f },

        // WEST
        triangle{ 0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f, 1.0f },
        triangle{ 0.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f, 1.0f },

        // TOP
        triangle{ 0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f },
        triangle{ 1.0f, 1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f },

        // BOTTOM
        triangle{ 0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f },
        triangle{ 1.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f }
    }}
};

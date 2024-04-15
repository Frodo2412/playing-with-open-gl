#pragma once

#include <cmath>

class vertex
{
    float x_, y_, z_;

    float length_ = x_ * x_ + y_ * y_ + z_ * z_;
    float magnitude_ = std::sqrt(length_);

public:
    explicit vertex(const float x = 0.0, const float y = 0.0, const float z = 0.0) : x_(x), y_(y), z_(z)
    {
    }

    // Getter methods for the coordinates
    float get_x() const;
    float get_y() const;
    float get_z() const;

    float magnitude() const;

    // Setter methods for the coordinates
    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);

    // Operators
    vertex operator+(const vertex& other) const;
    void operator+=(const vertex& other);
    vertex operator -(const vertex& other) const;
    vertex operator*(float s) const;
    vertex operator*(const vertex& other) const;
    vertex operator/(int s) const;
    vertex operator-() const;

    float dot_product(const vertex& other) const;
    float angle_with(const vertex& other) const; // returns in radians

    vertex normalize() const;
    vertex symmetrical(const vertex& other) const;

    static vertex zero();
    void reset();
    
};

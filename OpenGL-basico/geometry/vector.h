#pragma once

#include <cmath>

class vector
{
    float x_, y_, z_;

    float length_ = x_ * x_ + y_ * y_ + z_ * z_;
    float magnitude_ = std::sqrt(length_);

public:
    explicit vector(const float x = 0.0, const float y = 0.0, const float z = 0.0) : x_(x), y_(y), z_(z)
    {
    }

    // Getter methods for the coordinates
    float get_x() const;
    float get_y() const;
    float get_z() const;

    // Setter methods for the coordinates
    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);

    // Operators
    vector operator+(const vector& other) const;
    void operator+=(const vector& other);
    vector operator -(const vector& other) const;
    vector operator*(float s) const;
    vector operator*(const vector& other) const;
    vector operator/(int s) const;
    vector operator-() const;

    float dot_product(const vector& other) const;
    float angle_with(const vector& other) const; // returns in radians

    vector normalize() const;
    vector symmetrical(const vector& other) const;

    static vector zero();
    void reset();
    
};

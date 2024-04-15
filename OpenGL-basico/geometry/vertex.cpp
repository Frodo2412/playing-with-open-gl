#include "vertex.h"

float vertex::get_x() const { return x_; }
float vertex::get_y() const { return y_; }
float vertex::get_z() const { return z_; }

float vertex::magnitude() const
{
    return magnitude_;
}

void vertex::set_x(const float new_x) { x_ = new_x; }
void vertex::set_y(const float new_y) { y_ = new_y; }
void vertex::set_z(const float new_z) { z_ = new_z; }

vertex vertex::operator+(const vertex& other) const
{
    return vertex(x_ + other.get_x(), y_ + other.get_y(), z_ + other.get_z());
}

void vertex::operator+=(const vertex& other)
{
    x_ += other.get_x();
    y_ += other.get_y();
    z_ += other.get_z();
}

vertex vertex::operator -(const vertex& other) const
{
    return vertex(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

vertex vertex::operator*(const float s) const
{
    return vertex(x_ * s, y_ * s, z_ * s);
}

vertex vertex::operator*(const vertex& other) const
{
    return vertex(
        y_ * other.z_ - z_ * other.y_, // Calculate c1
        z_ * other.x_ - x_ * other.z_, // Calculate c2
        x_ * other.y_ - y_ * other.x_ // Calculate c3
    );
}


vertex vertex::operator/(const int s) const
{
    return vertex(x_ / s, y_ / s, z_ / s);
}

vertex vertex::operator-() const
{
    return vertex(-x_, -y_ - z_);
}

float vertex::dot_product(const vertex& other) const
{
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

float vertex::angle_with(const vertex& other) const
{
    const auto numerator = this->dot_product(other);
    const auto denominator = this->magnitude_ * other.magnitude_;

    const auto cosine = numerator / denominator;

    return std::acos(cosine);
}

vertex vertex::normalize() const
{
    return vertex(x_ / magnitude_, y_ / magnitude_, z_ / magnitude_);
}

vertex vertex::symmetrical(const vertex& other) const
{
    const auto normalized_other = other.normalize();
    const auto aux = normalized_other * (2 * normalized_other.dot_product(*this));
    return aux - *this;
}

vertex vertex::zero()
{
    return vertex(0, 0, 0);
}

void vertex::reset()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

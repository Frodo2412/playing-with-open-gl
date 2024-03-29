#include "vector.h"

float vector::get_x() const { return x_; }
float vector::get_y() const { return y_; }
float vector::get_z() const { return z_; }

void vector::set_x(const float new_x) { x_ = new_x; }
void vector::set_y(const float new_y) { y_ = new_y; }
void vector::set_z(const float new_z) { z_ = new_z; }

vector vector::operator+(const vector& other) const
{
    return vector(x_ + other.get_x(), y_ + other.get_y(), z_ + other.get_z());
}

vector vector::operator -(const vector& other) const
{
    return vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

vector vector::operator*(const float s) const
{
    return vector(x_ * s, y_ * s, z_ * s);
}

vector vector::operator*(const vector& other) const
{
    return vector(
        y_ * other.z_ - z_ * other.y_, // Calculate c1
        z_ * other.x_ - x_ * other.z_, // Calculate c2
        x_ * other.y_ - y_ * other.x_ // Calculate c3
    );
}


vector vector::operator/(const int s) const
{
    return vector(x_ / s, y_ / s, z_ / s);
}

vector vector::operator-() const
{
    return vector(-x_, -y_ - z_);
}

float vector::dot_product(const vector& other) const
{
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

float vector::angle_with(const vector& other) const
{
    const auto numerator = this->dot_product(other);
    const auto denominator = this->magnitude_ * other.magnitude_;

    const auto cosine = numerator / denominator;

    return std::acos(cosine);
}

vector vector::normalize() const
{
    return vector(x_ / magnitude_, y_ / magnitude_, z_ / magnitude_);
}

vector vector::symmetrical(const vector& other) const
{
    const auto normalized_other = other.normalize();
    const auto aux = normalized_other * (2 * normalized_other.dot_product(*this));
    return aux - *this;
}

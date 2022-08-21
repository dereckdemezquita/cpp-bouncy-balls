//
// Created by Dereck on 8/20/22.
//

#include "Vec2.h"

Vec2::Vec2(double x, double y) {
    this -> x = x;
    this -> y = y;
}

Vec2 Vec2::operator+(Vec2 v) const {
    return Vec2(this -> x + v.x, this -> y + v.y);
}

Vec2 Vec2::operator-(Vec2 v) const {
    return Vec2(this -> x - v.x, this -> y - v.y);
}

Vec2 Vec2::operator*(double scalar) const {
    return Vec2(this -> x * scalar, this -> y * scalar);
}

Vec2 Vec2::operator/(Vec2 v) const {
    return Vec2(this -> x / v.x, this -> y / v.y);
}

double Vec2::getMagnitude() const {
    return sqrt(pow(this -> x, 2) + pow(this -> y, 2));
}

// calculate magnitude
// magnitude = sqrt(pow(x, 2) + pow(y, 2))
Vec2 Vec2::normalise() const {
    if (this -> getMagnitude() > 0) return Vec2(this -> x / this -> getMagnitude(), this -> y / this -> getMagnitude());

    // error
    throw std::runtime_error("Cannot normalise a vector with a magnitude of 0");
}

// dot product returns scalar
// scalar is a magnitude calculated from two vectors
double Vec2::dot(Vec2 v) const {
    return (this -> x * v.x) + (this -> y * v.y);
}

// pythagoras theorem to find distance between two points
double Vec2::distance(Vec2 v) const {
    const double lX = this -> x - v.x;
    const double lY = this -> y - v.y;

    return sqrt(pow(lX, 2) + pow(lY, 2));
}

// returns normalised vector
// values between 0 and 1
Vec2 Vec2::direction(Vec2 v) const {
    return v.subtract(*this).normalise();
}

// convert cartesian coordinates to radian angle
double Vec2::toAngle() const {
    return atan2(this -> y, this -> x);
}

Vec2 Vec2::fromAngle(double radians) {
    return Vec2(cos(radians), sin(radians));
}




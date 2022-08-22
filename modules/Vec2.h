//
// Created by Dereck on 8/20/22.
//

#ifndef CPP_BOUNCY_BALLS_VEC2_H
#define CPP_BOUNCY_BALLS_VEC2_H

#include <cmath>
#include <stdexcept>

class Vec2 {
    public:
        double x, y;

        explicit Vec2(double x = 0, double y = 0);

        [[nodiscard]] Vec2 operator+(Vec2 v) const;

        Vec2& operator+=(Vec2 v);

        [[nodiscard]] Vec2 operator-(Vec2 v) const;

        Vec2& operator-=(Vec2 v);

        [[nodiscard]] Vec2 operator*(double scalar) const;

        Vec2& operator*=(Vec2 v);

        [[nodiscard]] Vec2 operator/(Vec2 v) const;

        Vec2& operator/=(Vec2 v);

        [[nodiscard]] double getMagnitude() const;

        [[nodiscard]] Vec2 normalise() const;

        [[nodiscard]] double dot(Vec2 v) const;

        [[nodiscard]] double distance(Vec2 v) const;

        [[nodiscard]] Vec2 direction(Vec2 v) const;

        [[nodiscard]] double toAngle() const;

        // static method fromAngle
        static Vec2 fromAngle(double radians);
};


#endif //CPP_BOUNCY_BALLS_VEC2_H

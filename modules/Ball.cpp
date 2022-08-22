//
// Created by $MY_NAME on 8/21/22.
//

#include "Ball.h"

Ball::Ball(
    double x,
    double y,
    float radius,
    double vX,
    double vY,
    double elasticity,
    sf::Color colour
) : sf::CircleShape(radius)  {

    this -> position = Vec2(x, y);
    this -> radius = radius;
    this -> velocity = Vec2(vX, vY);
    this -> colour = colour;

    if (elasticity > 1) {
        this -> elasticity = 1;
    } else if (elasticity < 0) {
        this -> elasticity = 0;
    } else {
        this -> elasticity = elasticity;
    }

    this -> mass = M_PI * pow(radius, 2) * density;
    this -> energy = (this -> mass / 2) * pow(velocity.getMagnitude(), 2);

    // set origin so when click centre of ball
    setOrigin(getRadius(), getRadius());
    setPosition((float)this -> position.x, (float)this -> position.y);
}

void Ball::addEnergy(double energy) {
    this -> energy += energy;
    this -> calculateVelocity();
}

void Ball::removeEnergy(double energy) {
    const double newEnergy = this -> energy - energy;

    if (newEnergy < 0) {
        this -> energy = 0;
    } else {
        this -> energy = newEnergy;
    }
}

void Ball::calculateVelocity() {
    // e = mc^2
    // c = sqrt(e / m / 2)
    double newMagnitude = sqrt(this -> energy / this -> mass / 2);

    round(newMagnitude) == 0 ? this -> velocity = Vec2() : this -> velocity = this -> velocity.normalise() * newMagnitude;
}

void Ball::calculateEnergy() {
    // e = (c^2) * m / 2
    this -> energy = (pow(this -> velocity.getMagnitude(), 2) * (this -> mass / 2));
}

void Ball::applyForce(Vec2 force) {
    this -> velocity = this -> velocity + force;
    this -> calculateEnergy();
}

void Ball::setDirection(Vec2 direction) {
    this -> velocity = direction * this -> velocity.getMagnitude();
}



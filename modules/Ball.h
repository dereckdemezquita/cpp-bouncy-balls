//
// Created by $MY_NAME on 8/21/22.
//

#ifndef CPP_BOUNCY_BALLS_BALL_H
#define CPP_BOUNCY_BALLS_BALL_H

#include "Vec2.h"
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>


class Ball : public sf::CircleShape {
    public:
        double energy = 0;
        double elasticity = 1;
        bool xColliding = false;
        bool yColliding = false;
        Vec2 position, velocity;
        double mass;
        float radius;

        double density = 0.01;

        sf::Color colour;

        explicit Ball(
            double x = 0,
            double y = 0,
            float radius = 5,
            double vX = 0,
            double vY = 0,
            double elasticity = 1,
            sf::Color colour = sf::Color{ 0x0000FFFF }
        );

        // takes a number to add energy to the ball
        // we are adding to the normalised vector of the velocity
        void addEnergy(double energy);

        void removeEnergy(double energy);

        // kinetic energy is calculated by m/2 * velocity ^ 2
        // we are calculating the magnitude of the ball
        // reminder magnitude is the length of a vector
        // then we can apply (multiply) the magnitude to the velocity after it is normalised
        void calculateVelocity();

        void calculateEnergy();

        void applyForce(Vec2 force);

        // changes the direction without affecting the magnitude
        // so no need to update energy etc
        void setDirection(Vec2 direction);
};


#endif //CPP_BOUNCY_BALLS_BALL_H

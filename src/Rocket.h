#ifndef ROCKET_H
#define ROCKET_H
#include <cstdint>
#include <raylib.h>
#include <stdexcept>
#include <string>

#include "IDrawable.h"


class Rocket : public IDrawable {
public:
    Rocket(const std::string &pathToRocketSprite,
        const std::string &pathToFireSprite,
        const std::string &pathToBgPath,
        double mass, double criticalMass,
        double massVelocity, double gasVelocity,
        double timePerFrame, double radius);


    void Draw(uint32_t posX, uint32_t posY) const override;

    double getResForce();

    double getGravForce();

    double getHeight() { return height; }

    double getVelocity() { return velocity; }

    void Update();

private:
    Texture2D rocketSprite;
    Texture2D fireSprite;
    Texture2D bgSprite;

    double rocketY;

    double height = 0;
    double mass;
    double criticalMass;
    double massVelocity;
    double gasVelocity;
    double timePerFrame;
    double velocity = 0;

    double Cd = 0.82f;
    double area;

    bool isFlying = false;
};

class RocketBuilder {
public:

    RocketBuilder* AddMass(double mass) {
        this->mass = mass;
        isMassInitialized = true;
        return this;
    }

    RocketBuilder* AddCriticalMass(double mass) {
        this->criticalMass = mass;
        isCriticalMassInitialized = true;
        return this;
    }

    RocketBuilder* AddMassVelocity(double massVelocity) {
        this->massVelocity = massVelocity;
        isMassVelocityInitialized = true;
        return this;
    }

    RocketBuilder* AddGasVelocity(double gasVelocity) {
        this->gasVelocity = gasVelocity;
        isGasVelocityInitialized = true;
        return this;
    }

    RocketBuilder* AddTimePerFrame(double timePerFrame) {
        this->timePerFrame = timePerFrame;
        isTimePerFrameInitialized = true;
        return this;
    }

    RocketBuilder* AddRadius(double radius) {
        this->radius = radius;
        isRadiusInitialized = true;
        return this;
    }

    Rocket Build() {
        if (!isMassInitialized || !isCriticalMassInitialized
            || !isMassVelocityInitialized || !isGasVelocityInitialized
            || !isTimePerFrameInitialized) throw std::invalid_argument("RocketBuilder::Build");

        return Rocket("../data/rocket.png", "../data/rocketFlame.png", "../data/bg.png",mass, criticalMass, massVelocity, gasVelocity, timePerFrame, radius);
    }

private:
    double mass;
    bool isMassInitialized = false;

    double criticalMass;
    bool isCriticalMassInitialized = false;

    double massVelocity;
    bool isMassVelocityInitialized = false;

    double gasVelocity;
    bool isGasVelocityInitialized = false;

    double timePerFrame;
    bool isTimePerFrameInitialized = false;

    double radius;
    bool isRadiusInitialized = false;
};



#endif //ROCKET_H

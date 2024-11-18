#include "Rocket.h"

#include <cmath>
#include <iostream>
#include <bits/stl_algo.h>


Rocket::Rocket(const std::string &pathToRocketSprite, const std::string &pathToFireSprite,
               const std::string &pathToBgPath, double mass, double criticalMass, double massVelocity, double gasVelocity,
               double timePerFrame, double radius) : mass(mass), criticalMass(criticalMass), massVelocity(massVelocity), gasVelocity(gasVelocity), timePerFrame(timePerFrame), area(radius * radius * std::numbers::pi) {

    auto rocketImage = LoadImage(pathToRocketSprite.c_str());
    auto fireImage = LoadImage(pathToFireSprite.c_str());
    ImageResize(&rocketImage, 100, 200);
    ImageResize(&fireImage, 200, 90);

    rocketSprite = LoadTextureFromImage(rocketImage);
    fireSprite = LoadTextureFromImage(fireImage);
    bgSprite = LoadTextureFromImage(LoadImage(pathToBgPath.c_str()));
    rocketY = 200.0f;
}

void Rocket::Draw(uint32_t posX, uint32_t posY) const {
    DrawTextureRec(
        bgSprite,
        Rectangle(0, bgSprite.height - posY - rocketY, 450, 400),
        Vector2(posX - bgSprite.width / 2 + rocketSprite.width / 2,
        posY - 150), WHITE);

    DrawTexture(rocketSprite, posX, posY, WHITE);
    if (isFlying) {
        DrawTextureEx(fireSprite, Vector2(posX + 148.0f, posY + 285.0f),
            180.0f, 1.0f,
            WHITE);
    }
}

double Rocket::getResForce() {
    double B = 5.6e-2;
    double p0 = 129.0;
    double p = p0 * std::pow(10, -B * height);
    double k2 = 0.5 * area * p * 0.5;
    return k2 * pow(velocity, 2);
}


double Rocket::getGravForce() {
    double G = 9.8;
    double M = 2e5;
    double R = 6378.0;
    return G * M * mass / pow(R + height, 2.0);
}

void Rocket::Update() {
    isFlying = true;
    mass -= massVelocity * timePerFrame;
    mass = std::max(mass, criticalMass);
    if (criticalMass >= mass) {
        isFlying = false;
    }

    double dv = ( (isFlying ? massVelocity * gasVelocity : 0 ) - getResForce() - getGravForce()) / mass * timePerFrame;
    velocity += dv;
    rocketY += velocity * timePerFrame;
    rocketY = std::clamp(rocketY, 200.0, (double)bgSprite.height - 250.0);
    if (rocketY >= bgSprite.height - 250.0) {
        rocketY = bgSprite.height - 903.0;
    }
    height += velocity * timePerFrame;
}

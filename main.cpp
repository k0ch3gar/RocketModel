#include <iostream>
#include <raylib.h>
#include <vector>
#include <cmath>
#include <GraphDrawer.h>
#include <Window.h>
#include <Rocket.h>
#include <Button.h>

int main() {

    const int screenWidth = 1600;
    const int screenHeight = 600;
    Window mainWindow(screenWidth, screenHeight, "RocketModel");

    GraphDrawerBuilder builder;
    GraphDrawer testGraph = builder
    .AddColor(WHITE)
    ->AddHeight(490)
    ->AddWidth(400)
    ->AddXMax(160)
    ->AddYMax(10)
    ->AddXPartition(7)
    ->AddYPartition(15)
    ->AddXUnit("h, (km)")
    ->AddYUnit("V, (km/c)")
    ->AddGraphFunction([](float x) {return x * 2.0f;})
    ->Build();

    testGraph.FullMode(false);

    Button startButton({ screenWidth / 2 - 150, screenHeight - 100, 100, 50}, "START");

    RocketBuilder rocketBuilder;
    Rocket rocket = rocketBuilder
    .AddGasVelocity(4.0f)
    ->AddMassVelocity(1e7  * 0.25)
    ->AddCriticalMass(1e7 * 0.03)
    ->AddMass(1e7)
    ->AddTimePerFrame(1.0f)
    ->AddRadius(25.0f)
    ->Build();

    SetTargetFPS(60);
    mainWindow.AddDrawable(testGraph, 100, 500);
    mainWindow.AddDrawable(rocket, 1000, 250);
    mainWindow.AddDrawable(startButton, 1000, 500);

    bool isStarted = false;
    float time = 0;

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        if (startButton.checkCollision(mousePoint) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            isStarted = true;
        }
        mainWindow.Render();
        if (isStarted) {
            time += 0.1f;
            rocket.Update();
            testGraph.AddPoint(rocket.getHeight(), rocket.getVelocity());
        }
    }

    CloseWindow();
    return 0;
}

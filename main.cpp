#include <raylib.h>
#include <vector>
#include <cmath>
#include <GraphDrawer.h>
#include <Window.h>
#include <Rocket.h>
#include <Button.h>

int main() {

    const int screenWidth = 1920;
    const int screenHeight = 600;
    Window mainWindow(screenWidth, screenHeight, "RocketModel");

    GraphDrawerBuilder builder;
    GraphDrawer testGraph = builder
    .AddColor(WHITE)
    ->AddHeight(460)
    ->AddWidth(400)
    ->AddXMax(1)
    ->AddYMax(1)
    ->AddYMin(0)
    ->AddXMin(0)
    ->AddXPartition(7)
    ->AddYPartition(15)
    ->AddXUnit("h, (km)")
    ->AddYUnit("V, (km/c)")
    ->AddGraphFunction([](float x) {return x * 2.0f;})
    ->Build();

    const double framesPerSecond = 60;

    testGraph.FullMode(false);

    Button startButton({ screenWidth / 2 - 300, screenHeight - 100, 100, 50}, "START");

    RocketBuilder rocketBuilder;
    Rocket rocket = rocketBuilder
    .AddGasVelocity(2.0)
    ->AddMassVelocity(2e7 * 0.05)
    ->AddCriticalMass(2e7 * 0.03)
    ->AddMass(2e7)
    ->AddTimePerFrame(1)
    ->AddRadius(25.0f)
    ->Build();

    GraphDrawer phaseGraph = builder
            .AddColor(WHITE)
            ->AddHeight(460)
            ->AddWidth(400)
            ->AddXMax(2e7)
            ->AddYMax(10000)
            ->AddYMin(-10000)
            ->AddXMin(1e7 * 0.03)
            ->AddXPartition(7)
            ->AddYPartition(15)
            ->AddXUnit("m, (kg)")
            ->AddYUnit("F, (H)")
            ->AddGraphFunction([](float x) { return x * 2.0f; })
            ->Build();
    phaseGraph.FullMode(false);

    SetTargetFPS(framesPerSecond);
    mainWindow.AddDrawable(testGraph, 100, 500);
    mainWindow.AddDrawable(rocket, 1000, 250);
    mainWindow.AddDrawable(startButton, 1000, 500);
    mainWindow.AddDrawable(phaseGraph, 1400, 500);

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
            phaseGraph.AddPoint(rocket.getMass(), rocket.getForce());
        }
    }

    CloseWindow();
    return 0;
}

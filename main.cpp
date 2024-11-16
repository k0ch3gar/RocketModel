#include <iostream>
#include <raylib.h>
#include <vector>
#include <src/GraphDrawer.hpp>

int main() {
    // Инициализация окна
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "График: Скорость от времени");

    // Данные для графика
    std::vector<float> times = {0, 1, 2, 3, 4, 5}; // Время
    std::vector<float> speeds = {0, 10, 20, 15, 30, 25}; // Скорость

    // Настройки графика
    const int graphWidth = 600;   // Ширина графика
    const int graphHeight = 400; // Высота графика
    const int graphX = 100;      // Смещение по X
    const int graphY = 500;      // Смещение по Y (нижняя граница)
    const float maxSpeed = 40;   // Максимальная скорость (для масштаба)
    const float maxTime = 5;     // Максимальное время (для масштаба)

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Рисуем оси
        DrawLine(graphX, graphY, graphX + graphWidth, graphY, BLACK); // Ось X
        DrawLine(graphX, graphY, graphX, graphY - graphHeight, BLACK); // Ось Y

        // Подписи осей
        DrawText("Time", graphX + graphWidth + 10, graphY, 20, BLACK);
        DrawText("Speed", graphX - 50, graphY - graphHeight - 10, 20, BLACK);

        // Рисуем данные графика
        for (size_t i = 0; i < times.size() - 1; ++i) {
            // Преобразуем координаты в пиксели
            float x1 = graphX + (times[i] / maxTime) * graphWidth;
            float y1 = graphY - (speeds[i] / maxSpeed) * graphHeight;
            float x2 = graphX + (times[i + 1] / maxTime) * graphWidth;
            float y2 = graphY - (speeds[i + 1] / maxSpeed) * graphHeight;

            DrawLine(x1, y1, x2, y2, RED); // Соединяем точки линией
        }

        // Рисуем точки
        for (size_t i = 0; i < times.size(); ++i) {
            float x = graphX + (times[i] / maxTime) * graphWidth;
            float y = graphY - (speeds[i] / maxSpeed) * graphHeight;
            DrawCircle(x, y, 5, BLUE); // Отмечаем точки на графике
        }

        EndDrawing();
    }

    CloseWindow(); // Закрываем окно
    return 0;
}

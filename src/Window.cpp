//
// Created by kosti on 17.11.2024.
//

#include "Window.h"
#include "IDrawable.h"

#include <list>
#include <raylib.h>


Window::Window(uint32_t width, uint32_t height, std::string title) : width(width), height(height), title(title) {
    InitWindow(width, height, title.c_str());
}

Window::~Window() {
    drawables.clear();
    CloseWindow();
}

void Window::Render() const {
    ClearBackground(BLACK);
    BeginDrawing();
    for (const auto& drawable : drawables) {
        drawable.drawable->Draw(drawable.position.x, drawable.position.y);
    }
    EndDrawing();
}

void Window::AddDrawable(IDrawable &drawable, uint32_t posX, uint32_t posY) {
    drawables.emplace_back(&drawable, Vector2(posX, posY));
}

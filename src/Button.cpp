//
// Created by kosti on 17.11.2024.
//

#include "Button.h"

bool Button::checkCollision(Vector2 point) {
    return CheckCollisionPointRec(point, buttonRect);
}

void Button::Draw(uint32_t posX, uint32_t posY) const {
    DrawRectangleRec(buttonRect, RAYWHITE);
    DrawText(text.c_str(), buttonRect.x + buttonRect.width / 2 - 15, buttonRect.y + buttonRect.height / 2, 15, GRAY);
}


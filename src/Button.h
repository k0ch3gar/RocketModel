//
// Created by kosti on 17.11.2024.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <cstdint>
#include <raylib.h>
#include <string>

#include "IDrawable.h"


class Button : public IDrawable {
public:
    Button(Rectangle rectangle, std::string text) : buttonRect(rectangle), text(text) { };

    bool checkCollision(Vector2 point);

    void Draw(uint32_t posX, uint32_t posY) const override;
private:
    Rectangle buttonRect;
    std::string text;
};



#endif //BUTTON_H

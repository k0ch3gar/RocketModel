//
// Created by kosti on 17.11.2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <cstdint>
#include <list>
#include <raylib.h>
#include <string>

#include "IDrawable.h"


class Window {
public:

    struct Drawable {
        IDrawable* drawable;
        Vector2 position;
    };

    Window(uint32_t width, uint32_t height, std::string title);
    ~Window();

    void Render() const;
    void AddDrawable(IDrawable& drawable, uint32_t posX, uint32_t posY);

private:
    uint32_t width;
    uint32_t height;
    std::string title;

    std::list<Drawable> drawables;
};



#endif //WINDOW_H

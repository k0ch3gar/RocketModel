//
// Created by kosti on 17.11.2024.
//

#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable {
public:
    virtual void Draw(uint32_t posX, uint32_t posY) const = 0;
};

#endif //IDRAWABLE_H

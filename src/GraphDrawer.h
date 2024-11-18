//
// Created by kosti on 16.11.2024.
//

#ifndef GRAPHDRAWER_HPP
#define GRAPHDRAWER_HPP
#include <cstdint>
#include <functional>
#include <utility>
#include <raylib.h>
#include <string>

#include "IDrawable.h"

class GraphDrawer : public IDrawable {
public:
    GraphDrawer(uint32_t width, uint32_t height,
                uint32_t xPartition, uint32_t yPartition,
                std::string xUnit, std::string yUnit,
                std::function<float(float)> graphFunction,
                Color color,
                float xMax, float yMax) :
                width(width), height(height),
                xPartition(xPartition), yPartition(yPartition),
                xMax(xMax), yMax(yMax),
                xUnit(std::move(xUnit)),
                yUnit(std::move(yUnit)),
                color(color), graphFunction(std::move(graphFunction)) {}


    void drawFull(uint32_t posX, uint32_t posY);

    void Draw(uint32_t posX, uint32_t posY) const;

    void AddPoint(float x, float y);

    void FullMode(bool flag);

private:

    std::vector<Vector2> points;

    uint32_t width;
    uint32_t height;

    uint32_t xPartition;
    uint32_t yPartition;

    bool fullDraw = true;

    float xMax;
    float yMax;

    std::string xUnit;
    std::string yUnit;

    Color color;

    std::function<float(float)> graphFunction;
};

class GraphDrawerBuilder {
public:
    GraphDrawerBuilder* AddWidth(uint32_t width);

    GraphDrawerBuilder* AddHeight(uint32_t height);

    GraphDrawerBuilder* AddXPartition(uint32_t xPartition);

    GraphDrawerBuilder* AddYPartition(uint32_t yPartition);

    GraphDrawerBuilder* AddXUnit(std::string xUnit);

    GraphDrawerBuilder* AddYUnit(std::string yUnit);

    GraphDrawerBuilder* AddXMax(float xMax);

    GraphDrawerBuilder* AddYMax(float yMax);

    GraphDrawerBuilder* AddGraphFunction(std::function<float(float)> graphFunction);

    GraphDrawerBuilder* AddColor(Color color);

    GraphDrawer Build();

private:
    uint32_t width;
    bool widthInitialized = false;
    uint32_t height;
    bool heightInitialized = false;

    uint32_t xPartition;
    bool xPartitionInitialized = false;
    uint32_t yPartition;
    bool yPartitionInitialized = false;

    float xMax;
    bool xMaxInitialized = false;
    float yMax;
    bool yMaxInitialized = false;

    std::string xUnit;
    bool xUnitInitialized = false;
    std::string yUnit;
    bool yUnitInitialized = false;

    std::function<float(float)> graphFunction;
    bool graphFunctionInitialized = false;

    Color color;
    bool colorInitialized = false;
};

#endif //GRAPHDRAWER_HPP

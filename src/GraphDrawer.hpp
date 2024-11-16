//
// Created by kosti on 16.11.2024.
//

#ifndef GRAPHDRAWER_HPP
#define GRAPHDRAWER_HPP
#include <cstdint>
#include <functional>
#include <utility>
#include <raylib.h>

class GraphDrawer {
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

    void drawFull(uint32_t posX, uint32_t posY) {
        DrawLine(posX, posY, posX, posY + height, color);
        DrawLine(posX, posY, posX + width, posY, color);

        for (float x = 0; x < xMax; x += 0.1f) {
            float y = graphFunction(x);
            DrawPixel(x, y, color);
        }
    }


private:
    uint32_t width;
    uint32_t height;

    uint32_t xPartition;
    uint32_t yPartition;

    float xMax;
    float yMax;

    std::string xUnit;
    std::string yUnit;

    Color color;

    std::function<float(float)> graphFunction;
};

class GraphDrawerBuilder {
public:
    GraphDrawerBuilder* AddWidth(uint32_t width) {
        this->width = width;
        widthInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddHeight(uint32_t height) {
        this->height = height;
        heightInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddXPartition(uint32_t xPartition) {
        this->xPartition = xPartition;
        xPartitionInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddYPartition(uint32_t yPartition) {
        this->yPartition = yPartition;
        yPartitionInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddXUnit(std::string xUnit) {
        this->xUnit = std::move(xUnit);
        xUnitInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddYUnit(std::string yUnit) {
        this->yUnit = std::move(yUnit);
        yUnitInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddXMax(float xMax) {
        this->xMax = xMax;
        xMaxInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddYMax(float yMax) {
        this->yMax = yMax;
        yMaxInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddGraphFunction(std::function<float(float)> graphFunction) {
        this->graphFunction = std::move(graphFunction);
        graphFunctionInitialized = true;
        return this;
    }

    GraphDrawerBuilder* AddColor(Color color) {
        this->color = color;
        colorInitialized = true;
        return this;
    }

    GraphDrawer Build() {
        if (!widthInitialized || !heightInitialized
            || !xPartitionInitialized || !yPartitionInitialized
            || !xUnitInitialized || !yUnitInitialized
            || !graphFunctionInitialized || !colorInitialized
            || !xMaxInitialized || !yMaxInitialized) {
            throw std::invalid_argument("GraphDrawerBuilder could not be initialized");
        }

        return {width, height, xPartition, yPartition, xUnit, yUnit, graphFunction, color, xMax, yMax};
    }

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

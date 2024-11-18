#include "GraphDrawer.h"

#include <raylib.h>
#include <stdexcept>

void GraphDrawer::Draw(uint32_t posX, uint32_t posY) const {
    DrawLine(posX, posY, posX, posY - height, color);
    DrawLine(posX, posY, posX + width, posY, color);
    DrawText(xUnit.c_str(), posX + width, posY - 10.0f, 20, color);
    DrawText(yUnit.c_str(), posX, posY - height - 20.0f, 20, color);

    for (float x = 0; x <= xMax; x += xMax / (float)xPartition) {
        DrawText(std::to_string(x).c_str(), posX + x * width / xMax, posY + 10, 10, color);
        DrawLine(posX + x * width / xMax, posY + 10, posX + x * width / xMax, posY - 10, color);
    }

    for (float y = 0; y <= yMax; y += yMax / (float)yPartition) {
        DrawText(std::to_string(y).c_str(), posX - std::to_string(y).size() * 8, posY - y * height / yMax, 10, color);
        DrawLine(posX + 10, posY - y * height / yMax, posX - 10, posY - y * height / yMax, color);
    }

    float xChange = (float)width / (float)xMax;
    float yChange = (float)height / (float)yMax;

    if (!fullDraw) {
        float prevX = posX;
        float prevY = posY;
        for (const auto& vec2 : points) {
            DrawLine(prevX, prevY, (float)posX + vec2.x * xChange, (float)posY - vec2.y * yChange, color);
            prevX = (float)posX + vec2.x * xChange;
            prevY = (float)posY - vec2.y * yChange;
            //DrawPixel((float)posX + vec2.x * xChange, (float)posY - vec2.y * yChange, color);
        }
        return;
    }

    for (float x = 0; x < xMax; x += 0.1f) {
        float y = graphFunction(x);
        DrawPixel((float)posX + x * xChange, (float)posY - y * yChange, color);
    }
}

void GraphDrawer::AddPoint(float x, float y) {
    points.emplace_back(x, y);
}

void GraphDrawer::FullMode(bool flag) {
    fullDraw = flag;
}

GraphDrawerBuilder* GraphDrawerBuilder::AddWidth(uint32_t width) {
    this->width = width;
    widthInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddHeight(uint32_t height) {
    this->height = height;
    heightInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddXPartition(uint32_t xPartition) {
    this->xPartition = xPartition;
    xPartitionInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddYPartition(uint32_t yPartition) {
    this->yPartition = yPartition;
    yPartitionInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddXUnit(std::string xUnit) {
    this->xUnit = std::move(xUnit);
    xUnitInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddYUnit(std::string yUnit) {
    this->yUnit = std::move(yUnit);
    yUnitInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddXMax(float xMax) {
    this->xMax = xMax;
    xMaxInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddYMax(float yMax) {
    this->yMax = yMax;
    yMaxInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddGraphFunction(std::function<float(float)> graphFunction) {
    this->graphFunction = std::move(graphFunction);
    graphFunctionInitialized = true;
    return this;
}

GraphDrawerBuilder *GraphDrawerBuilder::AddColor(Color color) {
    this->color = color;
    colorInitialized = true;
    return this;
}

GraphDrawer GraphDrawerBuilder::Build() {
    if (!widthInitialized || !heightInitialized
        || !xPartitionInitialized || !yPartitionInitialized
        || !xUnitInitialized || !yUnitInitialized
        || !graphFunctionInitialized || !colorInitialized
        || !xMaxInitialized || !yMaxInitialized) {
        throw std::invalid_argument("GraphDrawerBuilder could not be initialized");
    }

    return {width, height, xPartition, yPartition, xUnit, yUnit, graphFunction, color, xMax, yMax};
}

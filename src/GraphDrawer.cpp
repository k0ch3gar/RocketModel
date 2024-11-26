#include "GraphDrawer.h"

#include <iomanip>
#include <ios>
#include <raylib.h>
#include <stdexcept>

void GraphDrawer::Draw(uint32_t posX, uint32_t posY) const {
    DrawLine(posX, posY, posX, posY - height, color);
    DrawLine(posX, posY, posX + width, posY, color);
    DrawText(xUnit.c_str(), posX + width, posY - 10.0f, 20, color);
    DrawText(yUnit.c_str(), posX, posY - height - 20.0f, 20, color);

    float xChange = (float) width / (float) (xMax - xMin);
    float yChange = (float) height / (float)(yMax - yMin);

    float i = 0;
    for (float x = xMin; x <= xMax; x += (xMax - xMin) / static_cast<float>(xPartition)) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << x;
        std::string s = stream.str();

        DrawText(s.c_str(), posX + i * (float)width / xPartition, posY + 10, 10, color);
        DrawLine(posX + i * (float)width / xPartition, posY + 10, posX + i * (float)width / xPartition, posY - 10, color);
        ++i;
    }

    i = 0;
    for (float y = yMin; y <= yMax; y += (yMax - yMin) / static_cast<float>(yPartition)) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << y;
        std::string s = stream.str();

        DrawText(s.c_str(), posX - std::to_string(y).size() * 8, posY - i * (float)height / yPartition, 10, color);
        DrawLine(posX + 10, posY - i * (float)height / yPartition, posX - 10, posY - i * (height) / yPartition, color);
        ++i;
    }



    if (!fullDraw) {
        if (points.empty()) return;
        float prevX = (float)posX + (abs(xMin) + points.at(0).x) * xChange;
        float prevY = (float)posY - (abs(yMin) + points.at(0).y) * yChange;
        for (const auto& vec2 : points) {

            DrawLine(prevX, prevY, (float)posX + (vec2.x + abs(xMin)) * xChange, (float)posY - (vec2.y + abs(yMin)) * yChange, color);
            prevX = (float)posX + (vec2.x + abs(xMin)) * xChange;
            prevY = (float)posY - (vec2.y + abs(yMin)) * yChange;
        }
        auto vec2 = *points.rbegin();
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << vec2.x;
        std::string s = stream.str();

        DrawText(s.c_str(), prevX + 10, prevY, 10, color);
        stream.clear();
        stream << std::fixed << std::setprecision(2) << vec2.y;
        s = stream.str();

        DrawText(s.c_str(), prevX, prevY + 10, 10, color);
        return;
    }

    for (float x = 0; x < xMax; x += 0.1f) {
        float y = graphFunction(x);
        DrawPixel((float)posX + x + abs(xMin), (float)posY - y + abs(yMin), color);
    }
}

void GraphDrawer::AddPoint(float x, float y) {
    if (x > xMax * 0.9f) {
        if (xMax == 0) xMax += 1.0;
        xMax *= 1.5f;
    }
    if (y > yMax * 0.9f) {
        if (yMax == 0) yMax += 1.0;
        yMax *= 1.5f;
    }
    if (x < xMin * 0.9f) {
        if (xMin == 0) xMin -= 1.0;
        xMin *= 2.5f;
    }
    if (y < yMin * 0.9f) {
        if (yMin == 0) yMin -= 1.0;
        yMin *= 2.5f;
    }
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

GraphDrawerBuilder * GraphDrawerBuilder::AddXMin(float xMin) {
    this->xMin = xMin;
    xMinInitialized = true;
    return this;
}

GraphDrawerBuilder * GraphDrawerBuilder::AddYMin(float yMin) {
    this->yMin = yMin;
    yMinInitialized = true;
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

    return {width, height, xPartition, yPartition, xUnit, yUnit, graphFunction, color, xMax, yMax, xMin, yMin};
}

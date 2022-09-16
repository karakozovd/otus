#pragma once

#include "shapes.h"

#include <memory>
#include <algorithm>

using namespace Geometry;

class Model
{
public:
    Model() = delete;
    Model(const Rectangle &bound);
    Model(const Rectangle &bound, const std::vector<std::shared_ptr<Shape>> &shapes);

    virtual ~Model() = default;

    void setBounds(Rectangle &bounds);
    Rectangle bounds() { return m_bounds; }

    void addShape(const std::shared_ptr<Shape> &shape);
    void removeShape(const Shape &shape);
    void removeShape(int index);

    std::shared_ptr<Shape> at(int index);

    void clear() { m_shapes.clear(); }
    size_t size() { return m_shapes.size(); }

private:
    bool inBounds(const std::shared_ptr<Shape> &shape);
    void calculateBoundsPoints();

private:
    std::vector<std::shared_ptr<Shape>> m_shapes;
    Rectangle m_bounds;

    RawPoint m_maxPoint;
    RawPoint m_minPoint;
};

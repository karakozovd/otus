#pragma once

#include <memory>

namespace Geometry {
class Rectangle;
class Shape;
}

class Model;

class DrawerBackend
{
public:
    explicit DrawerBackend() = default;
    virtual ~DrawerBackend() = default;

    virtual void drawScene(const std::shared_ptr<Model> &model) = 0;
    virtual void drawShape(const std::shared_ptr<Geometry::Shape> &shape) = 0;
    virtual void drawBounds(const std::shared_ptr<Geometry::Rectangle> &bounds) = 0;
};

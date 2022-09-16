#pragma once

#include "drawerbackend.h"
#include "shapes.h"

class ConsoleDrawerBackend : public DrawerBackend
{
public:
    explicit ConsoleDrawerBackend();
    virtual ~ConsoleDrawerBackend() = default;

    virtual void drawScene(const std::shared_ptr<Model> &model) override;
    virtual void drawShape(const std::shared_ptr<Geometry::Shape> &shape) override;
    virtual void drawBounds(const std::shared_ptr<Geometry::Rectangle> &bounds) override;

private:
    std::string shapeType(ShapeTypes type);

private:
    std::map<ShapeTypes, std::string> m_typesMap;
};

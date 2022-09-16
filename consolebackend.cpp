#include "consolebackend.h"

#include "model.h"
#include "shapes.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>

ConsoleDrawerBackend::ConsoleDrawerBackend() : DrawerBackend()
{
    m_typesMap.insert(std::pair<ShapeTypes, std::string>(ShapeTypes::Point, {"Point"}));
    m_typesMap.insert(std::pair<ShapeTypes, std::string>(ShapeTypes::Line, {"Line"}));
    m_typesMap.insert(std::pair<ShapeTypes, std::string>(ShapeTypes::Rect, {"Rect"}));
}

void ConsoleDrawerBackend::drawScene(const std::shared_ptr<Model> &model)
{
    for (size_t i = 0; i < model->size(); ++i) {
        drawShape(model->at(i));
    }
}

void ConsoleDrawerBackend::drawBounds(const std::shared_ptr<Geometry::Rectangle> &bounds)
{
    std::cout << "[Bounds]\n";
    drawShape(bounds);
    std::cout << "\n[/Bounds]\n";
}

std::string ConsoleDrawerBackend::shapeType(ShapeTypes type)
{
    auto found = m_typesMap.find(type);
    return (found != m_typesMap.end()) ? found->second : std::string{"Unknown"};
}

void ConsoleDrawerBackend::drawShape(const std::shared_ptr<Geometry::Shape> &shape)
{
    if (!shape)
        return;

    std::cout << shapeType(shape->type());
    std::cout << "\tZ: " << shape->z() << " ";

    const size_t delimeterRange = shape->coordinates().size() - 1;
    std::stringstream tmp;
    tmp << "\n\t";

    for (size_t i = 0; i < shape->coordinates().size(); ++i) {
        tmp << "X" << i << ":" << shape->coordinates().at(i).x << " ";
        tmp << "Y" << i << ":" << shape->coordinates().at(i).y << " ";

        if (i != 0 && i != delimeterRange)
            tmp << "\n\t";
    }

    std::cout << tmp.str() << std::endl;
}

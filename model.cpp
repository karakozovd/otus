#include "model.h"

using namespace Geometry;

Model::Model(const Rectangle &bound) :
    m_bounds{bound}
{
    calculateBoundsPoints();
}

Model::Model(const Rectangle &bound, const std::vector<std::shared_ptr<Shape>> &shapes)
    : m_shapes{shapes},
      m_bounds{bound}
{
    calculateBoundsPoints();
}

void Model::setBounds(Rectangle &bounds)
{
    if (bounds.isValid())
        m_bounds = bounds;
}

void Model::addShape(const std::shared_ptr<Shape> &shape)
{
    int id = m_shapes.empty() ? 1 : m_shapes.back()->id() + 1;
    shape->setId(id);

    if (shape->isValid() && inBounds(shape))
        m_shapes.push_back(shape);
}

void Model::removeShape(const Shape &shape)
{
    (void) shape;

    /*
     * Removing shape by unique shape id
     */

    /*
    auto found = std::find_if(m_shapes.begin(), m_shapes.end(), [&shape](const std::shared_ptr<Shape> &tmp) {
        return tmp->id() == shape.id();
    });

    if (found != m_shapes.end())
        m_shapes.erase(found);
    */
}

void Model::removeShape(int index)
{
    m_shapes.erase(m_shapes.begin() + index);
}

std::shared_ptr<Shape> Model::at(int index)
{   
    return m_shapes.at(index);
}

bool Model::inBounds(const std::shared_ptr<Shape> &shape)
{
    (void) shape;
    /*for (const auto &point : shape->coordinates()) {
        if (point.x > m_maxPoint.x || point.y > m_maxPoint.y
                || point.x < m_minPoint.x || point.y < m_minPoint.y)
            return false;
    }*/

    return true;
}

void Model::calculateBoundsPoints()
{
    // calculate max and min points from bounds rect
}

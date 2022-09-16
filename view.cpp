#include "model.h"
#include "view.h"
#include "shapes.h"

#include "drawerbackend.h"

View::View(const std::shared_ptr<Model> &model)
    : m_model{model}
{

}

void View::drawScene()
{
    if (!m_drawerBackend)
        return;

    m_drawerBackend->drawBounds(std::make_shared<Rectangle>(m_model->bounds()));
    m_drawerBackend->drawScene(m_model);
}

void View::addShape(const std::shared_ptr<Shape> &shape)
{
    m_model->addShape(shape);
}

void View::removeShape(int index)
{
    m_model->removeShape(index);
}

void View::setShapeLayer(int index, int z)
{
    if (m_model->at(index))
        m_model->at(index)->setZ(z);
}

#pragma once

#include <memory>

class DrawerBackend;
class Model;

namespace Geometry {
    class Shape;
}

class View
{
public:
    explicit View(const std::shared_ptr<Model> &model);
    virtual ~View() = default;

    void setBackend(std::shared_ptr<DrawerBackend> backend) { m_drawerBackend = backend; }

    void drawScene();
    void refresh();

    void addShape(const std::shared_ptr<Geometry::Shape> &shape);
    void removeShape(int index);

    void setShapeLayer(int index, int z);

    std::shared_ptr<Model> model() { return m_model; }
    void setModel(const std::shared_ptr<Model> &model) { m_model = model; }

private:
    std::shared_ptr<Model> m_model;
    std::shared_ptr<DrawerBackend> m_drawerBackend;
};

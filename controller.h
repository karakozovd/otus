#pragma once
#include <memory>

#include "view.h"

namespace Project {
bool dump(const std::shared_ptr<Model> &model, const std::string &file)
{
    (void) model;
    (void) file;

    /*
     * 1) iterate every shape in model
     * 2) check shape type (Shape->type()) and convert to string
     * 3) convert shape coords to string (Shape->coordinates())
     * 4) convert shape z (position on view/scene) to string
     * 5) convert shape id to string
     * 6) write string to file
     *
     * dump model to file; format:
     * [0-n] - geometry type; [1,2] - delimeter (: ); first line always rectangle (bounds);
     * B: X1;Y1;X2;Y2;X3;Y3;X4;Y4|ID|Z\n
     * P: X1;Y1|ID|Z\n
     * L: X1;Y1;X2;Y2|ID|Z
     */

    return true;
}
std::shared_ptr<Model> fromFile(const std::string &path)
{
    (void) path;

    /*
     * 1) parse file
     * 2) create bounds
     * 3) create other shapes with validation check
     * 4) add shapes to vector
     * 5) create model
     */

    return nullptr;
}
}

class MainWindow
{
public:
    void setView(const std::shared_ptr<View> &view) { m_view = view; }

    void createProject() { /* Create new model and view */ }
    void createProject(const std::string &path) { (void) path;/*m_model = Project::fromFile(path);*/ }

    bool saveProject(const std::string &path) { return Project::dump(m_view->model(), path); }

    void selectShapeButton();

    void draw() { m_view->drawScene(); }

    void removeShapeAction(int index) { return m_view->removeShape(index); }
    void addShapeAction(const std::shared_ptr<Geometry::Shape> &shape) { return m_view->addShape(shape); }

private:
    std::shared_ptr<View> m_view;
};

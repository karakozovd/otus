#include "model.h"
#include "view.h"
#include "consolebackend.h"
#include "controller.h"

int main()
{
    Geometry::Line l0(Point(0, 0, 0), Point(1920, 0, 0), 0);
    Geometry::Line l1(Point(0, 0, 0), Point(0, 1080, 0), 0);
    Geometry::Line l2(Point(0, 1080, 0), Point(1920, 1080, 0), 0);
    Geometry::Line l3(Point(1920, 1080, 0), Point(1920, 0, 0), 0);

    std::array<Geometry::Line, 4> boundsRect{l0, l1, l2, l3};

    // create model
    std::shared_ptr<Model> model = std::make_shared<Model>(Geometry::Rectangle(boundsRect));
    // create view with model
    std::shared_ptr<View> view = std::make_shared<View>(model);
    // create drawing backend for view
    std::shared_ptr<DrawerBackend> backend = std::make_shared<ConsoleDrawerBackend>();
    view->setBackend(backend);

    // creating controller window
    MainWindow window;
    // setup with existing view
    window.setView(view);

    // for generate new view
    // window.createProject();
    // for import from file
    // window.createProject("project.txt");

    // addShapeAction - handler for gui button / etc.
    window.addShapeAction(std::make_shared<Geometry::Line>(l0));
    window.addShapeAction(std::make_shared<Geometry::Line>(l1));
    window.addShapeAction(std::make_shared<Geometry::Line>(l2));
    window.addShapeAction(std::make_shared<Geometry::Line>(l3));
    window.addShapeAction(std::make_shared<Geometry::Rectangle>(Geometry::Rectangle(boundsRect)));
    window.addShapeAction(std::make_shared<Geometry::Point>(Geometry::Point(5, 10)));

    // removeShapeAction - handler for gui button / etc.
    window.removeShapeAction(5);
    window.draw();

    // export current project to file
    window.saveProject("project.txt");

    return 0;
}

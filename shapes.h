#pragma once

#include <vector>
#include <array>
#include <map>

enum class ShapeTypes {
    Point,
    Line,
    Rect
};

namespace Geometry {
struct RawPoint
{
    int x;
    int y;
};

class Shape
{
public:
    explicit Shape(int z = 0, int id = 0) : m_z{z}, m_id{id} { }
    virtual ~Shape() = default;

    // return coord's vector
    virtual std::vector<RawPoint> coordinates() = 0;
    // validate shape geometry
    virtual bool isValid() = 0;
    // shape type
    virtual ShapeTypes type() = 0;

    // TODO: resolve the main problem of this approach:
    // howto determine that a shape is circle?
    // bool isCircle() { }

    int z() const { return m_z; }
    void setZ(int z) { m_z = z; }

    int id() const { return m_id; }
    void setId(int id) { m_id = id; }

private:
    int m_z;
    int m_id;
};

class Point : public Shape
{
public:
    explicit Point(int px, int py, int z = 0, int id = 0) : Shape(z, id), m_point{px, py} { }
    virtual ~Point() = default;

    virtual std::vector<RawPoint> coordinates() override { return std::vector<RawPoint>{m_point}; }
    virtual bool isValid() override { return true; }
    virtual ShapeTypes type() override { return ShapeTypes::Point; }

    RawPoint toRaw() { return m_point; }

private:
    RawPoint m_point;
};

class Line : public Shape
{
public:
    explicit Line(const Point &pstart, const Point &pfinish, int z = 0, int id = 0) : Shape(z, id), m_begin{pstart}, m_end{pfinish} { }
    virtual ~Line() = default;

    virtual std::vector<RawPoint> coordinates() override { return std::vector<RawPoint>{m_begin.toRaw(), m_end.toRaw()}; }
    virtual bool isValid() override { return true; }
    virtual ShapeTypes type() override { return ShapeTypes::Line; }

    Point begin() const { return m_begin; }
    Point end() const { return m_end; }

private:
    Point m_begin;
    Point m_end;
};

class Rectangle : public Shape
{
public:
    explicit Rectangle(std::array<Line, 4> lines, int z = 0, int id = 0) : Shape(z, id), m_lines{lines} { }
    virtual ~Rectangle() = default;

    virtual std::vector<RawPoint> coordinates() override
    {
        std::vector<RawPoint> points;
        points.reserve(8);

        for (const auto &line : m_lines) {
            points.push_back(line.begin().toRaw());
            points.push_back(line.end().toRaw());
        }

        return points;
    }
    virtual bool isValid() override{ return true; }
    virtual ShapeTypes type() override { return ShapeTypes::Rect; }

private:
    std::array<Line, 4> m_lines;
};
}

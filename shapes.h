#pragma once

constexpr double pi=geometry::pi<double>;

using Angle=geometry::Angle<double>;
using Point=geometry::coordinates::Cartesian<int>;
using Line=geometry::Line<Point, double>;
using Vector=geometry::Vector<Point, double, double>;
using Circle=geometry::Circle<Point, double, double>;
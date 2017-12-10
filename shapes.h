#pragma once

constexpr double pi=geometry::pi<double>;

using Angle=geometry::Angle<double>;
using Point=geometry::coordinates::Cartesian<int32>;
using Line=geometry::Line<Point, double>;
using Vector=geometry::Vector<Point, double, double>;
using Circle=geometry::Circle<Point, double, double>;

using Rect=geometry::Rect<int32, uint32>;
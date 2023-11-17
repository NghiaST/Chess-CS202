#include "RenderPS.hpp"
#include "Point.hpp"

RenderPS::RenderPS() : rPosition(Point()), rSize(Point()) {}

RenderPS::RenderPS(Point rPosition, Point rSize) : rPosition(rPosition), rSize(rSize) {}
#include <DataControl/RenderPS.hpp>
#include <DataControl/Point.hpp>

RenderPS::RenderPS() : rPosition(Point()), rSize(Point()) {}

RenderPS::RenderPS(Point rPosition, Point rSize) : rPosition(rPosition), rSize(rSize) {}
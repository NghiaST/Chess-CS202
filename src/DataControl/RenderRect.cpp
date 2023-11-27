#include <DataControl/RenderRect.hpp>
#include <DataControl/Point.hpp>

RenderRect::RenderRect() 
  : rPosition(Point()), rSize(Point()) {}
RenderRect::RenderRect(Point rPosition, Point rSize)
  : rPosition(rPosition), rSize(rSize) {}
RenderRect::RenderRect(int left, int top, int width, int height)
  : rPosition(left, top), rSize(width, height) {}
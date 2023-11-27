#ifndef __RenderPS_hpp__
#define __RenderPS_hpp__

#include <DataControl/Point.hpp>

struct RenderRect {
    RenderRect();
    RenderRect(Point rPosition, Point rSize);
    RenderRect(int left, int top, int width, int height);

    Point rPosition;
    Point rSize;
};

#endif
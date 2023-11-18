#ifndef __RenderPS_hpp__
#define __RenderPS_hpp__

#include <DataControl/Point.hpp>

struct RenderPS {
    RenderPS();
    RenderPS(Point rPosition, Point rSize);

    Point rPosition;
    Point rSize;
};

#endif
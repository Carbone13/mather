#include "drawers.hpp"

SolidDrawer::SolidDrawer(BaseRenderer &baseRenderer) : renderer(baseRenderer)
{
}

OutlineDrawer::OutlineDrawer(BaseRenderer &baseRenderer) : renderer(baseRenderer, profile), rasterizer(renderer)
{
    profile.width(1.0f);
    renderer.attach(baseRenderer);
}

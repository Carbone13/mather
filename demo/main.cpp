#include "mather.hpp"

using namespace mather;

int main()
{
    Context ctx = Context();
    ctx.backgroundColor = Color(0xc74a4a);

    float zigzag[] = {-200, -200, -150, -100, -75, 100, 0, 200};
    float star[] = {50, 3, 20, 97, 95, 37, 5, 37, 80, 97};

    while (!ctx.closeRequested())
    {
        ctx.beginFrame();
        {
            ctx.line(-620, -350, 620, 350, 3.0f, LineCap::Round, colors::white);
            ctx.polyline(zigzag, 8, 1.0f, LineCap::Square, LineJoin::Mitter, colors::green);
            ctx.circle(550, -200, 100, colors::cyan);
            ctx.rect(350, 350, 150, 200, colors::blue);
            ctx.roundedRect(700, 500, 80, 50, 10, colors::olive);
            ctx.polygon(star, sizeof(star) / sizeof(float), colors::teal);

            ctx.circleOutline(100, 100, 50, 1.f, colors::green);
        }
        ctx.endFrame();
    }

    return 0;
}

#include "mather.hpp"

using namespace mather;

int main()
{
    Context ctx = Context();
    ctx.backgroundColor = Color(0xc74a4a);

    float zigzag[] = {20, 50, 60, 500, 350, 100};
    float star[] = {50, 3, 20, 97, 95, 37, 5, 37, 80, 97};

    while (!ctx.closeRequested())
    {
        ctx.beginFrame();
        {
            ctx.line(20, 20, 1260, 700, 2.0f, LineCap::Round, colors::white);
            ctx.rect(350, 350, 150, 200, colors::blue);
            ctx.roundedRect(700, 500, 80, 50, 10, Color(0xfca103));

            ctx.polyline(zigzag, sizeof(zigzag) / sizeof(float), 5.0f, LineCap::Square, LineJoin::Mitter,
                         colors::green);

            ctx.polygon(star, sizeof(star) / sizeof(float), colors::blue);

            ctx.circleOutline(100, 100, 50, 1.f, colors::green);
        }
        ctx.endFrame();
    }

    return 0;
}

#include "mather.hpp"

using namespace mather;

int main()
{
    Context ctx = Context();

    while (!ctx.closeRequested())
    {
        ctx.beginFrame();
        ctx.endFrame();
    }

    return 0;
}

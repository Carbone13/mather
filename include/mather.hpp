#ifndef MATHER_MATHER_HPP
#define MATHER_MATHER_HPP

#include "drawers.hpp"

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <vector>

#include <agg_math_stroke.h>
#include <agg_trans_affine.h>
typedef agg::rendering_buffer Buffer;
typedef agg::trans_affine TransformMatrix;

namespace mather
{
    enum LineCap
    {
        Square,
        Round,
        Butt
    };

    enum LineJoin
    {
        Mitter,
        Bevel,
        Rounded,
    };

    class Context
    {
      private:
        int width;
        int height;

        GLFWwindow *window{nullptr};

        Buffer renderBuffer;
        PixelFormat pixelFormat;
        BaseRenderer baseRenderer;

        SolidDrawer solidDrawer;
        OutlineDrawer outlineDrawer;

        TransformMatrix matrix;

        unsigned char *internalBuffer{nullptr};

        static agg::line_cap_e matherCapToAggCap(LineCap cap);
        static agg::line_join_e matherJoinToAggJoin(LineJoin join);

      public:
        explicit Context(int width = 1280, int height = 720, const char *name = "Mather Application");
        ~Context();

        Color backgroundColor;

        void setTransform(float xOffset, float yOffset, float rotation);
        void resetTransform();

        void beginFrame();
        void endFrame();

        bool closeRequested();

        void line(float x0, float y0, float x1, float y1, float t, LineCap cap, Color color);
        void polyline(float pos[], int pointCount, float t, LineCap cap, LineJoin join, Color color);
        void circle(float x, float y, float r, Color color);
        void rect(float x, float y, float w, float h, Color color);
        void roundedRect(float x, float y, float w, float h, float r, Color color);
        void polygon(float pos[], int pointCount, Color color);

        void circleOutline(float x, float y, float r, float t, Color color);
        void rectOutline(float x, float y, float w, float h, float t, Color color);
        void roundedRectOutline(float x, float y, float w, float h, float r, float t, Color color);
        void polygonOutline(float pos[], int pointCount, float t, Color color);
    };

    namespace colors
    {
        static const Color transparent(0xff, 0xff, 0xff, 0x00);
        static const Color white(0xffffff);
        static const Color red(0xff0000);
        static const Color green(0x00ff00);
        static const Color blue(0x0000ff);

        static const Color yellow(0xffff00);
        static const Color cyan(0x00ffff);
        static const Color magenta(0xff00ff);

        static const Color silver(0xc0c0c0);
        static const Color gray(0x808080);
        static const Color maroon(0x800000);
        static const Color olive(0x808000);
        static const Color purple(0x800080);
        static const Color teal(0x008080);
        static const Color navy(0x000080);
    } // namespace colors
} // namespace mather

#endif // MATHER_MATHER_HPP

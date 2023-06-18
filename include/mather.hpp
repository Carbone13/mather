#ifndef MATHER_MATHER_HPP
#define MATHER_MATHER_HPP

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <vector>

#include "agg_math_stroke.h"
#include "agg_trans_affine.h"
#include <agg_pixfmt_rgb.h>
#include <agg_pixfmt_rgba.h>
#include <agg_rasterizer_scanline_aa.h>
#include <agg_renderer_base.h>
#include <agg_renderer_scanline.h>
#include <agg_scanline_p.h>

typedef agg::pixfmt_rgba32 PixelFormat;
typedef agg::renderer_base<PixelFormat> RendererBaseType;
typedef agg::rgba8 Color;

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

        agg::rendering_buffer renderBuffer;
        PixelFormat pixelFormat;
        RendererBaseType renderer;
        agg::scanline_p8 scanline;
        agg::rasterizer_scanline_aa<> ras;

        agg::trans_affine matrix;

        unsigned char *buffer{nullptr};

        void createWindow(const char *name);
        template <class VertexSource> void renderFilled(VertexSource &vs, Color color);

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

        void drawLine(float x0, float y0, float x1, float y1, float t, LineCap cap, Color color);
        void drawPolyline(float pos[], int pointCount, float t, LineCap cap, LineJoin join, Color color);

        void drawCircle(float x, float y, float r, Color color);
        void drawCircleOutline(float x, float y, float r, float t, Color color);

        void drawRect(float x, float y, float w, float h, Color color);

        void drawRoundedRect(float x, float y, float w, float h, float r, Color color);

        void drawPolygon(float pos[], int pointCount, Color color);
        void drawPolygonOutline(float pos[], int pointCount, float t, LineJoin join, Color color);
    };

    namespace colors
    {
        static const Color transparent(0xff, 0xff, 0xff, 0x00);
        static const Color white(0xff, 0xff, 0xff, 0xff);
        static const Color red(0xff, 0x00, 0x00, 0xff);
        static const Color green(0x00, 0xff, 0x00, 0xff);
        static const Color blue(0x00, 0x00, 0xff, 0xff);
    } // namespace colors
} // namespace mather

#endif // MATHER_MATHER_HPP

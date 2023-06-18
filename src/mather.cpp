#include "mather.hpp"
#include "agg_rounded_rect.h"
#include <agg_ellipse.h>
#include <agg_pixfmt_rgba.h>
#include <agg_rasterizer_scanline_aa.h>
#include <agg_renderer_base.h>
#include <agg_renderer_scanline.h>
#include <agg_scanline_p.h>

typedef agg::pixfmt_rgba32 PixelFormat;
typedef agg::renderer_base<PixelFormat> RendererBaseType;

namespace mather
{
    Context::Context(int width, int height, const char *name)
    {
        this->width = width;
        this->height = height;
        createWindow(name);
    }

    void Context::createWindow(const char *name)
    {
        glfwInit();
        window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        glfwMakeContextCurrent(window);
    }

    void Context::beginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Context::endFrame()
    {
        const int pixelSize = PixelFormat::pix_width;

        agg::rendering_buffer renderBuffer;
        PixelFormat pixFmt;
        RendererBaseType rBase;

        unsigned char *imageBuffer = new unsigned char[width * height * pixelSize];

        // Hook everything up
        renderBuffer.attach(imageBuffer, width, height, width * pixelSize);
        pixFmt.attach(renderBuffer);
        rBase.attach(pixFmt);

        const agg::rgba8 transparentWhiteColor(0xff, 0xff, 0xff, 0);
        const agg::rgba8 greenColor(0, 0xff, 0, 0xff);

        // clear the buffer with transparent white color
        rBase.clear(transparentWhiteColor);

        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_p8 scanline;
        {
            agg::ellipse eliipse(100, 100, 50, 80);

            ras.reset();
            ras.add_path(eliipse);

            agg::render_scanlines_aa_solid(ras, scanline, rBase, greenColor);
        }

        agg::rounded_rect rect2(20, 60, 170, 110, 10);

        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
        glfwSwapBuffers(window);
        glfwPollEvents();

        // delete[] imageBuffer;
    }

    bool Context::closeRequested()
    {
        return glfwWindowShouldClose(window);
    }

    Context::~Context()
    {
        glfwTerminate();
    }

} // namespace mather
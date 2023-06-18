#include "mather.hpp"
#include "config.hpp"

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

        auto pixelSize = PixelFormat::pix_width;
        buffer = new unsigned char[width * height * pixelSize];

        renderBuffer.attach(buffer, width, height, width * pixelSize);
        pixelFormat.attach(renderBuffer);
        renderer.attach(pixelFormat);
    }

    void Context::beginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Context::endFrame()
    {
        const agg::rgba8 transparentWhiteColor(0xff, 0xff, 0xff, 0);
        const agg::rgba8 greenColor(0, 0xff, 0, 0xff);

        // clear the buffer with transparent white color
        renderer.clear(transparentWhiteColor);

        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_p8 scanline;
        {
            agg::ellipse eliipse(100, 100, 50, 80);
            agg::rounded_rect rect2(20, 60, 170, 110, 10);

            ras.reset();
            ras.add_path(eliipse);
            ras.add_path(rect2);

            agg::render_scanlines_aa_solid(ras, scanline, renderer, greenColor);
        }

        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
        glfwSwapBuffers(window);
        glfwPollEvents();
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
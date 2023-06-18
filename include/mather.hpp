#ifndef MATHER_MATHER_HPP
#define MATHER_MATHER_HPP

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include <agg_pixfmt_rgb.h>
#include <agg_pixfmt_rgba.h>
#include <agg_renderer_base.h>

typedef agg::pixfmt_rgb24 PixelFormat;
typedef agg::renderer_base<PixelFormat> RendererBaseType;

namespace mather
{
    class Context
    {
      private:
        int width;
        int height;

        GLFWwindow *window{nullptr};

        agg::rendering_buffer renderBuffer;
        PixelFormat pixelFormat;
        RendererBaseType renderer;
        unsigned char *buffer;

        void createWindow(const char *name);

      public:
        void beginFrame();
        void endFrame();

        bool closeRequested();

        explicit Context(int width = 1280, int height = 720, const char *name = "Mather Application");
        ~Context();
    };
} // namespace mather

#endif // MATHER_MATHER_HPP

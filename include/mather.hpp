#ifndef MATHER_MATHER_HPP
#define MATHER_MATHER_HPP

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

namespace mather
{
    class Context
    {
      private:
        int width;
        int height;

        GLFWwindow *window{nullptr};

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

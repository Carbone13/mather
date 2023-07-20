#define WIDTH 1280
#define HEIGHT 720

#include "main.hpp"

GLFWwindow *window{nullptr};

float zigzag[] = {-200, -200, -150, -100, -75, 100, 0, 200};
float star[] = {50, 3, 20, 97, 95, 37, 5, 37, 80, 97};

int main()
{
    initGlfw();

    Context ctx = Context(WIDTH, HEIGHT);
    ctx.backgroundColor = Color(0xc74a4a);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw(ctx);

        glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, ctx.getBuffer());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void initGlfw () {
    glfwInit();
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW Demo", nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

void draw (Context &ctx) {
    ctx.clear();

    ctx.line(-620, -350, 620, 350, 3.0f, LineCap::Round, colors::white);
    ctx.polyline(zigzag, 8, 1.0f, LineCap::Square, LineJoin::Mitter, colors::green);
    ctx.circle(550, -200, 100, colors::cyan);
    ctx.rect(350, 350, 150, 200, colors::blue);
    ctx.roundedRect(700, 500, 80, 50, 10, colors::olive);
    ctx.polygon(star, sizeof(star) / sizeof(float), colors::teal);
    ctx.circleOutline(100, 100, 50, 1.f, colors::green);
}
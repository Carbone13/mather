#include "mather.hpp"
#include "path.hpp"

#include <agg_conv_stroke.h>
#include <agg_ellipse.h>
#include <agg_rounded_rect.h>
#include <iostream>

namespace mather
{
    Context::Context(int width, int height, const char *name) : outlineDrawer(baseRenderer), solidDrawer(baseRenderer)
    {
        this->width = width;
        this->height = height;

        glfwInit();
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
        window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        glfwMakeContextCurrent(window);

        internalBuffer = new unsigned char[width * height * PixelFormat::pix_width];
        renderBuffer.attach(internalBuffer, width, height, width * PixelFormat::pix_width);
        pixelFormat.attach(renderBuffer);
        baseRenderer.attach(pixelFormat);

        TransformMatrix centeringMatrix = agg::trans_affine_translation(width / 2.0f, height / 2.0f);

        solidDrawer.centeringMatrix = centeringMatrix;
        outlineDrawer.centeringMatrix = centeringMatrix;
    }

    void Context::setTransform(float xOffset, float yOffset, float rotation)
    {
        matrix.reset();
        matrix.rotate(rotation);
        matrix.translate(xOffset, yOffset);
    }

    void Context::resetTransform()
    {
        matrix.reset();
    }

    void Context::beginFrame()
    {
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);
        baseRenderer.clear(backgroundColor);
        matrix.reset();
    }

    void Context::endFrame()
    {
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, internalBuffer);
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

    /// ****
    /// SOLID PRIMITIVES
    /// ****

    void Context::line(float x0, float y0, float x1, float y1, float t, LineCap cap, Color color)
    {
        float p[] = {x0, y0, x1, y1};
        polyline(p, 4, t, cap, LineJoin::Mitter, color);
    }

    void Context::polyline(float *pos, int pointCount, float t, LineCap cap, LineJoin join, Color color)
    {
        SimplePath path(pos, pointCount, false);
        agg::conv_stroke<SimplePath> strokePath(path);

        strokePath.width(t);
        strokePath.line_cap(matherCapToAggCap(cap));
        strokePath.line_join(matherJoinToAggJoin(join));
        strokePath.miter_limit(t);

        solidDrawer.draw(strokePath, color);
    }

    void Context::circle(float x, float y, float r, Color color)
    {
        agg::ellipse circle(x, y, r, r);
        solidDrawer.draw(circle, color);
    }

    void Context::rect(float x, float y, float w, float h, Color color)
    {
        agg::rounded_rect rect(x, y, x + w, y - h, 0);
        solidDrawer.draw(rect, color);
    }

    void Context::roundedRect(float x, float y, float w, float h, float r, Color color)
    {
        agg::rounded_rect rect(x, y, x + w, y - h, r);
        solidDrawer.draw(rect, color);
    }

    void Context::polygon(float pos[], int pointCount, Color color)
    {
        SimplePath path(pos, pointCount, false);
        solidDrawer.draw(path, color, true);
    }

    /// ****
    /// Outlined Primitives
    /// ****
    void Context::circleOutline(float x, float y, float r, float t, Color color)
    {
        agg::ellipse circle(x, y, r, r);
        outlineDrawer.draw(circle, color, t);
    }

    void Context::rectOutline(float x, float y, float w, float h, float t, Color color)
    {
        agg::rounded_rect rect(x, y, x + w, y - h, 0);
        outlineDrawer.draw(rect, color, t);
    }

    void Context::roundedRectOutline(float x, float y, float w, float h, float r, float t, Color color)
    {
        agg::rounded_rect rect(x, y, x + w, y - h, r);
        outlineDrawer.draw(rect, color, t);
    }
    void Context::polygonOutline(float *pos, int pointCount, float t, Color color)
    {
        SimplePath path(pos, pointCount, false);
        outlineDrawer.draw(path, color, t, true);
    }

    /// ****
    /// UTILS
    /// ****
    agg::line_cap_e Context::matherCapToAggCap(LineCap cap)
    {
        switch (cap)
        {
        case Square:
            return agg::square_cap;
        case Round:
            return agg::round_cap;
        case Butt:
            return agg::butt_cap;
        }

        return agg::square_cap;
    }

    agg::line_join_e Context::matherJoinToAggJoin(LineJoin join)
    {
        switch (join)
        {
        case Mitter:
            return agg::miter_join;
        case Bevel:
            return agg::bevel_join;
        case Rounded:
            return agg::round_join;
        }

        return agg::miter_join;
    }
} // namespace mather
#include "mather.hpp"
#include "agg_conv_transform.h"
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
        ras.auto_close(false);
    }

    void Context::beginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.clear(backgroundColor);
        matrix.reset();
    }

    void Context::endFrame()
    {
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
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

    template <class VertexSource> void Context::renderFilled(VertexSource &vs, Color color)
    {
        agg::conv_transform<VertexSource> transformedVs(vs, matrix);

        ras.reset();
        ras.add_path(transformedVs);
        agg::render_scanlines_aa_solid(ras, scanline, renderer, color);
    }

    void Context::drawLine(float x0, float y0, float x1, float y1, float t, LineCap cap, Color color)
    {
        float p[] = {x0, y0, x1, y1};
        SimplePath path(p, 4, false);
        agg::conv_stroke<SimplePath> strokePath(path);
        strokePath.width(t);
        strokePath.line_cap(matherCapToAggCap(cap));

        renderFilled(strokePath, color);
    }

    void Context::drawPolyline(float *pos, int pointCount, float t, LineCap cap, LineJoin join, Color color)
    {
        SimplePath path(pos, pointCount, false);
        agg::conv_stroke<SimplePath> strokePath(path);

        strokePath.width(t);
        strokePath.line_cap(matherCapToAggCap(cap));
        strokePath.line_join(matherJoinToAggJoin(join));
        strokePath.miter_limit(t);

        renderFilled(strokePath, color);
    }

    void Context::drawCircle(float x, float y, float r, Color color)
    {
        agg::ellipse circle(x, y, r, r);
    }

    void Context::drawCircleOutline(float x, float y, float r, float t, Color color)
    {
        agg::ellipse circle(x, y, r, r);

        ras.reset();
        ras.add_path(circle);
        agg::render_scanlines_aa_solid(ras, scanline, renderer, color);
    }

    void Context::drawRect(float x, float y, float w, float h, Color color)
    {
        agg::rounded_rect rect(x, y, x + w, y - h, 0);
        renderFilled(rect, color);
    }

    void Context::drawRoundedRect(float x, float y, float w, float h, float r, Color color)
    {
        agg::rounded_rect rect(x, y, x + w, y - h, r);
        renderFilled(rect, color);
    }

    void Context::drawPolygon(float pos[], int pointCount, Color color)
    {
        ras.auto_close(true);
        SimplePath path(pos, pointCount, false);
        renderFilled(path, color);
        ras.auto_close(false);
    }

    void Context::drawPolygonOutline(float *pos, int pointCount, float t, LineJoin join, Color color)
    {
        SimplePath path(pos, pointCount, true);
        agg::conv_stroke<SimplePath> strokePath(path);

        strokePath.width(t);
        strokePath.line_cap(agg::line_cap_e::butt_cap);
        strokePath.line_join(matherJoinToAggJoin(join));
        strokePath.miter_limit(t);

        renderFilled(strokePath, color);
    }

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

} // namespace mather
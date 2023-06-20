#ifndef DRAWERS_HPP_
#define DRAWERS_HPP_

#include <agg_color_rgba.h>
#include <agg_conv_transform.h>
#include <agg_pixfmt_rgba.h>
#include <agg_renderer_base.h>
#include <agg_trans_affine.h>

typedef agg::rgba8 Color;

typedef agg::pixfmt_rgba32 PixelFormat;
typedef agg::renderer_base<PixelFormat> BaseRenderer;
typedef agg::trans_affine TransformMatrix;

#include <agg_rasterizer_scanline_aa.h>
#include <agg_renderer_scanline.h>
#include <agg_scanline_p.h>
class SolidDrawer
{
    typedef agg::rasterizer_scanline_aa<> Rasterizer;
    typedef agg::scanline_p8 Scanline;

  private:
    BaseRenderer &renderer;
    Rasterizer rasterizer;
    Scanline scanline;

  public:
    TransformMatrix centeringMatrix;

    explicit SolidDrawer(BaseRenderer &baseRenderer);

    template <class VertexSource> void draw(VertexSource &vs, Color color, bool autoClose = false)
    {
        rasterizer.reset();
        agg::conv_transform<VertexSource> tVs{vs, centeringMatrix};
        rasterizer.add_path(tVs);
        agg::render_scanlines_aa_solid(rasterizer, scanline, renderer, color);
    }
};

#include <agg_rasterizer_outline_aa.h>
#include <agg_renderer_outline_aa.h>
class OutlineDrawer
{
    typedef agg::renderer_outline_aa<BaseRenderer> Renderer;
    typedef agg::rasterizer_outline_aa<Renderer> Rasterizer;
    typedef agg::line_profile_aa Profile;

  private:
    Renderer renderer;
    Rasterizer rasterizer;
    Profile profile;

  public:
    TransformMatrix centeringMatrix;

    explicit OutlineDrawer(BaseRenderer &baseRenderer);

    template <class VertexSource>
    void draw(VertexSource &vs, Color color, float thickness = 1.0f, bool autoClose = false)
    {
        profile.width(thickness);
        renderer.color(color);
        agg::conv_transform<VertexSource> tVs{vs, centeringMatrix};
        rasterizer.add_path(tVs);
        rasterizer.render(autoClose);
    }
};

#endif // DRAWERS_HPP_

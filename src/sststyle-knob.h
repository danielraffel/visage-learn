/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#ifndef BACONPAUL_VISAGE_LEARN_SSTSTYLE_KNOB_H
#define BACONPAUL_VISAGE_LEARN_SSTSTYLE_KNOB_H

#include <visage_ui/frame.h>
#include "config.h"
#include "fonts.h"

namespace baconpaul::visage_learn
{
struct SSTStyleKnob : visage::Frame, PixelMixin<SSTStyleKnob>
{
    visage::Font detailFont;
    SSTStyleKnob() { detailFont = visage::Font(20, Fonts::firaCode, Fonts::firaCodeSize); }
    static constexpr float gapAngle{60.0 / 360.0 * M_PI};
    float value{0.2};
    static constexpr int margin{2}, ringThick{8}, bodyStart{margin + ringThick + 4},
        innerBodyStart{bodyStart + 6};

    void draw(visage::Canvas &canvas) override
    {
        if (isHovered)
            canvas.setColor(0xffff9000);
        else
            canvas.setColor(0xffd07000);
        float distance = (M_PI - gapAngle) * value;
        canvas.roundedArc(l2d(margin), l2d(margin), width() - l2d(2 * margin), l2d(ringThick),
                          distance + gapAngle + M_PI / 2, distance);

        auto bs = 0xff555555;
        if (isHovered)
            bs = 0xff777777;
        auto be = 0xff444444;
        auto bbs = 0xff333333;
        auto bbe = 0xff666666;

        canvas.setColor(visage::VerticalGradient(bbs, bbe));
        canvas.circle(l2d(bodyStart), l2d(bodyStart), width() - l2d(2 * bodyStart));

        canvas.setColor(visage::VerticalGradient(bs, be));
        canvas.circle(l2d(innerBodyStart), l2d(innerBodyStart), width() - l2d(2 * innerBodyStart));
    }

    float lastMouseY{0};
    bool isHovered{false};
    void mouseEnter(const visage::MouseEvent &e) override
    {
        isHovered = true;
        redraw();
    }
    void mouseExit(const visage::MouseEvent &e) override
    {
        isHovered = false;
        redraw();
    }
    void mouseDown(const visage::MouseEvent &e) override { lastMouseY = e.position.y; }
    void mouseUp(const visage::MouseEvent &e) override {}
    void mouseDrag(const visage::MouseEvent &e) override
    {
        auto dy = lastMouseY - e.position.y;
        lastMouseY = e.position.y;
        value += 0.004 * dy / dpiScale();
        value = std::clamp(value, 0.0f, 1.0f);
        redraw();
    }
};

struct SSTNKnobs : visage::Frame, PixelMixin<SSTNKnobs>
{
    static constexpr int nKnobs{4};
    SSTStyleKnob knobs[nKnobs];
    int knobSize{100}, knobGap{100};
    float llos{0};
    SSTNKnobs()
    {
        for (int i = 0; i < nKnobs; ++i)
        {
            addChild(&knobs[i]);
        }
    }

    void resized() override
    {
        llos = dpiScale();
        VLLOG("Reizing parent at dpiscale " << dpiScale());
        for (int i = 0; i < nKnobs; ++i)
        {
            int px = 10 + (i / 2) * knobGap;
            int py = 10 + (i % 2) * knobGap;

            knobs[i].setBounds({l2d(px), l2d(py), l2d(knobGap), l2d(knobGap)});
        }
    }

    void draw(visage::Canvas &canvas) override
    {
        if (dpiScale() != llos)
            resized();

        canvas.setColor(0xff000000);
        canvas.fill(0, 0, width(), height());
    }
};
} // namespace baconpaul::visage_learn
#endif // SSTSTYLE_KNOB_H

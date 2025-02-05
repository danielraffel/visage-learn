//
// Created by Paul Walker on 2/5/25.
//

#ifndef SSTSTYLE_KNOB_H
#define SSTSTYLE_KNOB_H

#include <visage_ui/frame.h>
#include "config.h"
#include "fonts.h"

namespace baconpaul::visage_learn
{
struct SSTStyleKnob : visage::Frame
{
    visage::Font detailFont;
    SSTStyleKnob() { detailFont = visage::Font(20, Fonts::firaCode, Fonts::firaCodeSize); }
    static constexpr float gapAngle{60.0 / 360.0 * M_PI};
    float value{0.2};
    void draw(visage::Canvas &canvas) override
    {
        canvas.setColor(0xff000000);
        canvas.fill(0, 0, width(), height());
        canvas.setColor(0xff0000ff);
        float distance = (M_PI - gapAngle) * value;
        canvas.roundedArc(5, 5, width() - 10, 20, distance + gapAngle + M_PI / 2, distance);
        canvas.setColor(0xffcccccc);

        std::string txt = "val= " + std::to_string(value);
        canvas.text(txt, detailFont, visage::Font::Justification::kCenter, 2, 2, width(), height());
    }

    float lastMouseY{0};
    void mouseEnter(const visage::MouseEvent &e) override {}
    void mouseExit(const visage::MouseEvent &e) override {}
    void mouseDown(const visage::MouseEvent &e) override { lastMouseY = e.position.y; }
    void mouseUp(const visage::MouseEvent &e) override {}
    void mouseDrag(const visage::MouseEvent &e) override
    {
        auto dy = lastMouseY - e.position.y;
        lastMouseY = e.position.y;
        value += 0.001 * dy;
        value = std::clamp(value, 0.0f, 1.0f);
        redraw();
    }
};
} // namespace baconpaul::visage_learn
#endif // SSTSTYLE_KNOB_H

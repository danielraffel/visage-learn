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
        if (isHovered)
          canvas.setColor(0xffff9000);
        else
          canvas.setColor(0xffd07000);
        float distance = (M_PI - gapAngle) * value;
        canvas.roundedArc(5, 5, width() - 10, 15, distance + gapAngle + M_PI / 2, distance);

        auto bs = 0xff555555;
        if (isHovered)
          bs = 0xff777777;
        auto be = 0xff444444;
        auto bbs = 0xff333333;
        auto bbe = 0xff666666;

        canvas.setColor(visage::VerticalGradient(bbs, bbe));
        canvas.circle(30, 30, width()-60);

        canvas.setColor(visage::VerticalGradient(bs, be));
        canvas.circle(40, 40, width()-80);

        //canvas.setColor(0xffcccccc);
        //std::string txt = "val= " + std::to_string(value);
        //canvas.text(txt, detailFont, visage::Font::Justification::kCenter, 2, 2, width(), height());
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
        value += 0.001 * dy;
        value = std::clamp(value, 0.0f, 1.0f);
        redraw();
    }
};

struct SSTFourKnobs : visage::Frame
{
  SSTStyleKnob knobs[4];
  int knobSize{200}, knobGap{220};
  SSTFourKnobs()
  {
  }

  void setup()
  {
    for (int i=0; i<4; ++i)
    {
      addChild(&knobs[i]);
      knobs[i].setBounds({20 + (i / 2) * knobGap, 20 + (i % 2) * knobGap, knobSize, knobSize});
    }
  }

  void draw(visage::Canvas &canvas) override
  {
    canvas.setColor(0xff000000);
    canvas.fill(0, 0, width(), height());
  }
};
} // namespace baconpaul::visage_learn
#endif // SSTSTYLE_KNOB_H

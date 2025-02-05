//
// Created by Paul Walker on 2/5/25.
//

#ifndef DRAGGABLE_CIRCLE_H
#define DRAGGABLE_CIRCLE_H

#include <visage_ui/frame.h>
#include "config.h"
#include "fonts.h"

namespace baconpaul::visage_learn
{
struct DraggableCircle : visage::Frame
{
    float cx{0.5}, cy{0.5};
    visage::Font detailFont;
    visage::Font circleFont;
    DraggableCircle()
    {
        detailFont = visage::Font(40, Fonts::firaCode, Fonts::firaCodeSize);
        circleFont = visage::Font(30, Fonts::pacifico, Fonts::pacificoSize);
    }

    void draw(visage::Canvas &canvas) override
    {
        canvas.setColor(0xff000066);
        canvas.fill(0, 0, width(), height());

        canvas.setColor(0xffCCAACC);
        std::string txt = "cx/y= " + std::to_string(cx) + ", " + std::to_string(cy);
        canvas.text(txt, detailFont, visage::Font::Justification::kTopLeft, 2, 2, width(), 50);

        float circle_radius = height() * 0.1f;
        float x = width() * cx - circle_radius;
        float y = height() * cy - circle_radius;
        canvas.setColor(0xff00ffff);
        canvas.circle(x, y, 2.0f * circle_radius);
        canvas.setColor(0xff222200);
        canvas.text("Fun", circleFont, visage::Font::Justification::kCenter, x, y,
                    2 * circle_radius, 2 * circle_radius);
    }
    void mouseDrag(const visage::MouseEvent &event) override
    {
        cx = 1.0 * event.position.x / width();
        cy = 1.0 * event.position.y / height();
        redraw();
    }
};
} // namespace baconpaul::visage_learn
#endif // DRAGGABLE_CIRCLE_H

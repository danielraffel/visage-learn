//
// Created by Paul Walker on 2/5/25.
//

#ifndef DRAGGABLE_CIRCLE_H
#define DRAGGABLE_CIRCLE_H

#include <visage_ui/frame.h>
#include "config.h"

namespace baconpaul::visage_learn
{
struct DraggableCircle : visage::Frame
{
  float cx{0.5}, cy{0.5};
  DraggableCircle()
  {
  }

  void draw(visage::Canvas &canvas) override
  {
    canvas.setColor(0xff000066);
    canvas.fill(0, 0, width(), height());

    float circle_radius = height() * 0.1f;
    float x = width() * cx - circle_radius;
    float y = height() * cy - circle_radius;
    canvas.setColor(0xff00ffff);
    canvas.circle(x, y, 2.0f * circle_radius);
  }
  void mouseDrag(const visage::MouseEvent &event) override
  {
      cx = 1.0 * event.position.x / width();
      cy = 1.0 * event.position.y / height();
      redraw();
  }
};
}
#endif //DRAGGABLE_CIRCLE_H

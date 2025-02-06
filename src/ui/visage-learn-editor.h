/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#ifndef BACONPAUL_VISAGE_LEARN_UI_VISAGE_LEARN_EDITOR_H
#define BACONPAUL_VISAGE_LEARN_UI_VISAGE_LEARN_EDITOR_H

#include <visage_app/application_window.h>
#include <visage_utils/dimension.h>

#include "config.h"
#include "ui/sststyle-knob.h"
#include "ui/fonts.h"
#include "ui/accesskit_to_visage.h"

namespace baconpaul::visage_learn
{
struct VisageLearnEditor : visage::ApplicationWindow
{
    static constexpr uint16_t width{800}, height{600};
    VisageLearnEditor();

    bool doGuiSetParent(void *window);

    std::unique_ptr<SSTNKnobs> knob_;
    ak_window_state akws_;
};
} // namespace baconpaul::visage_learn

#endif // VISAGE_LEARN_EDITOR_H

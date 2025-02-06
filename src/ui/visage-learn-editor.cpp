/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#include "visage-learn-editor.h"

namespace baconpaul::visage_learn
{
VisageLearnEditor::VisageLearnEditor()
{
    Fonts::setup();

    knob_ = std::make_unique<SSTNKnobs>();

    knob_->setBounds({0, 0, 800, 600});
    addChild(knob_.get());
}

bool VisageLearnEditor::doGuiSetParent(void *window)
{
    akws_.setFrame(this);
    akws_.setup((void *)window);
    show(width, height, window);
    akws_.postShow();
    setWindowDimensions(width, height);
    knob_->setBounds({0, 0, (int)(knob_->dpiScale() * width), (int)(knob_->dpiScale()) * height});

    return true;
}

} // namespace baconpaul::visage_learn
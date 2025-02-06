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

    frame_ = std::make_unique<visage::Frame>();
    frame_->onDraw() = [this](visage::Canvas &canvas)
    {
        canvas.setColor(visage::VerticalGradient(0xFF222244, 0xff111115));
        canvas.fill(0, 0, frame_->width(), frame_->height());
    };
    frame_->setBounds({0, 0, edWidth, edHeight});
    knob_ = std::make_unique<SSTNKnobs>();
    textEd_ = std::make_unique<visage::TextEditor>();

    knob_->setBounds({0, 0, (int)(edWidth * 0.5), (int)(edHeight * 0.5)});
    textEd_->setBounds({0, (int)(edHeight * 0.55), (int)(edWidth * 0.5), (int)(edHeight * 0.1)});
    textEd_->setText("This is my text");
    frame_->addChild(knob_.get());
    frame_->addChild(textEd_.get());
    addChild(frame_.get());
}

bool VisageLearnEditor::doGuiSetParent(void *window)
{
    akws_.setFrame(this);
    akws_.setup((void *)window);
    show(edWidth, edHeight, window);
    akws_.postShow();
    setWindowDimensions(edWidth, edHeight);
    resized();
    return true;
}

void VisageLearnEditor::resized()
{
    ApplicationWindow::resized();
    frame_->setBounds({0, 0, (int)(edWidth * dpiScale()), (int)(edHeight * dpiScale())});
    knob_->setBounds({0, 0, (int)(knob_->dpiScale() * edWidth * 0.5),
                      (int)(knob_->dpiScale() * edHeight * 0.5)});
    textEd_->setBounds({0, (int)(edHeight * dpiScale() * 0.55), (int)(edWidth * dpiScale() * 0.5),
                        (int)(edHeight * dpiScale() * 0.1)});

    textEdFont_ = visage::Font(20 * dpiScale(), Fonts::pacifico, Fonts::pacificoSize);
    textEd_->setFont(textEdFont_);
}

} // namespace baconpaul::visage_learn
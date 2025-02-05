#include <visage/app.h>
#include <iostream>
#include "draggable-circle.h"
#include "sststyle-knob.h"
#include "fonts.h"
#include "config.h"

int realMain()
{
    VLLOG("Starting visage_learn");
    baconpaul::visage_learn::Fonts::setup();

    visage::ApplicationWindow app;
#define KNOB_CHILD
#ifdef CIRCLE_CHILD
    baconpaul::visage_learn::DraggableCircle child;
    app.addChild(&child);
    child.layout().setDimensions(800, 600);
#endif

#ifdef KNOB_CHILD
    baconpaul::visage_learn::SSTFourKnobs child;
    app.addChild(&child);
    child.setBounds({0, 0, 800, 600});
    child.setup();
#endif

    app.setTitle("BaconPaul learns Visage");
    app.show(800, 600);
    app.runEventLoop();

    return 0;
}

#if VISAGE_WINDOWS
#include <windows.h>
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line,
                   _In_ int show_cmd)
{
    return realMain();
}
#else
int main(int argc, char **argv) { return realMain(); }
#endif
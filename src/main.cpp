#include <visage/app.h>
#include <iostream>
#include "draggable-circle.h"

int realMain()
{
    std::cout << "Hello World" << std::endl;
    visage::ApplicationWindow app;
    baconpaul::visage_learn::DraggableCircle circle;
    app.addChild(&circle);
    circle.layout().setDimensions(800, 600);

    app.onDraw() = [&circle](visage::Canvas& canvas) {
        circle.draw(canvas);
    };


    app.setTitle("Visage Basic Example");
    app.show(800, 600);
    app.runEventLoop();

    return 0;
}

#if VISAGE_WINDOWS
#include <windows.h>
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line,
                   _In_ int show_cmd) {
    return realMain();
}
#else
int main(int argc, char** argv) {
    return realMain();
}
#endif
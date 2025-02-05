#include <visage/app.h>
#include <iostream>

int realMain()
{
    std::cout << "Hello World" << std::endl;
    visage::ApplicationWindow app;

    app.onDraw() = [&app](visage::Canvas& canvas) {
        canvas.setColor(0xff000066);
        canvas.fill(0, 0, app.width(), app.height());

        float circle_radius = app.height() * 0.1f;
        float x = app.width() * 0.5f - circle_radius;
        float y = app.height() * 0.5f - circle_radius;
        canvas.setColor(0xff00ffff);
        canvas.circle(x, y, 2.0f * circle_radius);
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
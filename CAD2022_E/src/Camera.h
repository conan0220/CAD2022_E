#pragma once

class Camera
{
public:
    // constructor
    Camera() {}
    ~Camera() {}

    // function
    static void Render();

    static void RenderAim(bool display);

    // data
    static float scaling;
    static float x;     // position of aim
    static float y;     // position of aim
    static float velocity;

private:

};


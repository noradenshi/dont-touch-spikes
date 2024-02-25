#include "bird.h"
#include "spike.h"
#include <raylib.h>

int main() {
    const int width = 600;
    const int height = 800;
    SetTraceLogLevel(LOG_NONE);
    InitWindow(width, height, "don't touch the spikes");

    float deltaTime = 0.f;
    bool fps = true;

    SetTraceLogLevel(LOG_DEBUG);
    SetTargetFPS(60);

    spike_init(height);
    bird_init();
    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();
        bird_update(deltaTime);

        if (IsKeyPressed(KEY_R)) {
            spike_reset();
            bird_reset();
        }
        if (IsKeyPressed(KEY_F)) {
            fps = !fps;
            SetTargetFPS(fps ? 60 : 600);
        }

        BeginDrawing();
        ClearBackground((Color){150, 150, 250});
        spike_draw();
        bird_draw();
        EndDrawing();
    }

    return 0;
}

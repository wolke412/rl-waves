#include "raylib.h"

int main() {
  // Initialization
  const int screenWidth = 800; const int screenHeight = 450; InitWindow(screenWidth, screenHeight, "This is an altered c++ file");

  float circleX = screenWidth / 2.0f;
  float circleY = screenHeight / 2.0f;
  float circleRadius = 50.0f;
  float speed = 200.0f;

  SetTargetFPS(60); // Set FPS limit

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    if (IsKeyDown(KEY_RIGHT))
      circleX += speed * GetFrameTime();
    if (IsKeyDown(KEY_LEFT))
      circleX -= speed * GetFrameTime();
    if (IsKeyDown(KEY_UP))
      circleY -= speed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN))
      circleY += speed * GetFrameTime();

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Use arrow keys to move the circle!", 10, 10, 20, DARKGRAY);
    DrawCircleV(Vector2{circleX, circleY}, circleRadius, MAROON);
    EndDrawing();
  }

  // De-Initialization
  CloseWindow();
  return 0;
}

#include "raylib.h"
#include<stdlib.h>
#include<cmath>

// Constants
const float GRAVITY = 980.0f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const float FRICTION = 0.01f;

struct Player {
    Vector2 position;
    Vector2 velocity;
    bool isGrounded;
    float speed;
    float jumpForce;
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Xero - Movement Test");

    Player player = { 0 };
    player.position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 100.0f };
    player.speed = 400.0f;
    player.jumpForce = -600.0f; // Negative because Y increases downward in 2D
    player.isGrounded = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // 1. INPUT HANDLING
        if (IsKeyDown(KEY_LEFT))  player.velocity.x = -player.speed;
        else if (IsKeyDown(KEY_RIGHT)) player.velocity.x = player.speed;
        else
        {
            if (player.isGrounded) {
                player.velocity.x *= FRICTION; // Apply friction when grounded
            }
            if (std::abs(player.velocity.x) < 0.1f) player.velocity.x = 0;
        }

        if (IsKeyPressed(KEY_SPACE) && player.isGrounded) {
            player.velocity.y = player.jumpForce;
            player.isGrounded = false;
        }

        // 2. APPLY PHYSICS
        player.velocity.y += GRAVITY * deltaTime; // Apply Gravity
        player.position.x += player.velocity.x * deltaTime;
        player.position.y += player.velocity.y * deltaTime;

        // 3. BASIC GROUND COLLISION (Floor at SCREEN_HEIGHT - 50)
        float floorLevel = SCREEN_HEIGHT - 50.0f;
        if (player.position.y >= floorLevel) {
            player.position.y = floorLevel;
            player.velocity.y = 0;
            player.isGrounded = true;
        }

 

		if (player.position.x < 20) player.position.x = SCREEN_WIDTH - 20; // Left boundary
		if (player.position.x > SCREEN_WIDTH - 20) player.position.x = 20; // Right boundary

        // 4. DRAWING
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw "Floor"
        DrawRectangle(0, (int)floorLevel + 40, SCREEN_WIDTH, 10, GRAY);

        // Draw Player
        DrawRectangleV({ player.position.x - 20, player.position.y - 40 }, { 40, 40 }, BLUE);

        DrawText("SPACE to Jump, Arrows to Move", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}


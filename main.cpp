#include "raylib.h"
#include "classes.h"

int main()
{

    InitWindow(screenWidth, screenHeight, "Hockey Pong");
    SetTargetFPS(60);
    // score
    int player_score = 0;
    int cpu_score = 0;

    // ball parameters
    ball.width_x = screenWidth / 2;
    ball.height_y = screenHeight / 2;
    ball.radius = 15;
    ball.speed_x = 5;
    ball.speed_y = 5;
    ball.acceleration = 1.5;

    // player1 parameters
    Player player1;
    player1.width = 20;
    player1.height = 100;
    player1.y = (screenHeight / 2) - (player1.height / 2);
    player1.speed = 7;

    // player1 parameters
    //  player2 parameters
    Player2 player2;
    player2.width = 20;
    player2.height = 100;
    player2.y = (screenHeight / 2) - (player2.height / 2);
    player2.speed = 7;
    // CPU parameters
    /* CPU cpu;
    cpu.cpu_x = 10;
    cpu.cpu_y = (screenHeight / 2) - (player.height / 2);
    cpu.width = 20;
    cpu.height = 100;
    cpu.speed = 7; */

    while (!WindowShouldClose())
    {
        // Event
        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(screenWidth - player1.width - 10), float(player1.y), float(player1.width), float(player1.height)}) && !IsKeyDown(KEY_LEFT))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(10), float(player2.y), float(player2.width), float(player2.height)}) && !IsKeyDown(KEY_D))
        {
            ball.speed_x *= -1;
        }
        // Powershot 1
        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(screenWidth - player1.width - 10), float(player1.y), float(player1.width), float(player1.height)}) && IsKeyDown(KEY_LEFT))
        {
            ball.speed_x += ball.acceleration;
            ball.speed_x *= -1;
            if (ball.speed_y > 4)
            {
                ball.speed_y += ball.acceleration;
                player1.speed += ball.acceleration;
                player2.speed += ball.acceleration;
            }
        }

        // Powershot 2
        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(10), float(player2.y), float(player2.width), float(player2.height)}) && IsKeyDown(KEY_D))
        {
            ball.speed_x += ball.acceleration;
            ball.speed_x *= -1;
            if (ball.speed_y > 4)
            {
                ball.speed_y += ball.acceleration;
                player1.speed += ball.acceleration;
                player2.speed += ball.acceleration;
            }
        }

        // Goal check
        if (ball.width_x - ball.radius <= 0)
        {
            player_score += 1;
            player1.speed = 7;
            player2.speed = 7;
            ball.speed_y = 5;
            ball.speed_x = 5;
            ball.goal();
        }
        else if (ball.width_x + ball.radius >= screenWidth)
        {
            cpu_score += 1;
            player1.speed = 7;
            player2.speed = 7;
            ball.speed_y = 5;
            ball.speed_x = 5;
            ball.goal();
        }

        // Movement
        ball.MoveBall();
        player1.MovePlayer();
        player2.MovePlayer();

        // Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // drawing big circles
        DrawCircle(screenWidth / 2, screenHeight / 2, 100, BLUE); // central circle
        DrawCircle(screenWidth / 2, screenHeight / 2, 95, WHITE);
        DrawCircle(screenWidth / 8, screenHeight / 4, 100, RED); // upper left circle
        DrawCircle(screenWidth / 8, screenHeight / 4, 95, WHITE);
        DrawCircle(screenWidth / 8, 3 * screenHeight / 4, 100, RED); // under left circle
        DrawCircle(screenWidth / 8, 3 * screenHeight / 4, 95, WHITE);
        DrawCircle(7 * screenWidth / 8, 3 * screenHeight / 4, 100, RED); // under right circle
        DrawCircle(7 * screenWidth / 8, 3 * screenHeight / 4, 95, WHITE);
        DrawCircle(7 * screenWidth / 8, screenHeight / 4, 100, RED); // upper right circle
        DrawCircle(7 * screenWidth / 8, screenHeight / 4, 95, WHITE);
        // Drawing a hockey field Lines
        DrawLineEx(Vector2{float(screenWidth / 2), 0}, Vector2{float(screenWidth / 2), 700}, 10.0f, RED);                                                          // central red line
        DrawLineEx(Vector2{float(2 * ((screenWidth / 2) / 3)), 0}, Vector2{float(2 * ((screenWidth / 2) / 3)), 700}, 10.0f, BLUE);                                 // left blue line
        DrawLineEx(Vector2{float((screenWidth / 2) + ((screenWidth / 2) / 3)), 0}, Vector2{float((screenWidth / 2) + ((screenWidth / 2) / 3)), 700}, 10.0f, BLUE); // right blue line
        // puck circles
        DrawCircle(screenWidth / 2, screenHeight / 2, 15, BLUE);                                     // central circle for puck
        DrawCircle((screenWidth / 2) + ((screenWidth / 2) / 3) - 40, screenHeight / 4, 15, RED);     // right upcircle for puck
        DrawCircle((screenWidth / 2) + ((screenWidth / 2) / 3) - 40, 3 * screenHeight / 4, 15, RED); // right undercircle for puck
        DrawCircle(2 * ((screenWidth / 2) / 3) + 40, screenHeight / 4, 15, RED);                     // left upcircle for puck
        DrawCircle(2 * ((screenWidth / 2) / 3) + 40, 3 * screenHeight / 4, 15, RED);                 // left undercircle for puck
        DrawCircle(7 * screenWidth / 8, screenHeight / 4, 15, RED);                                  // far upper right circle for puck
        DrawCircle(7 * screenWidth / 8, 3 * screenHeight / 4, 15, RED);                              // far under right circle for puck
        DrawCircle(screenWidth / 8, 3 * screenHeight / 4, 15, RED);                                  // far under left circle for puck
        DrawCircle(screenWidth / 8, screenHeight / 4, 15, RED);                                      // far upper left circle for puck

        DrawText(TextFormat("%i", cpu_score), screenWidth / 4, 10, 100, BLUE);
        DrawText(TextFormat("%i", player_score), 3 * screenWidth / 4, 10, 100, RED);
        ball.DrawBall();
        player1.DrawPlayer();
        player2.DrawPlayer();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
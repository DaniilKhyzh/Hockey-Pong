#include "raylib.h"

int screenWidth = 1200;
int screenHeight = 700;

class Ball
{
public:
    int width_x;
    int height_y;
    int radius;
    int speed_x;
    int speed_y;

    void DrawBall()
    {
        DrawCircle(width_x, height_y, radius, BLACK);
    }

    void MoveBall()
    {
        height_y -= speed_y;
        width_x -= speed_x;
        if (height_y - radius <= 0 || height_y + radius >= screenHeight)
        {
            speed_y *= -1;
        }
    }

    void goal()
    {
        int ballspeed[2] = {-1, 1};
        width_x = screenWidth / 2;
        height_y = screenHeight / 2;
        speed_x *= ballspeed[GetRandomValue(0, 1)];
        speed_y *= ballspeed[GetRandomValue(0, 1)];
    }
};

Ball ball; // making ball global

class Player
{
public:
    int width;
    int height;
    int speed;
    int y;

    void DrawPlayer()
    {
        DrawRectangleRounded(Rectangle{float(screenWidth - width - 10), float(y), float(width), float(height)}, 5.0f, 4, RED);
    }

    void MovePlayer()
    {
        if (IsKeyDown(KEY_UP) && y >= 0)
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN) && y <= screenHeight - height)
        {
            y += speed;
        }
    }
};

class CPU
{
public:
    int cpu_x;
    int cpu_y;
    int width;
    int height;
    int speed;

    void cpuDraw()
    {
        DrawRectangleRounded(Rectangle{float(cpu_x), float(cpu_y), float(width), float(height)}, 5.0f, 4, BLUE);
    }

    void Move()
    {
        if (ball.height_y >= cpu_y + (height / 2) && cpu_y <= screenHeight - height)
        {
            cpu_y += speed;
        }
        if (ball.height_y <= cpu_y + (height / 2) && cpu_y >= 0)
        {
            cpu_y -= speed;
        }
    }
};

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

    // player parameters
    Player player;
    player.width = 20;
    player.height = 100;
    player.y = (screenHeight / 2) - (player.height / 2);
    player.speed = 7;

    // CPU parameters
    CPU cpu;
    cpu.cpu_x = 10;
    cpu.cpu_y = (screenHeight / 2) - (player.height / 2);
    cpu.width = 20;
    cpu.height = 100;
    cpu.speed = 7;

    while (!WindowShouldClose())
    {
        // Event
        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(screenWidth - player.width - 10), float(player.y), float(player.width), float(player.height)}) && !IsKeyDown(KEY_LEFT))
        {
            ball.speed_x *= -1;
        }
        // Powershot
        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(screenWidth - player.width - 10), float(player.y), float(player.width), float(player.height)}) && IsKeyDown(KEY_LEFT))
        {
            ball.speed_x *= -2;
            if (ball.speed_y > 4)
            {
                ball.speed_y += 4;
            }
            else if (ball.speed_y > 6 || ball.speed_y < -6)
            {
                ball.speed_y *= 2;
            }
            else
            {
                ball.speed_y -= 4;
            }
        }

        if (CheckCollisionCircleRec({float(ball.width_x), float(ball.height_y)}, float(ball.radius), {float(cpu.cpu_x), float(cpu.cpu_y), float(cpu.width), float(cpu.height)}))
        {
            if (ball.speed_x < -5) // if powershot was saved
            {
                ball.speed_x -= 2;
            }
            else
            {
                ball.speed_x *= -1;
            }

            if (ball.speed_y > 5)
            {
                ball.speed_y -= 2;
            }
            else if (ball.speed_y < -5)
            {
                ball.speed_y += 2;
            }
        }

        // Goal check
        if (ball.width_x - ball.radius <= 0)
        {
            player_score += 1;
            ball.speed_y = 5;
            ball.speed_x = 5;
            ball.goal();
        }
        else if (ball.width_x + ball.radius >= screenWidth)
        {
            cpu_score += 1;
            ball.speed_y = 5;
            ball.speed_x = 5;
            ball.goal();
        }

        // Movement
        ball.MoveBall();
        player.MovePlayer();
        cpu.Move();
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
        player.DrawPlayer();
        cpu.cpuDraw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
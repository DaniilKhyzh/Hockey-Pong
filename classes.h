#include "raylib.h"

float screenWidth = 1200.0;
float screenHeight = 700.0;

class Ball
{
public:
    float width_x;
    float height_y;
    float radius;
    float speed_x;
    float speed_y;
    float acceleration;

    void DrawBall()
    {
        DrawCircle(width_x, height_y, radius, BLACK);
    }

    void MoveBall()
    {
        height_y -= speed_y;
        width_x -= speed_x;
        if (height_y - radius + 1 <= 1 || height_y + radius >= screenHeight)
        {
            height_y = 3;
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

Ball ball;

class Player
{
public:
    float width;
    float height;
    float speed;
    float y;

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

/* class CPU
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
}; */

class Player2
{
public:
    float width;
    float height;
    float speed;
    float y;

    void DrawPlayer()
    {
        DrawRectangleRounded(Rectangle{float(10), float(y), float(width), float(height)}, 5.0f, 4, BLUE);
    }

    void MovePlayer()
    {
        if (IsKeyDown(KEY_W) && y >= 0)
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_S) && y <= screenHeight - height)
        {
            y += speed;
        }
    }
};

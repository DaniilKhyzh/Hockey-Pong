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

Ball ball;

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

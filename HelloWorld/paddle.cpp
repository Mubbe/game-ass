#include "Paddle.h"


void drawPaddle(const Paddle& p)
{
    Vector2f topLeft = p.pos;
    Vector2f botRight = p.pos + p.size;

    DrawRect(topLeft, botRight, cWhite, true);
}


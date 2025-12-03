#pragma once
#include "Play.h"

using namespace Play;


struct Paddle
{
	Vector2f pos;
	Vector2f size;
	

	Paddle() : pos({ 0.0f, 0.0f }), size({ 80.0f, 10.0f })
	{

	}
};


void drawPaddle(const Paddle& p);
void UpdatePaddle();

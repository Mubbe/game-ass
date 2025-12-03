#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Paddle.h"


void spawnball();

void StepFrame(float elapstime);

void SetupScene();

bool IsColliding(const Paddle& p, const Play::GameObject& obj);




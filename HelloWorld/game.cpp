#include "game.h"
#define PLAY_USING_GAMEOBJECT_MANAGER
#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "constants.h"
#include "paddle.h"
#include "score.h"
bool gameover = false;
Score new_score;
Paddle new_paddle = Paddle();
CaurentScore new_caurent_score;
void spawnball()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 1, DISPLAY_HEIGHT - 60 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, 1 }) * ballSpeed;


}

void StepFrame(float elapstime)
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);

	

	for (int i = 0; i < ballIds.size(); i++)
	{
		GameObject& ball = Play::GetGameObject(ballIds[i]);

		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0)
		{
			ball.velocity.x *= -1;

		}
		if (ball.pos.y > DISPLAY_HEIGHT)
		{
			ball.velocity.y *= -1;
		
		}
		if (ball.pos.y < 0 && !gameover) {
			gameover = true;  //this check if the gameover and print out gameover.
			newArray.pushback(new_caurent_score.score);
			save_file();
		}
		if (IsColliding(new_paddle, ball))
		{
			ball.velocity.y *= -1;
			
		}
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);
	}
	if (gameover)
	{
		DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "GAME OVER", cRed, true);
	}
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for(int j= 0; j < brickIds.size(); j++)
	{
		int brick = brickIds[j];
		for (int i = 0; i < ballIds.size(); i++)
		{
			int ball = ballIds[i];

			if (Play::IsColliding(Play::GetGameObject(ball), Play::GetGameObject(brick)))
			{
				Play::DestroyGameObject(brick);
				Play::GetGameObject(ball).velocity.y *= -1;
				new_caurent_score.score++;
				break;

			}
		}
		Play::UpdateGameObject(Play::GetGameObject(brickIds[j]));
		Play::DrawObject(Play::GetGameObject(brickIds[j]));
	}
	 drawPaddle(new_paddle);
	 UpdatePaddle();
	 draw_cur_score(new_caurent_score);
	 draw_score(new_score);
}

void SetupScene()
{
	int spriteId = GetSpriteId("brick");
	const Vector2f spriteSize = Play::Graphics::GetSpriteSize(spriteId);
	
	for (int x = 0; x < DISPLAY_WIDTH; x+=spriteSize.x)
	{
		for (int y = 300; y < DISPLAY_HEIGHT; y+=spriteSize.y)
		{
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x , y }, 7, "brick");
		
		}
		
	}
}


void UpdatePaddle()
{
	int speed_of_paddle;
	speed_of_paddle = 5;
	// if the gameover the paddle pos doesn't update
	if (gameover)
	{
		return;
	}
	if (KeyDown(KEY_LEFT))
	{
		if (new_paddle.pos.x < 0 )
		{
			new_paddle.pos.x += 1;
		}
		else
		{
			new_paddle.pos.x -= speed_of_paddle;
		}
		

	}
	if (KeyDown(KEY_RIGHT) || KeyDown(KEY_D)) 
	{
		if (new_paddle.pos.x >= DISPLAY_WIDTH - new_paddle.size.x)
		{
			new_paddle.pos.x -= 1;
		}
		else
		{
			new_paddle.pos.x += speed_of_paddle;
		}
			
	}
}


bool IsColliding(const Paddle& p, const Play::GameObject& obj)
{
	Vector2f topLeft = p.pos;
	Vector2f botRight = p.pos + p.size;

	const float dx = obj.pos.x - max(topLeft.x, min(obj.pos.x, botRight.x));
	const float dy = obj.pos.y - max(topLeft.y, min(obj.pos.y, botRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}





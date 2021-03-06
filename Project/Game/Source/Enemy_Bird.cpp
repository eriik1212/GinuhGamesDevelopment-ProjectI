#include "Enemy_Bird.h"

#include "App.h"
#include "Log.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "Scene.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Player.h"
#include "Map.h"
#include "Input.h"
#include "HUD.h"



Enemy_Bird::Enemy_Bird(bool enabled, int x, int y) : Enemy(x, y), Module(enabled)
{
	// LEFT

	//Idle anim
	leftStandB.PushBack({ 0, 0, 16, 16 });
	leftStandB.PushBack({ 16, 0, 16, 16 });
	leftStandB.PushBack({ 0, 32, 16, 16 });
	leftStandB.PushBack({ 16, 32, 16, 16 });
	leftStandB.PushBack({ 32, 32, 16, 16 });
	leftStandB.PushBack({ 16, 32, 16, 16 });
	leftStandB.PushBack({ 0, 32, 16, 16 });
	leftStandB.loop = true;
	leftStandB.speed = 0.15f;

	//flying
	leftFlyB.PushBack({ 0, 16, 16, 16 });
	leftFlyB.PushBack({ 16, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 2, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 3, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 4, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 5, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 6, 16, 16, 16 });
	leftFlyB.PushBack({ 16 * 7, 16, 16, 16 });
	leftFlyB.loop = true;
	leftFlyB.speed = 0.15f;



	//RIGHT
	//idle anim
	rightStandB.PushBack({ 112, 48, 16, 16 });
	rightStandB.PushBack({ 96, 48, 16, 16 });
	rightStandB.PushBack({ 112, 80, 16, 16 });
	rightStandB.PushBack({ 96, 80, 16, 16 });
	rightStandB.PushBack({ 80, 80, 16, 16 });
	rightStandB.PushBack({ 96, 80, 16, 16 });
	rightStandB.PushBack({ 112, 80, 16, 16 });
	rightStandB.loop = true;
	rightStandB.speed = 0.15f;

	//flying
	leftFlyB.PushBack({ 112, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 2, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 3, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 4, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 5, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 6, 64, 16, 16 });
	leftFlyB.PushBack({ 112 - 16 * 7, 64, 16, 16 });
	leftFlyB.loop = true;
	leftFlyB.speed = 0.15f;

	//PATH

	//Collider
	birdBody.x = x;
	birdBody.y = y;
	birdBody.w = 16;
	birdBody.h = 16;

	birdCollider.AddCollider(birdBody.x, birdBody.y, birdBody.w, birdBody.h);

	coolDownBird = 0;
}


void Enemy_Bird::Update()
{

	//Check Enemy Attack Collision
	coolDownBird++;

	if (!app->play->godMode && coolDownBird > 100 && app->play->playerData.GetCollider().CheckCollision(birdCollider.GetCollider(), 0.0f, ENEMY))
	{
		//app->play->playerData.GetCollider().CheckCollision(birdCollider.GetCollider(), 0.0f, ENEMY);
		app->hud->lifes--;
		coolDownBird = 0;
		
	}
	else if (app->play->playerData.GetCollider().CheckCollision(birdCollider.GetCollider(), 0.0f, ENEMY) == false)
	{
		coolDownBird = 101;
	}

	if (coolDownBird >= 101) coolDownBird = 101;

	//Check Player Attack Collision
	if (app->play->playerData.attacking == true)
	{
		if (app->play->attackCollider.GetCollider().CheckCollision(birdCollider.GetCollider(), 0.0f, ATTACK))
		{
			if (app->play->playerData.direction == 1)
			{
				// For moving the collider
				birdCollider.GetCollider().Move(50, -50);

				// For drawing the collider where it has to be
				birdBody.x += 50;
				birdBody.y -= 50;

				// For changing enemy position
				position.x += 50;
				position.y -= 50;
			}
			else
			{
				// For moving the collider
				birdCollider.GetCollider().Move(-50, -50);

				// For drawing the collider where it has to be
				birdBody.x -= 50;
				birdBody.y -= 50;

				// For changing enemy position
				position.x -= 50;
				position.y -= 50;
			}



		}

	}

	if (app->play->collidersOn == true)
	{
		birdCollider.GetCollider().DebugDraw(birdBody, ENEMY);
	}

	//------------------------------------------------------------LEFT direcction
	if (currentAnim == &leftStandB) direcction = 0;
	if (currentAnim == &leftFlyB) direcction = 0;
	
	//------------------------------------------------------------RIGHT ANIM direction
	if (currentAnim == &rightStandB) direcction = 1;
	if (currentAnim == &leftFlyB) direcction = 1;

	if (app->enemies->birdHitted)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (app->enemies->enemies[i] != nullptr)
			{
				if (app->enemies->enemies[i]->lifes[0] == 0)
				{
					app->enemies->points += 2;
					delete app->enemies->enemies[i];
					app->enemies->enemies[i] = nullptr;
				}
			}
		}

		app->enemies->birdHitted = false;
	}

	
	currentAnim = &leftStandB;
	Enemy::Update();
}





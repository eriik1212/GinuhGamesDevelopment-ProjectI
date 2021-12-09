#include "Enemies.h"

#include "App.h"
#include "Defs.h"
#include "Log.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"

#include "Player.h"

#include "Enemy.h"
#include "Enemy_Bird.h"
#include "Enemy_Fox.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool enabled) : Module(enabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{

	fox = app->tex->Load("Assets/enemies/fox_sprites.png");
	bird = app->tex->Load("Assets/enemies/bird_sprites.png");
	

	enemyDamageFX = app->audio->LoadFx("Assets/audio/FX/enter.wav");
	enemyDestroyedFx = app->audio->LoadFx("Assets/audio/FX/enter.wav");

	return true;
}

bool ModuleEnemies::Update(float dt)
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return true;
}

bool ModuleEnemies::PostUpdate()
{



	

	return true;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * app->win->GetScale() < app->render->camera.x + (app->render->camera.w * app->win->GetScale()) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * app->win->GetScale());

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			/*if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}*/
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case ENEMY_TYPE::BIRD:
				enemies[i] = new Enemy_Bird(true, info.x, info.y);
				enemies[i]->texture = bird;
				enemies[i]->destroyedFx = enemyDestroyedFx;
				enemies[i]->damageFX = enemyDamageFX;

				for (int a = 0; a < MAX_LIFE; ++a) {
					enemies[i]->lifes[a] = 1;
				}
				break;
			case ENEMY_TYPE::FOX:
				enemies[i] = new Enemy_Fox(info.x, info.y);
				enemies[i]->texture = fox;
				enemies[i]->destroyedFx = enemyDestroyedFx;
				enemies[i]->damageFX = enemyDamageFX;
				for (int a = 0; a < MAX_LIFE; ++a) {
					enemies[i]->lifes[a] = 1;
				}
				break;
			
			}

			break;
		}
	}
}
void updateLifes(unsigned short* lifes, unsigned short damage)
{

	for (int i = (MAX_LIFE - 1); i >= 0; --i) {

		if (*(lifes + i) == 0) {
			++damage;
		}
		else if (*(lifes + i) == 1 && i >= (MAX_LIFE - damage)) {
			*(lifes + i) = 0;
		}
	}
}

/*void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision

			if (app->collisions->matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_HIT])
			{
				App->collisions->matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
			}
			//---------------------------------------------------------------iNTENT DE VIDES ALS ENEMICS-----------------------------------------------
			updateLifes(enemies[i]->lifes, 1);
			if (enemies[i]->lifes[0] == 0)
			{
				App->HUD->scoreP1++;
				delete enemies[i];
				enemies[i] = nullptr;
			}





			break;
		}
	}
}*/
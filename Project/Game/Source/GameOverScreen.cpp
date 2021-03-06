#include "GameOverScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "FadeToBlack.h"
#include "Log.h"
#include "Level2.h"


GameOverScreen::GameOverScreen(bool enabled) : Module(enabled)
{
	
}

GameOverScreen::~GameOverScreen()
{

}

// Load assets
bool GameOverScreen::Start()
{
	//LostGameFX = app->audio->LoadFx("Assets/audio/fx/game_over.wav");

	if (this->Enabled())
	{
		// Load music
		app->audio->StopMusic();
		app->audio->PlayMusic("Assets/audio/fx/game_over.wav");
		
		//Disable Player & map
		app->play->Disable();
		app->map->Disable();
	}

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	// Members Texture
	GameOverTex = app->tex->Load("Assets/textures/gameover.png");

	//Aqui podem posar algun so a veure amb la pantalla d'inici
	//app->audio->PlayMusic("Assets/Audio/02_character_selection.ogg", 1.0f);

	//Fade In
	app->fade->FadeToBlack(this, app->gameOver, 30);

	return true;
}

bool GameOverScreen::Update(float dt)
{
	// ScanCodes
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		//Fade Out
		if (app->play->lastLevel == 1)
		{
			app->fade->FadeToBlack(this, app->scene, 30);
			app->LoadGameRequest();


		}
		else if (app->play->lastLevel == 2)
		{
			app->fade->FadeToBlack(this, app->level2, 30);
			app->LoadGameRequest();


		}
		app->audio->StopMusic();
		//app->play->revive = true;
		app->play->playerData.isDead = false;
	}

	else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool GameOverScreen::PostUpdate()
{
	app->render->DrawTexture(GameOverTex, 0, 0, true, NULL);
	return true;
}

// Called before quitting
bool GameOverScreen::CleanUp()
{
	LOG("Freeing GameOverScreen");

	app->tex->CleanUp();

	return true;
}
#include "LogoScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "FadeToBlack.h"
#include "GameOverScreen.h"


LogoScreen::LogoScreen(bool enabled) : Module(enabled)
{
	
}

LogoScreen::~LogoScreen()
{

}

// Load assets
bool LogoScreen::Start()
{
	
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	backgroundLogo.x = 0;
	backgroundLogo.y = 0;
	backgroundLogo.w = 690;
	backgroundLogo.h = 480;

	// Members Texture
	screen = app->tex->Load("Assets/textures/ginuh_logo.png");

	//Aqui podem posar algun so a veure amb la pantalla d'inici
	//app->audio->PlayMusic("Assets/Audio/02_character_selection.ogg", 1.0f);

	//Fade In
	app->fade->FadeToBlack(this, app->logo, 30);

	return true;
}

bool LogoScreen::Update(float dt)
{
	
	// ScanCodes
	if (app->input->GetKey(SDL_SCANCODE_RETURN) ==KEY_DOWN)
	{
		//Fade Out
		app->fade->FadeToBlack(this, app->scene, 30);
	}

	else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool LogoScreen::PostUpdate()
{

	app->render->DrawRectangle(backgroundLogo, 255, 255, 255, 255);
	app->render->DrawTexture(screen, 0, 0, NULL);
	return true;
}

#include "TitleScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "FadeToBlack.h"
#include "Level2.h"
#include "GuiManager.h"
#include "Window.h"

#include "Defs.h"
#include "Log.h"


TitleScreen::TitleScreen(bool enabled) : Module(enabled)
{

}

TitleScreen::~TitleScreen()
{

}

// Load assets
bool TitleScreen::Start()
{
	//TitleMusic = app->play->("Assets/audio/fx/game_over.wav");

	if (this->Enabled())
	{
		// Load music
		app->audio->PlayMusic("Assets/audio/music/title_music.ogg");

		//Disable Player & map
		app->play->Disable();
		app->map->Disable();

		app->LoadGameRequest();
		//app->LoadInitialGameRequest();

	}
	changeFX = app->audio->LoadFx("Assets/audio/fx/switching.wav");
	enterFX = app->audio->LoadFx("Assets/audio/fx/enter.wav");

	Title = app->tex->Load("Assets/textures/titleW.png");
	NewGamePressed= app->tex->Load("Assets/textures/PressedNG.png");
	NewGameUnpressed= app->tex->Load("Assets/textures/UnpressedNG.png");
	ContinuePressed= app->tex->Load("Assets/textures/PressedCont.png");
	ContinueUnpressed= app->tex->Load("Assets/textures/UnpressedCont.png");
	SelectArrow = app->tex->Load("Assets/textures/SelectedArrow.png");

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	NewGameRect.x = 288;
	NewGameRect.y = 280;
	NewGameRect.w = 99;
	NewGameRect.h = 16;

	ContinueRect.x = 270;
	ContinueRect.y = 300;
	ContinueRect.w = 152;
	ContinueRect.h = 16;

	settingsRect.x = 270;
	settingsRect.y = 320;
	settingsRect.w = 152;
	settingsRect.h = 16;

	creditsRect.x = 270;
	creditsRect.y = 340;
	creditsRect.w = 152;
	creditsRect.h = 16;

	exitOptionsRect.x = 100;
	exitOptionsRect.y = 0;
	exitOptionsRect.w = 16;
	exitOptionsRect.h = 16;

	backgroundTitle.x = 0;
	backgroundTitle.y = 0;
	backgroundTitle.w = 690;
	backgroundTitle.h = 480;

	// Members Texture
	//GameOverTex = app->tex->Load("Assets/textures/gameover.png");

	//Aqui podem posar algun so a veure amb la pantalla d'inici
	//app->audio->PlayMusic("Assets/Audio/02_character_selection.ogg", 1.0f);

	//Fade In
	//app->fade->FadeToBlack(this, app->title, 30);

	newGameButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "NewGame", NewGameRect, this);
	continueButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Continue", ContinueRect, this);
	settingsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Settings", settingsRect, this);
	creditsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits", creditsRect, this);

	return true;
}

bool TitleScreen::Update(float dt)
{
	// ScanCodes
	/*if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		//Fade Out
		app->audio->PlayFx(enterFX);
		if (option == 1)//New game option
		{
			cont = false;
			app->play->restartLVL1 = true;
			//app->SaveGameRequest();
			app->fade->FadeToBlack(this, app->scene, 30);
			
			app->play->playerData.isDead = false;
			

		}
		else //continue option
		{
			cont = true;
			if (app->play->lastLevel == 1)
			{
				app->fade->FadeToBlack(this, app->scene, 30);
				app->LoadGameRequest();

			}

			if (app->play->lastLevel == 2)
			{
				app->fade->FadeToBlack(this, app->level2, 30);
				app->LoadGameRequest();

			}

		}
		
		
	}

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		app->audio->PlayFx(changeFX);
		option = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		app->audio->PlayFx(changeFX);
		option = 1;
	}*/

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool TitleScreen::PostUpdate()
{

	app->render->DrawTexture(Title, 0, 0, false, NULL);

	/*if (option == 1)
	{
		app->render->DrawTexture(NewGamePressed, 432, 432, false, &NewGameRect);
		app->render->DrawTexture(ContinueUnpressed, 405, 464, false, &ContinueRect);
	}
	else
	{
		app->render->DrawTexture(NewGameUnpressed, 432, 432, false, &NewGameRect);
		app->render->DrawTexture(ContinuePressed, 405, 464, false, &ContinueRect);
	}*/

	//Draw GUI
	app->guiManager->Draw();

	if (optionsEnabled)
	{
		DrawOptionsMenu();
	}

	// DrawTexture TEMPLATE
	//app->render->DrawTexture(nom textura, rectangle.x, rectangle.y, --necesita estar escalat?--, &rectangle)
	return true;
}

bool TitleScreen::CleanUp()
{
	LOG("Freeing TitleScreen");

	return true;
}

bool TitleScreen::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		// ID = 1 -> New Game Button
		// ID = 2 -> Continue Button
		// ID = 3 -> Settings Button
		// ID = 4 -> Credits Button
		// ID = 5 -> ExitOptions Button

		switch (control->id)
		{
		case 1:
			cont = false;

			app->audio->PlayFx(enterFX);

			app->play->restartLVL1 = true;
			//app->SaveGameRequest();
			app->fade->FadeToBlack(this, app->scene, 30);

			app->play->playerData.isDead = false;

			LOG("Click on NewGame");
			break;
		case 2:
			cont = true;

			app->audio->PlayFx(enterFX);

			if (app->play->lastLevel == 1)
			{
				app->fade->FadeToBlack(this, app->scene, 30);
				app->LoadGameRequest();

			}

			if (app->play->lastLevel == 2)
			{
				app->fade->FadeToBlack(this, app->level2, 30);
				app->LoadGameRequest();

			}

			LOG("Click on ContinueGame");
			break;
		case 3:
			optionsEnabled = true;
			break;
		case 4:

			break;
		case 5:
			optionsEnabled = false;
			exitButtonCreated = false;

			break;
		default:
			break;
		}

	}
	//Other cases here

	default: break;
	}

	return true;
}

void TitleScreen::DrawOptionsMenu()
{
	if (!exitButtonCreated)
	{
		LOG("Exit");
		exitOptionsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "ExitOptions", exitOptionsRect, this);
		exitButtonCreated = true;
	}

	app->render->DrawRectangle({ 0,0,50,50 }, 255, 0, 0, 255);
}

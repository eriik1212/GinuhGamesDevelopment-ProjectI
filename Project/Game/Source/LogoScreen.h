#ifndef __MODULE_LOGOSCREEN_H__
#define __MODULE_LOGOSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Scene.h"



struct SDL_Texture;

class LogoScreen : public Module
{
public:
	//Constructor
	LogoScreen(bool enabled);

	//Destructor
	~LogoScreen();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start();

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update(float dt);

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

public:
	// Members Texture
	SDL_Texture* logo;

	SDL_Rect backgroundLogo;
	SDL_Rect logoRect;
};

#endif //__MODULE_MEMBERS_H__

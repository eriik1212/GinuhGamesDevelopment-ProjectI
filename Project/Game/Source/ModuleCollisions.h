#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#define MAX_COLLIDERS 150

#include "Module.h"
#include "Collider.h"

enum Colliders
{
	PLAYER = 0, //0
	WALL // 1
};

class ModuleCollisions
{
public:
	ModuleCollisions();
	~ModuleCollisions();

	// Draws all existing colliders with some transparency
	// PLAYER = 0, WALL = 1
	void DebugDraw(SDL_Rect body, int type);

	Collider AddCollider(int x, int y, int w, int h);
	Collider GetCollider() { return Collider(colliderBody); }

	iPoint origin;

private:

	SDL_Rect colliderBody;
};

/*class ModuleCollisions : public Module
{
public:
	// Constructor
	// Fills all collision matrix data
	ModuleCollisions(bool enabled);

	// Destructor
	~ModuleCollisions();

	// Called at the beginning of the application loop
	// Removes all colliders pending to delete
	// Checks for new collisions and calls its listeners
	bool PreUpdate();

	// Called at the middle of the application loop
	// Switches the debug mode on/off
	bool Update(float dt);

	// Called at the end of the application loop
	// Draw all colliders (if debug mode is enabled)
	bool PostUpdate();

	// Removes all existing colliders
	bool CleanUp();

	// Adds a new collider to the list
	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);

	// Draws all existing colliders with some transparency
	void DebugDraw();

	bool matrix[Collider::Type::MAX][Collider::Type::MAX];
	//bool GodMode = true;

private:
	// All existing colliders in the scene
	Collider* colliders[MAX_COLLIDERS] = { nullptr };

	// The collision matrix. Defines the interaction for two collider types
	// If set two false, collider 1 will ignore collider 2


	// Simple debugging flag to draw all colliders
	bool showColl = false;

};*/

#endif // __MODULE_COLLISIONS_H__
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Render.h"
#include "ModuleCollisions.h"
#include "Collider.h"

struct SDL_Texture;
struct Collider;

struct PlayerData
{
	// The player's body
	SDL_Rect playerBody;

	int xVel, yVel, maxVel;
	int gravity;

	bool jumping;
	bool canJumpAgain;

	bool attacking;

	bool isDead, winner, isCollidingUp;

	int direction; //1 if player looks right, 0 if player looks left

	Collider GetCollider() { return Collider(playerBody); }

};

class Player : public Module
{
public:

	Player(bool enabled);

	// Destructor
	virtual ~Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	bool collidersOn = false;
	bool debug = false;
	bool godMode = false;
	bool inLeader = false;

	int lastLevel = 1;

	bool inBirdView = false;
	bool inFoxView = false;
	
	bool chekpoint = false;

private:
	SDL_Texture* img;

	uint CheckPointFX;

	// Load player general properties
	bool LoadPlayer(pugi::xml_node player);

public:
	PlayerData playerData;

	bool restartLVL1 = false;
	bool restartLVL2 = false;

	ModuleCollisions attackCollider;
	SDL_Rect attackColliderRect;

	SDL_Texture* playerTex = nullptr;
	SDL_Texture* fullHeart = nullptr;
	SDL_Texture* emptyHeart = nullptr;

	int lifes;

	Animation walkR,
		walkL,
		jumpR,
		jumpL,
		idleAnimL,
		idleAnimR,
		deathAnimR,
		deathAnimL,
		victory,
		upStairsL,
		upStairsR,
		hit1L,
		hit1R,
		hit2L,
		hit2R,
		getsDamagedL,
		getsDamagedR;

	SDL_Texture* winTexture;


};
#endif // __PLAYER_H__
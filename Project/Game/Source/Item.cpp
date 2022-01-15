#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"

Item::Item(uint32 id, SDL_Rect bounds) : Entity(EntityType::ITEM)
{
	name.Create("item");

	this->pos = iPoint(bounds.x, bounds.y);
}

Item::~Item() {}


bool Item::Update(float dt)
{
	if (isPicked == true)
	{

	}

	return true;
}

bool Item::Draw(Render* render)
{
	//L13: TODO 3: Draw the item
	render->DrawRectangle({ pos.x,pos.y,20,20 }, 0, 0, 255);

	return true;
}

bool Item::CleanUp()
{

	return true;
}
/**********************************************************************************
// Food (Código Fonte)
//
// Criação:     03 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Comida do SVW
//
**********************************************************************************/

#include "SVW.h"
#include "Projectile.h"
#include "Player.h"
#include "GameManager.h"
#include "Wall.h"

// ---------------------------------------------------------------------------------

Projectile::Projectile(Player* player, float velX, float velY, Image* image)
{
	this->player = player;

	this->velX = velX;
	this->velY = velY;

	type = PROJECTILE;

	sprite = new Sprite(image);
}

// ---------------------------------------------------------------------------------

Projectile::~Projectile()
{
	delete sprite;
}

void Projectile::OnCollision(Object* obj) {
	if (obj->Type() == PLAYER && player != obj) {
		GameManager::currLevel->scene->Delete(this, MOVING);
	} else if (obj->Type() == WALL) {
		Wall* wall = (Wall*)obj;

		GameManager::currLevel->scene->Delete(this, PROJECTILE);
	}
}

// ---------------------------------------------------------------------------------

void Projectile::Update()
{
	Translate(velX * gameTime, velY * gameTime);

	if (y < 0 || x < 0 || y > window->Height() || x > window->Width()) {
		GameManager::currLevel->scene->Delete();
	}
	
}


// ---------------------------------------------------------------------------------

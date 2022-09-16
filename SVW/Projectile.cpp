/**********************************************************************************
// Food (C�digo Fonte)
//
// Cria��o:     03 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Comida do SVW
//
**********************************************************************************/

#include "SVW.h"
#include "Projectile.h"
#include "Player.h"
#include "GameManager.h"
#include "Wall.h"
#include "LevelAnim.h"

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

		if (GameManager::explosionTs && !player->specialPower) {
			LevelAnim* anim = new LevelAnim(GameManager::explosionTs, 0.1f);

			anim->MoveTo(x, y);

			GameManager::currLevel->scene->Add(anim, STATIC);
		}
		else if (GameManager::blueExplosionTs && player->specialPower) {
			LevelAnim* anim = new LevelAnim(GameManager::blueExplosionTs, 0.1f);

			anim->MoveTo(x, y);

			GameManager::currLevel->scene->Add(anim, STATIC);
		}
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

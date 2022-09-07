/**********************************************************************************
// Food (C�digo Fonte)
//
// Cria��o:     03 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Comida do PacMan
//
**********************************************************************************/

#include "PacMan.h"
#include "Projectile.h"
#include "Player.h"
#include "GameManager.h"

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
	if ((obj->Type() == PLAYER1 || obj->Type() == PLAYER2) && player != obj) {
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

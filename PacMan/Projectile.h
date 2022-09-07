/**********************************************************************************
// Food (Arquivo de Cabe�alho)
//
// Cria��o:     03 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tiro do PacMan
//
**********************************************************************************/

#ifndef _PACMAN_PROJECTILE_H_
#define _PACMAN_PROJECTILE_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"                     // jogador do PacMan

// ---------------------------------------------------------------------------------

class Projectile : public Object
{
private:
	Sprite* sprite = nullptr;          // sprite da comida
	Player* player = nullptr;
	Image* image = nullptr;

	float velX;
	float velY;

public:
	Projectile(Player* player, float velX, float velY, Image * image);
	~Projectile();

	void OnCollision(Object* obj);     // resolu��o da colis�o

	void Update();
	void Draw();
};

// ---------------------------------------------------------------------------------

inline void Projectile::Draw()
{
	sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif
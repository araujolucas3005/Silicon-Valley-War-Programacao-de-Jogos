/**********************************************************************************
// Food (Arquivo de Cabe�alho)
//
// Cria��o:     03 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tiro do SVW
//
**********************************************************************************/

#ifndef _SVW_PROJECTILE_H_
#define _SVW_PROJECTILE_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"                     // jogador do SVW

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
	Player* PlayerInfo();
};

// ---------------------------------------------------------------------------------

inline void Projectile::Draw()
{
	sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

inline Player* Projectile::PlayerInfo()
{
	return player;
}

// ---------------------------------------------------------------------------------

#endif
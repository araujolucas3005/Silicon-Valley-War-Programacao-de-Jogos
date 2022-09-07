/**********************************************************************************
// Food (Arquivo de Cabeçalho)
//
// Criação:     03 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tiro do PacMan
//
**********************************************************************************/

#ifndef _PACMAN_PROJECTILE_H_
#define _PACMAN_PROJECTILE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
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

	void OnCollision(Object* obj);     // resolução da colisão

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
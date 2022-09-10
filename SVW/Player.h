/**********************************************************************************
// Player (Arquivo de Cabe�alho)
//
// Cria��o:     01 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Player do jogo SVW
//
**********************************************************************************/

#ifndef _SVW_PLAYER_H_
#define _SVW_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Image.h"
#include "Scene.h"
#include "Timer.h"
#include "string"
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss�veis para o jogador

enum PLAYERSTATE { STOPED, UP, DOWN, LEFT, RIGHT };
enum PLAYERTYPE { PLAYER1, PLAYER2 };

struct MovementKeys {
	int up;
	int left;
	int down;
	int right;
	int shoot;
};

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	Sprite* spriteL = nullptr;         // sprite do player indo para esquerda
	Sprite* spriteR = nullptr;         // sprite do player indo para direita
	Sprite* spriteU = nullptr;         // sprite do player indo para cima
	Sprite* spriteD = nullptr;         // sprite do player indo para baixo
	Sprite* playerTypeSprite = nullptr;// sprite para identificar o jogador 1 ou 2
	Sprite* letterP = nullptr;
	vector<Sprite*> lifeChain;
	Image* heart = nullptr;				// sprite do coracao
	PLAYERTYPE playerType;

	float velX = 0;                     // velocidade horizontal do player
	float velY = 0;                     // velocidade vertical do player
	int life = 5;					// vida do jogador

	Image* bulletVerImg = nullptr;
	Image* bulletHoriImg = nullptr;

	Image* specialPowerUp = nullptr;
	Image* specialPowerLeft = nullptr;
	Image* specialPowerRight = nullptr;
	Image* specialPowerDown = nullptr;

	Timer* timer = nullptr;
	Timer* specialPowerTimer = nullptr;

	boolean ctrlShot;

	MovementKeys movementKeys;

public:
	uint currState = STOPED;            // estado atual do jogador
	uint nextState = STOPED;            // pr�ximo estado do jogador
	bool specialPower = false;
	float prevX;
	float prevY;

	Player(MovementKeys movementKeys, PLAYERTYPE pt);
	~Player();                          // destrutor

	void Stop();                        // p�ra jogador
	void Up();                          // muda dire��o para cima
	void Down();                        // muda dire��o para baixo
	void Left();                        // muda dire��o para esquerda
	void Right();                       // muda dire��o para direita

	void OnCollision(Object* obj);     // resolu��o da colis�o
	void PivotCollision(Object* obj);  // revolve colis�o com piv�

	void Update();                      // atualiza��o do objeto
	void Draw();                        // desenho do objeto
};

#endif
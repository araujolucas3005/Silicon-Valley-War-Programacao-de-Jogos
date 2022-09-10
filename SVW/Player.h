/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo SVW
//
**********************************************************************************/

#ifndef _SVW_PLAYER_H_
#define _SVW_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
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

// estados possíveis para o jogador

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
	uint nextState = STOPED;            // próximo estado do jogador
	bool specialPower = false;
	float prevX;
	float prevY;

	Player(MovementKeys movementKeys, PLAYERTYPE pt);
	~Player();                          // destrutor

	void Stop();                        // pára jogador
	void Up();                          // muda direção para cima
	void Down();                        // muda direção para baixo
	void Left();                        // muda direção para esquerda
	void Right();                       // muda direção para direita

	void OnCollision(Object* obj);     // resolução da colisão
	void PivotCollision(Object* obj);  // revolve colisão com pivô

	void Update();                      // atualização do objeto
	void Draw();                        // desenho do objeto
};

#endif
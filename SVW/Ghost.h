/**********************************************************************************
// Ghost (Arquivo de Cabeçalho)
// 
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Fantasmas do SVW
//
**********************************************************************************/

#ifndef _SVW_GHOST_H_
#define _SVW_GHOST_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"                     // jogador do SVW

// ---------------------------------------------------------------------------------

class Ghost : public Object
{
private:
    Sprite * sprite = nullptr;          // sprite do player
    Player * player = nullptr;          // ponteiro para jogador

public:
    float velX = 0;                     // velocidade horizontal
    float velY = 0;                     // velocidade vertical

    Ghost(Player * p);                  // construtor
    ~Ghost();                           // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Ghost::Draw()
{ sprite->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
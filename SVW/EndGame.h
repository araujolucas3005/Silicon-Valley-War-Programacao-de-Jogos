#pragma once
/**********************************************************************************
// EndGame (Arquivo de Cabe�alho)
//
// Descri��o:   Tela de fim de jogo
//
**********************************************************************************/

#ifndef _SVW_LEVEl1_H_
#define _SVW_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Level.h"

// ------------------------------------------------------------------------------

class EndGame : public Game, Level
{
private:
    Sprite* backg = nullptr;       // background
    Sprite* player = nullptr;
    bool ctrlKeyEnter = false;

public:
    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// -----------------------------------------------------------------------------

#endif
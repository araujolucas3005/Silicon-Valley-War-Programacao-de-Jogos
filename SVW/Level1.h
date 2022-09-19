/**********************************************************************************
// Level1 (Arquivo de Cabe�alho)
// 
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   N�vel 1 do jogo SVW
//
**********************************************************************************/

#ifndef _SVW_LEVEl1_H_
#define _SVW_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Level.h"
#include "TileSet.h"
#include "Audio.h"
#include "Font.h"
#include "Timer.h"
#include "Player.h"


// ------------------------------------------------------------------------------

class Level1 : public Game, Level
{
private:
    Player* playerOne = nullptr;
    Player* playerTwo = nullptr;

    Sprite * backg = nullptr;       // background
    bool viewBBox = false;          // habilita visualiza��o da bounding box
    bool ctrlKeyB = false;          // controle da tecla B
    Timer* foodTime = nullptr;      // controla o tempo para aparecer comidas
    Audio* audio = nullptr;         // controla o audio

    boolean musicCtrl[2] = { 0 };

    TileSet* explosionTs = nullptr;
    TileSet* blueExplosionTs = nullptr;
    TileSet* puffTs = nullptr;

    Font* fontTimer = nullptr;

    Timer* levelTimer = nullptr;
    Timer* endingTimer = nullptr;

public:
    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// -----------------------------------------------------------------------------

#endif
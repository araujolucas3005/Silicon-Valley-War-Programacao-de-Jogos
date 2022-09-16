/**********************************************************************************
// EndGame (Código Fonte)
//
// Descrição:   Tela de encerramento do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "EndGame.h"
#include "Home.h"
#include "GameManager.h"

// ------------------------------------------------------------------------------

void EndGame::Init()
{
    if (GameManager::winner == PLAYER1) {
        player = new Sprite(GameManager::playerImages[0] + ".png");
        backg = new Sprite("Resources/tela-vencedor-p1.png");
    }
     
    else {
        player = new Sprite(GameManager::playerImages[1] + ".png");
        backg = new Sprite("Resources/tela-vencedor-p2.png");
    }
}

// ------------------------------------------------------------------------------

void EndGame::Finalize()
{
    delete backg;
    delete player;
}

// ------------------------------------------------------------------------------

void EndGame::Update()
{
    // passa ao primeiro nível com ENTER
    if (ctrlKeyEnter && window->KeyDown(VK_SPACE)) {
        ctrlKeyEnter = false;
        Engine::Next<Home>();
    }
    else if (window->KeyUp(VK_SPACE)) {
        ctrlKeyEnter = true;
    }
}

// ------------------------------------------------------------------------------

void EndGame::Draw()
{
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    player->Draw(float(window->CenterX()), float(window->CenterY()));
}

// ------------------------------------------------------------------------------
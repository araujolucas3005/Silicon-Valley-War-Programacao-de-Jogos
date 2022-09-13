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
    player = new Sprite(GameManager::playerImages[GameManager::winnerSpriteID] + ".png");

    if (GameManager::winner == PLAYER1)
        backg = new Sprite("Resources/tela-vencedor-p1.png");
    else
        backg = new Sprite("Resources/tela-vencedor-p2.png");
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
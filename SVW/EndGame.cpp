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
enum { MUSIC };

// ------------------------------------------------------------------------------

void EndGame::Init()
{
	audio = new Audio();
	audio->Add(MUSIC, "Resources/VictorySound.wav");
	audio->Play(MUSIC);

	if (GameManager::draw) {

		GameManager::draw = false;
		backg = new Sprite("Resources/draw.jpg");

	} else if (GameManager::winner == PLAYER1) {

		player = new Sprite(GameManager::playerImages[0] + "_grande.png");
		backg = new Sprite("Resources/tela-vencedor-p1.png");

	} else {

		player = new Sprite(GameManager::playerImages[1] + "_grande.png");
		backg = new Sprite("Resources/tela-vencedor-p2.png");

	}
}

// ------------------------------------------------------------------------------

void EndGame::Finalize()
{
	delete backg;
	delete player;
	delete audio;
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
	backg->Draw(float(window->CenterX()), float(window->CenterY()), GameManager::draw ? Layer::FRONT : Layer::BACK);

	if (player)
		player->Draw(float(window->CenterX()), float(window->CenterY()));
}

// ------------------------------------------------------------------------------
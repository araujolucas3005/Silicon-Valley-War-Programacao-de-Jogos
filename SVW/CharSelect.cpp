/**********************************************************************************
// Home (Código Fonte)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de abertura do jogo SVW
//
**********************************************************************************/

#include "Engine.h"
#include "CharSelect.h"
#include "Level1.h"

enum { MUSIC, SELECTION, SELECTED };

// ------------------------------------------------------------------------------

void CharSelect::Init()
{
	backg = new Sprite("Resources/selecao-personagem.png");
	border = new Sprite("Resources/Special.png");
	selectedBorder = new Sprite("Resources/Special.png");
	audio = new Audio();
	audio->Add(MUSIC, "Resources/SelectMusic.wav");
	audio->Add(SELECTION, "Resources/SelectionSound.wav");
	audio->Add(SELECTED, "Resources/SelectedSound.wav");
	audio->Play(MUSIC);
	coinTs = new TileSet("Resources/CoinSmall.png", 50.0f, 47.0f, 9, 9);
	coinAnim = new LevelAnim(coinTs, 0.05f, true);
	coinSelectedAnim = new LevelAnim(coinTs, 0.05f, true);;

	charSelectImg[0] = "Resources/apple";
	charSelectImg[1] = "Resources/android";
	charSelectImg[2] = "Resources/google";
	charSelectImg[3] = "Resources/microsoft";

	for (int i = 0; i < charsCount; i++) {
		charSelectSprite[i] = new Sprite(charSelectImg[i] + "_grande.png");
	}

	for (int i = 0; i < GameManager::maxPlayers; i++) {
		selectedIndex[i] = -1;
	}

	index = currentPlayerSelecting = 0;
}

// ------------------------------------------------------------------------------

void CharSelect::Finalize()
{
	delete backg;
	delete border;
	delete selectedBorder;
	delete coinTs;
	delete coinAnim;
	delete coinSelectedAnim;
	delete audio;

	for (int i = 0; i < charsCount; i++) {
		delete charSelectSprite[i];
	}
}

bool CharSelect::AlreadySelected(int index) {
	for (int i = 0; i < currentPlayerSelecting; i++) {
		if (index == selectedIndex[i]) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------

void CharSelect::Update()
{
	if (ctrlEnter && window->KeyDown(VK_RETURN)) {
		ctrlEnter = false;
		audio->Play(SELECTED);
		selectedIndex[currentPlayerSelecting] = index;
		GameManager::playerImages[currentPlayerSelecting++] = charSelectImg[index];

		if (currentPlayerSelecting == GameManager::maxPlayers) {
			audio->Play(SELECTED);
			Sleep(800);
			Engine::Next<Level1>();
			return;
		}

		index = index == 0 ? 1 : 0;
	}
	else if (window->KeyUp(VK_RETURN)) {
		ctrlEnter = true;
	}

	if (ctrlKeyRight && window->KeyDown(VK_RIGHT) && index + 1 < charsCount) {
		ctrlKeyRight = false;
		audio->Play(SELECTION);

		if (AlreadySelected(index + 1)) {
			if (index + 2 < charsCount) {
				index += 2;
			}
		}
		else
			index += 1;

	}
	else if (window->KeyUp(VK_RIGHT)) {
		ctrlKeyRight = true;
	}

	if (ctrlKeyLeft && window->KeyDown(VK_LEFT) && index) {
		ctrlKeyLeft = false;
		audio->Play(SELECTION);

		if (AlreadySelected(index - 1)) {
			if (index - 2 >= 0) {
				index -= 2;
			}
		}
		else
			index -= 1;
	}
	else if (window->KeyUp(VK_LEFT)) {
		
		ctrlKeyLeft = true;
	}

	/*if (ctrlKeyUp && window->KeyDown(VK_UP) && index - 3 >= 0) {
		ctrlKeyUp = false;

		if (AlreadySelected(index - 3)) {
			if (index - 6 >= 0) {
				index -= 6;
			}
		}
		else
			index -= 3;
	}
	else if (window->KeyUp(VK_UP)) {
		ctrlKeyUp = true;
	}

	if (ctrlKeyDown && window->KeyDown(VK_DOWN) && index + 3 < charsCount) {
		ctrlKeyDown = false;

		if (AlreadySelected(index + 3)) {
			if (index + 6 < charsCount) {
				index += 6;
			}
		}
		else
			index += 3;
	}
	else if (window->KeyUp(VK_DOWN)) {
		ctrlKeyDown = true;
	}*/

	coinAnim->MoveTo(208.0f + 176.0f * index, 520.0f, Layer::FRONT);
	coinAnim->Update();
	coinSelectedAnim->Update();

	for (int i = 0; i < charsCount; i++) {
		for (int j = 0; j < GameManager::maxPlayers; j++) {
			if (selectedIndex[j] == i) {
				coinSelectedAnim->MoveTo(208.0f + 176.0f * i, 520.0f, Layer::FRONT);
			}
		}
	}
}

// ------------------------------------------------------------------------------

void CharSelect::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	coinAnim->Draw();

	if (currentPlayerSelecting == 1) 
		coinSelectedAnim->Draw();

	int player1select = selectedIndex[0];

	if (player1select > -1) {
		charSelectSprite[player1select]->Draw(220.0f, 280.0f, Layer::FRONT);
	}

	if (currentPlayerSelecting == 0) {
		charSelectSprite[index]->Draw(220.0f, 280.0f, Layer::FRONT);
	}
	else {
		charSelectSprite[index]->Draw(720.0f, 280.0f, Layer::FRONT);
	}

}
	
// ------------------------------------------------------------------------------
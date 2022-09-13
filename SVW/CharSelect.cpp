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

// ------------------------------------------------------------------------------

void CharSelect::Init()
{
	backg = new Sprite("Resources/selecao-personagem.jpg");
	border = new Sprite("Resources/Special.png");
	selectedBorder = new Sprite("Resources/Special.png");

	charSelectImg[0] = "Resources/microsoft";
	charSelectImg[1] = "Resources/apple";
	charSelectImg[2] = "Resources/google";
	charSelectImg[3] = "Resources/android";

	for (int i = 0; i < charsCount; i++) {
		charSelectSprite[i] = new Sprite(charSelectImg[i] + ".png");
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
	if (currentPlayerSelecting == GameManager::maxPlayers) {
		Engine::Next<Level1>();
		return;
	}

	if (ctrlEnter && window->KeyDown(VK_RETURN)) {
		ctrlEnter = false;
		selectedIndex[currentPlayerSelecting] = index;
		GameManager::playerImages[currentPlayerSelecting++] = charSelectImg[index];

		int nextIndex = 0;
		for (int i = 0; i < charsCount; i++) {
			if (selectedIndex[i] == -1) {
				nextIndex = i;
				break;
			}
			else {
				nextIndex++;
			}
		}

		index = nextIndex;
	}
	else if (window->KeyUp(VK_RETURN)) {
		ctrlEnter = true;
	}

	if (ctrlKeyRight && window->KeyDown(VK_RIGHT) && index + 1 < charsCount) {
		ctrlKeyRight = false;

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

	if (ctrlKeyUp && window->KeyDown(VK_UP) && index - 3 >= 0) {
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
	}
}

// ------------------------------------------------------------------------------

void CharSelect::Draw()
{
	float posX = -100;
	float posY = -charsCount * 20;

	border->Draw(200, 200, Layer::FRONT);

	for (int i = 0; i < charsCount; i++) {
		for (int j = 0; j < GameManager::maxPlayers; j++) {
			if (selectedIndex[j] == i) {
				selectedBorder->Draw(window->CenterX() + posX, window->CenterY() + posY, Layer::FRONT);
			}
		}

		if (index == i) {
			border->Draw(window->CenterX() + posX, window->CenterY() + posY, Layer::FRONT);
		}

		charSelectSprite[i]->Draw(window->CenterX() + posX, window->CenterY() + posY, Layer::MIDDLE);

		if ((i + 1) % 3 == 0) {
			posY += abs(posY);
			posX = -posX;
		}
		else {
			posX += 100;
		}
	}
}

// ------------------------------------------------------------------------------
#ifndef _SVW_CHARSELECT_H_
#define _SVW_CHARSELECT_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "GameManager.h"
using std::string;

class CharSelect : public Game
{
private:
	Sprite* backg = nullptr;
	bool ctrlKeyUp = false;
	bool ctrlKeyDown = false;
	bool ctrlKeyLeft = false;
	bool ctrlKeyRight = false;
	bool ctrlEnter = false;

	int index;
	static const int charsCount = 5;
	string charSelectImg[charsCount];
	Sprite* charSelectSprite[charsCount];
	Sprite* border = nullptr;
	Sprite* selectedBorder = nullptr;
	int selectedIndex[GameManager::maxPlayers];
	int currentPlayerSelecting;

	bool AlreadySelected(int index);

public:
	void Init();                    // inicializa��o
	void Update();                  // atualiza��o
	void Draw();                    // desenho
	void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif
#ifndef _SVW_CHARSELECT_H_
#define _SVW_CHARSELECT_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "GameManager.h"
#include "TileSet.h"
#include "LevelAnim.h"
#include "Audio.h"
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
	static const int charsCount = 4;
	string charSelectImg[charsCount];
	Sprite* charSelectSprite[charsCount];
	Sprite* border = nullptr;
	Sprite* selectedBorder = nullptr;
	Audio* audio = nullptr;         // controla o audio
	int selectedIndex[GameManager::maxPlayers];
	int currentPlayerSelecting;

	TileSet* coinTs = nullptr;
	LevelAnim* coinAnim = nullptr;
	LevelAnim* coinSelectedAnim = nullptr;

	bool AlreadySelected(int index);

public:
	void Init();                    // inicialização
	void Update();                  // atualização
	void Draw();                    // desenho
	void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif
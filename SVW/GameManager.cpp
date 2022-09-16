#include "GameManager.h"

Level* GameManager::currLevel = nullptr;
bool GameManager::endGame = false;
vector<pair<float, float>> GameManager::PivotPositions = {};
int GameManager::foodLimit = 5;
int GameManager::foodNow = 0;
string GameManager::playerImages[] = { "" };
PLAYERTYPE GameManager::winner = PLAYER1;
int GameManager::winnerSpriteID = 0;
TileSet* GameManager::explosionTs = nullptr;
TileSet* GameManager::blueExplosionTs = nullptr;
TileSet* GameManager::puffTs = nullptr;

void GameManager::AddObjectToCurrLevelScene(Object* obj, uint objType) {
	if (currLevel && obj) {
		currLevel->scene->Add(obj, objType);
	}
}
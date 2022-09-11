#include "GameManager.h"

Level* GameManager::currLevel = nullptr;
bool GameManager::endGame = false;
vector<pair<float, float>> GameManager::PivotPositions = {};
int GameManager::foodLimit = 5;
int GameManager::foodNow = 0;
string GameManager::playerImages[] = { "" };
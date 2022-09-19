#ifndef _SVW_CURRLEVEL_H_
#define _SVW_CURRLEVEL_H_

#include "Level.h"
#include "Player.h"
#include "TileSet.h"
#include <string>
#include <vector>
using namespace std;

class GameManager
{
public:
	static Level* currLevel;
	static bool endGame;
	static vector<pair<float, float>> PivotPositions;
	static int foodLimit;
	static int foodNow;
	static const uint maxPlayers = 2;
	static string playerImages[maxPlayers];
	static PLAYERTYPE winner;
	static int winnerSpriteID;
	static TileSet* explosionTs;
	static TileSet* blueExplosionTs;
	static TileSet* puffTs;

	static bool draw;

	static void AddObjectToCurrLevelScene(Object* obj, uint objType);
};

#endif

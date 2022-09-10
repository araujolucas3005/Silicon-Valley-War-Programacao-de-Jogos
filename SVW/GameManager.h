#ifndef _SVW_CURRLEVEL_H_
#define _SVW_CURRLEVEL_H_

#include "Level.h"
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
};

#endif

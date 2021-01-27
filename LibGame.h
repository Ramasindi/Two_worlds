#ifndef LIBGAME_H_INCLUDED
#define LIBGAME_H_INCLUDED

#include <iostream>
#include <ctime>
#include <cstdlib>

/// #define NDEBUG
#include <cassert>

using namespace std;

namespace GameSpace
{
	struct GameCell
	{
		bool blnFood; /// Applies to the ground world.
		bool blnCoin; /// Applies to the sky world.
	};

	typedef GameCell** GameArray;

	struct GameWorld
	{
		GameArray aryWorld;
		int intRows;
		int intCols;
		int intFoodItems;
		int intCoins;

		int intPRow;
		int intPCol;
		bool blnInGroundWorld; /// Tells us in which world the player is.
	};

	enum Entity
	{
	    EMPTY_SPACE,
	    PLAYER,
	    FOOD,
	    COIN
	};

	const char ARY_SYMBOLS[] = {'.', 'P', 'o', '$'};

	GameWorld createWorld(int intRow, int intCols, int intFood, int intCoins);
	void displayWorld(GameWorld recWorld);
	void movePlayer(GameWorld& recWorld, char chOption);
	bool isEndOfGame(GameWorld recWorld);
	void destroyWorld(GameWorld& recWorld);
}





#endif // LIBGAME_H_INCLUDED

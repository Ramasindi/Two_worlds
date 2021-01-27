#include "LibGame.h"

namespace GameSpace
{
	int rangedRandom(int intLBound, int intUBound)
	{
		/// Enforce the following assertion.
		assert(intLBound < intUBound);

		int intRange = intUBound - intLBound + 1;
		return rand() % intRange + intLBound;
	}

    /// You may modify placeEntities() so that it allows for placing the player as well.
	void placePlayer(GameWorld& recWorld)
	{
		int intPRow = rangedRandom(0, recWorld.intRows - 1);
		int intPCol = rangedRandom(0, recWorld.intCols - 1);
		while(recWorld.aryWorld[intPRow][intPCol].blnFood)
		{
			recWorld.intPRow = rangedRandom(0, recWorld.intRows - 1);
			recWorld.intPCol = rangedRandom(0, recWorld.intCols - 1);
		}
		/// Simply recording the location of the player.
		/// Not necessarily placing the player in any of the worlds.
		recWorld.intPRow = intPRow;
		recWorld.intPCol = intPCol;
	}

	bool isInWorld(GameWorld recWorld, int intRow, int intCol)
	{
		if(intRow < 0)
			return false;
		if(intRow >= recWorld.intRows)
			return false;
		if(intCol < 0)
			return false;
		if(intCol >= recWorld.intCols)
			return false;

		return true;
	}

	int countEntitiesAround(GameWorld recWorld, int intRow, int intCol, Entity eEntity)
	{
		int intCount = 0;
		for(int r = intRow - 1; r < intRow + 1; r++)
		{
			for(int c = intCol - 1; c < intCol + 1; c++)
			{
				if(isInWorld(recWorld, r, c))
				{
					if(eEntity == FOOD)
					{
					    /// We are counting food items.
						if(recWorld.aryWorld[r][c].blnFood)
							intCount++;
					}
					else if(eEntity == COIN)
					{
					    /// We are counting coins.
						if(recWorld.aryWorld[r][c].blnCoin)
							intCount++;
					}
				}
			}
		}
		return intCount;
	}

	void placeEntity(GameWorld recWorld, Entity eEntity, int intNumEntities)
	{
		int intNumPlaced = 0;
		while(intNumPlaced < intNumEntities)
		{
			int intRandR = rangedRandom(0, recWorld.intRows - 1);
			int intRandC = rangedRandom(0, recWorld.intCols - 1);
			if(eEntity == FOOD)
			{
				/// We are placing an item on the ground world.
				if(!recWorld.aryWorld[intRandR][intRandC].blnFood
						&& countEntitiesAround(recWorld, intRandR, intRandC, eEntity) == 0)
				{
					/// Place the food item.
					recWorld.aryWorld[intRandR][intRandC].blnFood = true;
					intNumPlaced++;
				}
			}
			else if(eEntity == COIN)
			{
				/// We are placing an item on the sky world.
				if(!recWorld.aryWorld[intRandR][intRandC].blnCoin
						&& countEntitiesAround(recWorld, intRandR, intRandC, eEntity) == 0)
				{
					recWorld.aryWorld[intRandR][intRandC].blnCoin = true;
					intNumPlaced++;
				}
			}
		}
	}

	void movePlayer(GameWorld& recWorld, char chOption)
	{
		int intDRow = recWorld.intPRow;
		int intDCol = recWorld.intPCol;

		switch(chOption)
		{
			case 'H':
			case 'h':
				/// Just flip the truth value.
				recWorld.blnInGroundWorld = !recWorld.blnInGroundWorld;
				break;
			case 'W':
			case 'w':
				intDRow--;
				break;
			case 'S':
			case 's':
				intDRow++;
				break;
			case 'A':
			case 'a':
				intDCol--;
				break;
			case 'D':
			case 'd':
				intDCol++;
				break;
		}

		/// First validate intDRow and intDCol...
		if(isInWorld(recWorld, intDRow, intDCol))
		{
			/// Check if the player is in the same cell as a food/coin item.
			if(recWorld.blnInGroundWorld)
			{
				/// Check for food item...
				if(recWorld.aryWorld[intDRow][intDCol].blnFood)
				{
					/// Collect the food item.
					recWorld.aryWorld[intDRow][intDCol].blnFood = false;
					recWorld.intFoodItems--;
				}
			}
			else
			{
				if(recWorld.aryWorld[intDRow][intDCol].blnCoin)
				{
					/// Collect the coin.
					recWorld.aryWorld[intDRow][intDCol].blnCoin = false;
					recWorld.intCoins--;
				}
			}
			/// Update the player's location.
			recWorld.intPRow = intDRow;
			recWorld.intPCol = intDCol;
		}
	}

	bool isEndOfGame(GameWorld recWorld)
	{
		return recWorld.intFoodItems == 0 && recWorld.intCoins == 0;
	}

	GameWorld createWorld(int intRows, int intCols, int intFood, int intCoins)
	{
		assert(intRows > 0);
		assert(intCols > 0);

		GameWorld recWorld;
		/// Use member access operator to access members of the record structure.
		recWorld.intRows = intRows;
		recWorld.intCols = intCols;
		recWorld.intFoodItems = intFood;
		recWorld.intCoins = intCoins;
		recWorld.blnInGroundWorld = true; /// Player starts on the ground world.

		recWorld.aryWorld = new GameCell*[intRows];
		for(int r = 0; r < intRows; r++)
		{
			recWorld.aryWorld[r] = new GameCell[intCols];
			for(int c = 0; c < intCols; c++)
			{
			    /// Start by making both worlds empty
				recWorld.aryWorld[r][c].blnFood = false;
				recWorld.aryWorld[r][c].blnCoin = false;
			}
		}
		/// Place entities in the respective worlds.
		placeEntity(recWorld, FOOD, intFood);
		placeEntity(recWorld, COIN, intCoins);
        placePlayer(recWorld);

		return recWorld;
	}

	void displayWorld(GameWorld recworld)
	{
		for(int r = 0; r < recworld.intRows; r++)
		{
			for(int c = 0; c < recworld.intCols; c++)
			{
			    /// Regardless of which world we are in, we will always display the player.
				if(recworld.intPRow == r && recworld.intPCol == c)
					cout << PLAYER << ' ';

                /// Which entity gets displayed depends on which world we are in.
				else if(recworld.blnInGroundWorld)
				{
					if(recworld.aryWorld[r][c].blnFood)
						cout << FOOD << ' ';
					else
						cout << EMPTY_SPACE << ' ';
				}
				else
				{
					if(recworld.aryWorld[r][c].blnCoin)
						cout << COIN << ' ';
					else
						cout << EMPTY_SPACE << ' ';
				}
			}
			cout << endl;
		}
	}

	void destroyWorld(GameWorld& recWorld)
	{
		assert(recWorld.aryWorld != nullptr);

		for(int r = 0; r < recWorld.intRows; r++)
		{
			delete [] recWorld.aryWorld[r];
		}
		delete [] recWorld.aryWorld;
		recWorld.aryWorld = nullptr;
	}
}

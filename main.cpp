#include "LibGame.h"

using namespace GameSpace;

int main()
{
    srand(time(nullptr));
    bool blnContinue = true;

    GameWorld recWorld = createWorld(10, 15, 5, 5);
    do
    {
        system("cls");
        displayWorld(recWorld);

        cout << "Movement: W(w), A(a), S(s), D(d)" << endl
             << "Food items remaining: " << recWorld.intFoodItems << endl
             << "Coins remaining: " << recWorld.intCoins << endl
             << "Enter an option: ";

        char chOption = '\0';
        cin >> chOption;
        switch(chOption)
        {
        case 'W':
        case 'w':
        case 'S':
        case 's':
        case 'A':
        case 'a':
        case 'D':
        case 'd':
        case 'H':
        case 'h':
            movePlayer(recWorld, chOption);
            break;
        case 'X':
        case 'x':
            blnContinue = false;
            break;
        default:
            cerr << "Wrong input!!!" << endl;
            break;
        }

        /// End-game test.
        if(isEndOfGame(recWorld))
        {
            cout << "You win :D !!!" << endl;
            blnContinue = false;
        }
    }while(blnContinue);

    destroyWorld(recWorld);
    return 0;
}

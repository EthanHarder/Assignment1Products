
#include <iostream>
using namespace std;

class Location; //prototypes
class KeyLocation;
class LootLocation;
class PoisonLocation;
void ChangeLocations(Location*);
void GameOver();

//player information.
bool keepPlaying= true;
bool hasKey=false;
Location* location;
int score=200;
int lives=2;

Location* area[10];

class Location
{
public:
    Location* north = nullptr;
    Location* south = nullptr;
    Location* west = nullptr;
    Location* east = nullptr;
    void virtual EnterLocation() {}
    virtual ~Location() {}

};

class KeyLocation : public Location
{


    void EnterLocation() override
    {
        if (hasKey)
        {
            std::cout << "Maybe there was a key here, once\n";
            return;
        }
        char input;
        std::cout << "You've wandered upon a key! shall you pick it up? 'y' 'n' \n";
        std::cin >> input;
        if (input == 'y' || input == 'Y')
        {
            std::cout << "You pick up the key. You also gain 50 points!\n";
            score += 50;
            hasKey = true;
        }
        else if (input == 'n' || input == 'N')
        {
            std::cout << "You leave the key alone.\n";
        }
        else
        {
            std::cout << "Unrecognized input: " << input << "\n\n";
            EnterLocation();
        }
    }
};

class LootLocation : public Location
{

    void EnterLocation() override
    {
        if (!hasKey)
        {
            std::cout << "You've wandered upon a treasure chest! but it is locked...";
            return;
        }

        char input;
        std::cout << "You've wandered upon a treasure chest! shall you use your key? 'y' 'n' \n";
        std::cin >> input;
        if (input == 'y' || input == 'Y')
        {
            std::cout << "You open up the chest. congratulations! You win!!!\n";
            GameOver();
        }
        else if (input == 'n' || input == 'N')
        {
            std::cout << "You leave the chest alone.\n";
        }
        else
        {
            std::cout << "Unrecognized input: " << input << "\n\n";
            EnterLocation();
        }

    }
};

class PoisonLocation : public Location
{

    void EnterLocation() override
    {
        std::cout << "You accidentally step into a vat of poison!!!\n-1 Health";
        lives -= 1;
        if (lives == 0)
            return;
        score += 10;//you arent supposed to lose score for touching poison, so I add it back artifically so it doesn't decrease.
        ChangeLocations(west); //kind of cheating, but you didnt request modular parts sooooooo....hardcoding here we goooo
        std::cout << "You scramble back down the hallway you were before.\n";

    }
};

void AssignPointers()
{
    for (int i = 0; i < 10; ++i) { area[i] = nullptr; }

    area[0] = new Location();
    area[1] = new Location();
    area[2] = new Location();
    area[3] = new Location();
    area[4] = new Location();
    area[5] = new LootLocation();
    area[6] = new KeyLocation();
    area[7] = new Location();
    area[8] = new PoisonLocation();
    area[9] = new PoisonLocation();

    //std::cout << "Starting to allocate pointers";
    area[0]->north = area[7];
    area[0]->east = area[1];
    area[0]->south = nullptr;
    area[1]->north = area[2];
    area[1]->west = area[0];
    area[2]->north = area[3];
    area[2]->east = area[8];
    area[2]->south = area[1];
    area[3]->east = area[9];
    area[3]->south = area[2];
    area[3]->west = area[4];
    area[4]->east = area[3];
    area[4]->south = area[6];
    area[4]->west = area[5];
    area[5]->east = area[4];
    area[6]->north = area[4];
    area[6]->west = area[7];
    area[7]->east = area[6];
    area[7]->south = area[0];
    area[8]->west = area[2];
    area[9]->west = area[3];
    //std::cout << "finished making connections";
}

//reset the player values
void SetValues(Location* start)
{
    hasKey = false;
    
    score = 200;
    lives = 2;
    
    location = start;
    

    
    
}

void ChangeLocations(Location* newLoc)
{
    if (newLoc == nullptr)
    {
        score -= 5;
        std::cout << "You bump into a wall.\n";
    }
    else
    {
        score -= 10;
        std::cout << "You walk further. \n";
        location = newLoc;
        location->EnterLocation();
    }

}

void PlayerMenu()
{
    std::cout << "Current Score: " << score;
    std::cout << "     Lives: " << lives;
    std::cout << "\n You can see: \n";
    
    if (location->north != nullptr)
        std::cout << "A path to the north, 'n'\n";
    if (location->east != nullptr)
        std::cout << "A path to the east, 'e'\n";
    if (location->south != nullptr)
        std::cout << "A path to the south, 's'\n";
    if (location->west != nullptr)
        std::cout << "A path to the west, 'w'\n"; 

    std::cout << "What direction would you like to go?\n";
    char choice;
    std::cin >> choice;
    switch (choice)
    {
    case 'n':
    case 'N':
        ChangeLocations(location->north);
        break;
    case 'e':
    case 'E':
        ChangeLocations(location->east);
        break;
    case 's':
    case 'S':
        ChangeLocations(location->south);
        break;
    case 'w':
    case 'W':
        ChangeLocations(location->west);
        break;
    case 'x':
    case 'X':
        keepPlaying = false;
        break;
    default:
        std::cout << "Invalid input\n";
        PlayerMenu();
        break;

    }
}

void GameOver()
{
    char choice;
    std::cout << "\n\n Game Over. Well played. Would you like to play again? 'y' 'n'\n";
    std::cin >> choice;
    switch (choice)
    {
        case 'y':
        case 'Y':
            SetValues(area[0]);
            break;
        case 'n':
        case 'N':
            keepPlaying = false;
            break;
        default:
            std::cout << "Invalid input\n";
            GameOver();
            break;

    }
}

int main()
{
    std::cout<<"Let us play a game!\n";
    AssignPointers();
    SetValues(area[0]);

    do
    {
        PlayerMenu();
        if (lives == 0)
            GameOver();


    } while (keepPlaying);
    
}
#include <iostream>
#include <vector>
#include "player.cpp"
#include "message.cpp"

using namespace std;

class Game
{
private:
    int totalPlayers;
    double startingBalance;
    vector<Player> players;
    StyleMessage styleMessage;

public:
    // Total Players
    void setTotalPlayers()
    {
        // Get number of players
        int numPlayers;
        bool validInput = false;
        while (!validInput)
        {
            cout << "Enter number of players: ";
            cin >> numPlayers;

            // Check if input is valid
            if (cin.fail())
            {
                cin.clear();                                         // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input! Please enter a number." << endl;
            }
            else if (numPlayers < 2 || numPlayers > 4)
            {
                cout << "Number of players should be 2-4!" << endl;
            }
            else
            {
                validInput = true;
            }
        }
        this->totalPlayers = numPlayers;
        cout << "======> Total players: " << totalPlayers << endl;
    };

    int getTotalPlayers()
    {
        return totalPlayers;
    };

    // Starting Balance
    void setStartingBalance()
    {
        // Set starting balance for all players
        double startingBalance;
        bool validInput = false;
        while (!validInput)
        {
            cout << "Enter starting balance for each player: ";
            cin >> startingBalance;

            // Check if input is valid
            if (cin.fail())
            {
                cin.clear();                                         // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input! Please enter a number." << endl;
            }
            else if (startingBalance < 100 || startingBalance > 1000)
            {
                cout << "Starting balance should be between 100 and 1000!" << endl;
            }
            else
            {
                validInput = true;
            }
        }
        this->startingBalance = startingBalance;
    };

    double getStartingBalance()
    {
        return startingBalance;
    };

    // Set Players
    void setPlayers()
    {
        // Create players array
        for (int i = 0; i < totalPlayers; i++)
        {
            Player player;
            this->players.push_back(player);

            // Set starting balance for each player
            players[i].setBalance(startingBalance);
        }
    };

    // Get Players
    vector<Player> getPlayers()
    {
        return this->players;
    };

    // Print players balance
    void getAllPlayersBalance()
    {
        styleMessage.headingMsg("All Players Balance");
        for (int i = 0; i < totalPlayers; i++)
        {
            cout << "Player " << i + 1 << " balance: " << this->players[i].getBalance() << endl;
        }
        styleMessage.footerMsg("All Players Balance");
    };
};

class StartGame : public Game
{
public:
    void startGame()
    {
        // Object instance
        Message message;
        Game game;

        // Display heading message
        message.headingMsg();

        // Input number of players and starting balance
        game.setTotalPlayers();
        game.setStartingBalance();

        // Create players array
        game.setPlayers();

        // Get players balance
        game.getAllPlayersBalance();

        // Start the game
        cout << "Game started!" << endl;
    }
};
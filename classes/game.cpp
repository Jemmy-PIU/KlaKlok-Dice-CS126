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

    // Player turns
    void playerTurns()
    {
        for (int i = 0; i < this->totalPlayers; i++)
        {
            Player &currentPlayer = this->players[i];

            // Check if player is betting
            cout << endl
                 << "=====> Player " << i + 1 << "'s turn <=====" << endl;
            currentPlayer.setIsTurn(true);
            while (currentPlayer.getIsTurn() == true)
            {
                // Get input from 1-6
                int input;
                bool validInput = false;
                while (!validInput)
                {
                    cout << "Enter a number from 1 to 6: ";
                    cin >> input;
                    // Check if input is valid
                    if (cin.fail() || input < 1 || input > 6)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number from 1 to 6." << endl;
                    }

                    // Check if player already guessed the number
                    else if (currentPlayer.inputExists(input))
                    {
                        cout << "You already guessed this number! Please enter a different number." << endl;
                    }
                    else
                    {
                        validInput = true;
                    }
                }
                currentPlayer.addInputValues(input);

                // Get bet amount
                double betAmount;
                validInput = false;
                while (!validInput)
                {
                    cout << "Enter bet amount: ";
                    cin >> betAmount;
                    // Check if input is valid
                    if (cin.fail() || betAmount <= 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a valid bet amount." << endl;
                    }
                    else if (betAmount > currentPlayer.getBalance())
                    {
                        cout << "Bet amount should be less than or equal to your balance!" << endl;
                    }
                    else if (betAmount > currentPlayer.getCanBetAmount())
                    {
                        cout << "Can not bet! You only have " << currentPlayer.getCanBetAmount() << " left!" << endl;
                    }
                    else
                    {
                        validInput = true;
                    }
                }
                currentPlayer.addBetAmounts(betAmount);

                if (currentPlayer.getCanBetAmount() > 0 && currentPlayer.getInputValues().size() < 6)
                {
                    // Continue betting
                    char continueBetting;
                    validInput = false;
                    while (!validInput)
                    {
                        cout << "Continue betting? (y/n): ";
                        cin >> continueBetting;
                        // Check if input is valid
                        if (cin.fail() || (continueBetting != 'y' && continueBetting != 'n'))
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input! Please enter y or n." << endl;
                        }
                        else
                        {
                            validInput = true;
                        }
                    }

                    // Set isBetting
                    bool isTurn = (continueBetting == 'y') ? true : false;
                    currentPlayer.setIsTurn(isTurn);
                }
                else
                {
                    cout << endl;
                    currentPlayer.setIsTurn(false);
                }
            }
        }
    }
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

        // Player turns
        game.playerTurns();

        // Display player guesses
        for (int i = 0; i < game.getTotalPlayers(); i++)
        {
            Player currentPlayer = game.getPlayers()[i];
            cout << "Player " << i + 1 << " guessed: " << endl;
            for (int j = 0; j < currentPlayer.getInputValues().size(); j++)
            {
                cout << "( " << currentPlayer.getInputValues()[j] << " - $" << currentPlayer.getBetAmounts()[j] << " )" << endl;
            }
            cout << endl;
        }
    }
};
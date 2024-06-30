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
            cout << "Player " << i + 1 << " balance: $" << this->players[i].getBalance() << endl;
        }
        styleMessage.footerMsg("All Players Balance");
    };

    // Check if a player exceeds 10 times the starting balance
    bool isPlayerExceedsLimit()
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            if (players[i].getBalance() > (startingBalance * 10))
            {
                return true;
            }
        }
        return false;
    };

    // Check if only one player is left has balance
    bool isOnePlayerLeft()
    {
        int count = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (players[i].getBalance() > 0)
            {
                count++;
            }
        }
        return count == 1;
    };

    // Check if no player has balance
    bool isNoPlayerLeft()
    {
        int count = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (players[i].getBalance() <= 0)
            {
                count++;
            }
        }
        return count == totalPlayers;
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

    // Randomize 3 dice values from 1-6
    vector<int> randomizeDiceValues()
    {
        vector<int> diceValues;

        // Seed the random number generator with the current time
        srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 0; i < 3; i++)
        {
            int randomVal = (rand() % 6) + 1;
            diceValues.push_back(randomVal);
        }
        return diceValues;
    };

    // Check if player guessed the number and get the bet amount, then add balance if correct, deduct balance if wrong
    void checkPlayerGuess(const vector<int> &diceValues)
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            Player &currentPlayer = players[i];
            vector<int> correctGuesses;

            // Check for wrong guesses and deduct balance
            for (int j = 0; j < currentPlayer.getInputValues().size(); j++)
            {
                if (find(diceValues.begin(), diceValues.end(), currentPlayer.getInputValues()[j]) == diceValues.end())
                {
                    // cout << "Player " << i + 1 << " guessed the number " << diceValues[j] << " wrongly!" << endl;
                    currentPlayer.deductBalance(currentPlayer.getBetAmounts()[j]);
                }
                else
                {
                    // Add the correct guess to the player's correct guesses
                    correctGuesses.push_back(currentPlayer.getInputValues()[j]);
                }
            }

            // Check for correct guesses and add balance accordingly with the dice result
            for (int j = 0; j < correctGuesses.size(); j++)
            {
                // Count the number of correct guesses
                int count = std::count(diceValues.begin(), diceValues.end(), correctGuesses[j]);
                string abbre = "";

                switch (count)
                {
                case 1:
                    abbre = "once";
                    break;
                case 2:
                    abbre = "twice";
                    break;
                case 3:
                    abbre = "thrice";
                    break;
                default:
                    abbre = "";
                    break;
                }

                double amount = currentPlayer.getBetAmounts()[j] * count;
                currentPlayer.addBalance(amount);
                cout << "Player " << i + 1 << " guessed the number " << correctGuesses[j] << " correctly " << abbre << " and earned " << amount << endl;
            }
        }
    }

    // Reset player input values and bet amounts
    void resetPlayerValues()
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            players[i].clearInputValues();
            players[i].clearBetAmounts();
        }
    };
};

class StartGame : public Game
{
public:
    void startGame()
    {
        // Object instance
        Message message;
        StyleMessage styleMessage;
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

        // Game loop, if a player exceeds 10 times the starting balance or only one player is left, end the game
        while (!game.isPlayerExceedsLimit() && !game.isOnePlayerLeft() && !game.isNoPlayerLeft())
        {
            // Player turns
            game.playerTurns();

            // Randomize dice values
            vector<int> diceValues = game.randomizeDiceValues();

            // Display dice values
            styleMessage.randomDiceMsg(diceValues);

            // Check if player guessed the number and get the bet amount, then add balance if correct, deduct balance if wrong
            game.checkPlayerGuess(diceValues);

            // Get players balance
            game.getAllPlayersBalance();

            // Reset player input values and bet amounts
            game.resetPlayerValues();
        }
        cout << endl;

        // Check win condition
        if (game.isPlayerExceedsLimit())
        {
            // Display winner
            cout << "================WINNER================" << endl;
            for (int i = 0; i < game.getTotalPlayers(); i++)
            {
                double playerBal = game.getPlayers()[i].getBalance();
                if (game.getPlayers()[i].getBalance() > (game.getStartingBalance() * 10))
                {
                    cout << "Player " << i + 1 << " is the winner with $" << playerBal
                         << endl;
                }
            }
            cout << "======================================" << endl
                 << endl;
        }
        else if (game.isOnePlayerLeft())
        {
            // Display winner
            cout << "================WINNER================" << endl;
            for (int i = 0; i < game.getTotalPlayers(); i++)
            {
                double playerBal = game.getPlayers()[i].getBalance();
                if (game.getPlayers()[i].getBalance() > 0)
                {
                    cout << "Player " << i + 1 << " is the winner with $" << playerBal << endl;
                }
            }
            cout << "======================================" << endl
                 << endl;
        }
        else if (game.isNoPlayerLeft())
        {
            cout << "================EVERYONE LOSES================" << endl;
            cout << "All players ran out of money!" << endl;

            cout << "==============================================" << endl
                 << endl;
        }
        else
        {
            cout << "Game ended!" << endl;
        }

        // Display exit message
        message.exitMsg();
    }
};
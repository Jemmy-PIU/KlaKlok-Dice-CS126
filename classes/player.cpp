#include <iostream>
#include <vector>
using namespace std;

class Player
{
private:
    double balance;
    bool isTurn;
    bool isWinner;
    vector<int> inputValues;
    vector<double> betAmounts;

public:
    Player()
    {
        balance = 0;
        isWinner = false;
        isTurn = false;
    }

    double getBalance()
    {
        return balance;
    }

    void setBalance(double newBalance)
    {
        balance = newBalance;
    }

    void addBalance(double amount)
    {
        balance += amount;
    }

    void deductBalance(double amount)
    {
        balance -= amount;
    }

    bool getIsWinner()
    {
        return isWinner;
    }

    void setIsWinner(bool newIsWinner)
    {
        isWinner = newIsWinner;
    }

    bool getIsTurn()
    {
        return isTurn;
    }

    void setIsTurn(bool newIsTurn)
    {
        isTurn = newIsTurn;
    }

    // Get input values
    vector<int> getInputValues()
    {
        return inputValues;
    }

    // add input values
    void addInputValues(int value)
    {
        inputValues.push_back(value);
    }

    // Input exists
    bool inputExists(int value)
    {
        for (int i = 0; i < inputValues.size(); i++)
        {
            if (inputValues[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    // Clear input values
    void clearInputValues()
    {
        inputValues.clear();
    }

    // Get bet amounts
    vector<double> getBetAmounts()
    {
        return betAmounts;
    }

    // Add bet amounts
    void addBetAmounts(double amount)
    {
        betAmounts.push_back(amount);
    }

    // Clear bet amounts
    void clearBetAmounts()
    {
        betAmounts.clear();
    }

    // Get total bet amount
    double getTotalBetAmount()
    {
        double total = 0;
        for (int i = 0; i < betAmounts.size(); i++)
        {
            total += betAmounts[i];
        }
        return total;
    }

    // Get can bet amount
    double getCanBetAmount()
    {
        double totalBetAmount = getTotalBetAmount();
        return balance - totalBetAmount;
    }
};
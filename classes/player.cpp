#include <iostream>
using namespace std;

class Player {
    private:
        double balance;
        bool isWinner;

    public:
        Player() {
            balance = 0;
            isWinner = false;
        }

        double getBalance() {
            return balance;
        }

        void setBalance(double newBalance) {
            balance = newBalance;
        }

        void addBalance(double amount) {
            balance += amount;
        }

        void deductBalance(double amount) {
            balance -= amount;
        }

        bool getIsWinner() {
            return isWinner;
        }

        void setIsWinner(bool newIsWinner) {
            isWinner = newIsWinner;
        }
};
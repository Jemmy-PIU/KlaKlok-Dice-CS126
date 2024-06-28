#include <iostream>

using namespace std;

class Message
{
public:
    void headingMsg()
    {
        cout << "============================================" << endl;
        cout << "Welcome to KlaKlok Dice V1 by Team 1 - CS126" << endl;
        cout << "============================================" << endl;
    }

    void exitMsg()
    {
        cout << "============================================" << endl;
        cout << "Thank you for playing KlaKlok Dice V1!" << endl;
        cout << "============================================" << endl;
    }
};

class StyleMessage : public Message
{
public:
    void headingMsg(string msg)
    {
        cout << endl
             << "====[ " << msg << " ]====" << endl;
    }

    void footerMsg(string msg)
    {
        int msgLength = msg.length();
        string msgFooter = "======" + string(msgLength, '=') + "======";
        cout
            << msgFooter << endl
            << endl;
    }
};

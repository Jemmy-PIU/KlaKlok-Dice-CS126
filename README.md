# <span style="color:blue">KlaKlok Dice Game V1 (C++ Terminal Version)</span>

This C++ project is created for educational purpose at **[Paragon International University](https://paragoniu.edu.kh/)** under the course **CS 126 Section 1 - Principles of Programming II (June 2024)**!



> [!IMPORTANT]
>
> **Lecturer:** Prof. Tin Hok
>
> **Group 1** **Members:**
>
> - Jemmy Seang
> - Manil Hor
> - Vitou Muy



## <span style="color:#d36300">Getting Started</span>

1. Clone the git repository to your local system by downloading the source code or by running the following commands:`git clone https://github.com/Jemmy-PIU/KlaKlok-Dice-CS126`

2. Using the terminal, navigate into the directory of the game folder
   - For example, on my laptop, the ***klaklok-dice-v1*** folder is located in **Desktop**, so I will run the follwing commands to navigate into the folder: `cd Desktop/klaklok-dice-v1`

3. Compile *(If haven't yet)* the main.cpp and run the executable file using the terminal

   - Inside the game folder, `g++ main.cpp -o main`

   - Then, run the created executable file:
     - On Window: `main.exe`
     - On MacOS: `./main`

4. The game is started!



## <span style="color:#d36300">Playing the Game</span>

1. Enter the number of players from **2 to 4**
1. Enter the initial amount of money from **100 to 1000** (This applies to all players)
3. The guessing phase started, and everyone takes turn into guessing and betting (Everyone must bet at least once)
   - The first player input **a** preferred number from **1 to 6**
   - Then, the player input the amount to bet (<span style="color:red">***the amount must be bigger than 0 and smaller than the player's balance***</span>)
   - After that, the player can choose to continue to bet by entering `y` or skip to the next player using `n` (**Note**: if the player has no balance left for betting, the game will automatically skip to the next player)

4. Once every player finished betting, the system will randomly roll 3 dices
5. The player that bet correctly will earn money accordingly to the bet amount (If the guessed number appears on the dices more than once, the player will earn **X times** the bet amount amount)
6. The game continues until it meets the following criteria:
   - All players has no balance left: `The game ended and no one wins`
   - One player has remaining balance, and the others ran out of balance: `The one player wins the game`
   - One or more players' balance reach 10x amount of initial balance: `Those players win the game`


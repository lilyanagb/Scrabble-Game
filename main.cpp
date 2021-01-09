#include <iostream>
#include "Scrabble.hpp"
using namespace std;

int main() {
    displayInstructions();
    cout << endl;
    cout << "Let's start! Press Enter to open the menu.";
    cin.get();
    clearScreen();
    int numberForOption;
    int letters = DEFAULT_LETTERS, rounds = DEFAULT_ROUNDS;

    do {
        menu();
        cin >> numberForOption;
        enteredOptionMenu(numberForOption, letters, rounds);
    } while (numberForOption != 4);

    return 0;
}

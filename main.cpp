/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Lilyana Georgieva Belcheva
* @idnumber 62599
* @compiler VC
*
* <main.cpp file>
*
*/

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

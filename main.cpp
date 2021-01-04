#include <iostream>
#include <fstream>
using namespace std;

int length(char arr[]) {
    int i = 0;
    for (; arr[i] != '\0'; ++i) {}
    return i;
}

void clearScreen() {
    for (int i = 0; i < 40; i++) {
        cout << endl;
    }
}

void pressEnter() {
    cout << endl;
    cout << "Let's start! Press Enter to open the menu.";
    cin.get();
    clearScreen();
}

void displayInstructions() {
    char myInstructions[150];
    ifstream readToFile;
    readToFile.open("instructions.txt");
    if (!readToFile.is_open()) {
        cout << "cannot be opened";
        return;
    }

    while (readToFile.good()) {
        readToFile.getline(myInstructions, 150);
        cout << myInstructions << endl;
    }
    readToFile.close();
}

void menu() {
    cout << "To select a menu option, type the corresponding number." << endl;
    cout << "Menu:" << endl;
    cout << "1 -> Start a game" << endl;
    cout << "2 -> Settings" << endl;
    cout << "3 -> Add a new word" << endl;
    cout << "4 -> Exit" << endl;
}

void enteredOptionMenu(int numberForOption, int &letters, int &rounds) {
    int numberForSettings;

    if (numberForOption == 1) {

    }
    if (numberForOption == 2) {
        cout << "1 -> Change the number of submitted letters" << endl;
        cout << "2 -> Change the number of rounds" << endl;
        cin >> numberForSettings;

        if (numberForSettings == 1) {
            cout << "Enter the number of letters: ";
            cin >> letters;
        } else if (numberForSettings == 2) {
            cout <<"Enter the number of rounds: ";
            cin >> rounds;
        }
    }
    if (numberForOption == 3) {
        char newWord[100];
        ofstream writeToFile;
        writeToFile.open("dictionary.txt", ios_base::app);
        cout << "Enter a new word: ";
        cin.get();
        cin.getline(newWord, 100);
        writeToFile << endl << newWord;
        writeToFile.close();
    }
}
int main() {
    displayInstructions();
    pressEnter();
    int numberForOption, letters = 10, rounds = 10;
    do {
        menu();
        cin >> numberForOption;
        enteredOptionMenu(numberForOption, letters, rounds);
    } while (numberForOption != 4);

    return 0;
}

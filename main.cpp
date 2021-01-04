#include <iostream>
#include <fstream>
using namespace std;

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

int main() {
    //displayInstructions();
    menu();
    return 0;
}

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

int main() {
    displayInstructions();
    return 0;
}

#include <iostream>
#include <fstream>
#include <ctime>
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

bool checkForVowel(int number, char randomLetters[]){
    for(int i=0;i<number;i++){
        if(randomLetters[i]=='a' || randomLetters[i]=='e'){
            return true;
        }else if(randomLetters[i]=='i' || randomLetters[i]=='o'){
            return true;
        }else if(randomLetters[i]=='u'){
            return true;
        }
    }
    return false;
}

int points(char userWord[]) {
    int lengthWord = length(userWord);
    int points = 0;
    for (int i = 0; i < lengthWord; i++) {
        points++;
    }
    return points;
}

void randomGet(int number, char randomLetters[]) {
    char alphabets[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                          't', 'u', 'v', 'w', 'x', 'y', 'z'};

    srand(time(nullptr));

    int i = 0;
    while (i < number) {
        int temp = rand() % 26;
        randomLetters[i] = alphabets[temp];
        i++;
    }
    randomLetters[i]='\0';
}

void getRandomLetters(int number,char array[]){
    randomGet(number,array);
    while(!checkForVowel(number,array)) {
        randomGet(number, array);
    }
}

void sortWord(char arr[]) {
    int n = length(arr);
    char swapElement;
    for (int i = 0; n > i; i++) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j - 1] > arr[j])
            {
                swapElement = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = swapElement;
            }
        }
    }
}

bool findWord(char userWord[]) {
    char myDictionary[101];
    ifstream readToFile;
    readToFile.open("dictionary.txt");
    if (!readToFile.is_open()) {
        cout << "cannot be opened";
        return false;
    }

    int lengthUserWord = length(userWord);
    int lengthDictionaryWord;
    int similarLetters = 0;
    while (readToFile.good()) {
        readToFile >> myDictionary;
        lengthDictionaryWord = length(myDictionary);
        if (lengthUserWord == lengthDictionaryWord) {
            for (int i = 0; i < lengthUserWord; i++) {
                if (userWord[i] == myDictionary[i]) {
                    similarLetters++;
                } else {
                    break;
                }
            }
        }
        if (similarLetters == lengthUserWord) {
            readToFile.close();
            return true;
        }
    }
    readToFile.close();
    return false;
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

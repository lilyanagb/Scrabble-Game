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
* <Scrabble.cpp file>
*
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include "Scrabble.hpp"

using namespace std;

int length(char arr[]) {
    int i = 0;
    for (; arr[i] != '\0'; ++i) {}
    return i;
}

void clearScreen() {
    for (int i = 0; i < NEWLINE_COUNT; i++) {
        cout << endl;
    }
}

void pressEnter() {
    cout << ">> Press Enter to continue";
    cin.get();
    clearScreen();
}

void displayInstructions() {
    char myInstructions[MAX_INSTRUCTION_LEN];
    ifstream readToFile;
    readToFile.open("instructions.txt");

    if (!readToFile.is_open()) {
        cout << "cannot be opened";
        return;
    }

    while (readToFile.good()) {
        readToFile.getline(myInstructions, MAX_INSTRUCTION_LEN);
        cout << myInstructions << endl;
    }
    readToFile.close();
}

void menu() {
    cout << endl;
    cout << ">>To select a menu option, type the corresponding number<<" << endl;
    cout << "Menu:" << endl;
    cout << "1 -> Start a game" << endl;
    cout << "2 -> Settings" << endl;
    cout << "3 -> Add a new word" << endl;
    cout << "4 -> Exit" << endl;
}

bool checkForVowel(int number, char randomLetters[]) {
    for (int i = 0; i < number; i++) {
        if (randomLetters[i] == 'a' || randomLetters[i] == 'e') {
            return true;
        } else if (randomLetters[i] == 'i' || randomLetters[i] == 'o') {
            return true;
        } else if (randomLetters[i] == 'u') {
            return true;
        }
    }
    return false;
}

void copyArray(char arr[], char newArr[]) {
    int lengthArr = length(arr);
    for (int i = 0; i < lengthArr; i++) {
        newArr[i] = arr[i];
    }
    newArr[lengthArr] = '\0';
}

int points(char userWord[]) {
    int lengthWord = length(userWord);
    int points = 0;

    if (userWord[0] == '0') {
        return 0;
    }

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
    randomLetters[i] = '\0';
}

//the random get function is called until there is at least one vowel in the random letters
void getRandomLetters(int number, char array[]) {
    randomGet(number, array);
    while (!checkForVowel(number, array)) {
        randomGet(number, array);
    }
}

void sortWord(char arr[]) {
    int n = length(arr);
    char swapElement;

    for (int i = 0; n > i; i++) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j - 1] > arr[j]) {
                swapElement = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = swapElement;
            }
        }
    }
}

bool findWord(char userWord[]) {
    char myDictionary[MAX_LINE_LENGTH + 1];
    ifstream readToFile;
    readToFile.open("dictionary.txt");

    if (!readToFile.is_open()) {
        cout << "cannot be opened";
        return false;
    }

    int lengthUserWord = length(userWord);
    int lengthDictionaryWord;
    int sameLetters = 0;

    while (readToFile.good()) {
        readToFile >> myDictionary;
        lengthDictionaryWord = length(myDictionary);

        if (lengthUserWord == lengthDictionaryWord) {
            for (int i = 0; i < lengthUserWord; i++) {
                if (userWord[i] == myDictionary[i]) {
                    sameLetters++;
                } else {
                    sameLetters = 0;
                    break;
                }
            }
        }

        if (sameLetters == lengthUserWord) {
            readToFile.close();
            return true;
        }
    }
    readToFile.close();
    return false;
}

bool validateUserWord(char arrFromUser[], char lettersFromComputer[]) {
    char tempUser[MAX_LINE_LENGTH + 1];
    char tempComputer[MAX_LINE_LENGTH + 1];
    int computerLength = length(lettersFromComputer);
    int userLength = length(arrFromUser);

    if (userLength > computerLength) {
        return false;
    }

    copyArray(arrFromUser, tempUser);
    copyArray(lettersFromComputer, tempComputer);
    sortWord(tempUser);
    sortWord(tempComputer);

    //check whether the user's word is composed of the random letters
    for (int i = 0; i < computerLength; i++) {
        for (int j = 0; j < userLength; j++) {
            if (tempUser[j] == tempComputer[i]) {
                tempUser[j] = '1';
                break;
            }
        }
    }

    for (int i = 0; i < userLength; i++) {
        if (tempUser[i] != '1') {
            return false;
        }
    }
    return true;
}

bool correctNewWord(char newWord[]) {
    char dictionary[MAX_LINE_LENGTH + 1];
    ifstream readToFile;
    readToFile.open("dictionary1.txt");

    if (!readToFile.is_open()) {
        cout << "cannot be opened";
        return false;
    }

    int lengthNewWord = length(newWord);

    while (readToFile.good()) {
        readToFile.getline(dictionary, MAX_LINE_LENGTH);
        int counter = 0;

        for (int i = 0; i < lengthNewWord; i++) {
            if (newWord[i] == dictionary[i]) {
                counter++;
            }
        }

        if (counter == lengthNewWord) {
            readToFile.close();
            return true;
        }
    }
    readToFile.close();
    return false;
}

//3(MAX_TRIES) options per round to request new letters
void displayChangedLetters(int &counter, int letters, char randomLetters[]) {
    counter++;
    cout << endl;
    cout << ">> " << MAX_TRIES - counter << " letter changes left" << endl;
    cout << ">> New available letters: ";
    getRandomLetters(letters, randomLetters);
    cout << randomLetters << endl;
}

int playGame(int letters, int rounds) {
    char randomLetters[MAX_LINE_LENGTH + 1];
    char userWord[MAX_LINE_LENGTH + 1];
    int sumOfPoints = 0;
    clearScreen();

    for (int i = 1; i <= rounds; i++) {
        int counter = 0;
        int roundPoints;

        cout << "<< Round " << i << "." << "Available letters: ";
        getRandomLetters(letters, randomLetters);

        cout << randomLetters << endl;
        cout << ">> Try with word or type 0 for new letters: ";
        cin >> userWord;

        while (!(validateUserWord(userWord, randomLetters) && findWord(userWord)) || userWord[0] == '0') {

            if (userWord[0] == '0') {
                if (counter < MAX_TRIES) {
                    displayChangedLetters(counter, letters, randomLetters);
                } else {
                    break;
                }
            }
            cout << endl;
            cout << ">> Try again with another word or type 0 for new letters: ";
            cin >> userWord;
        }
        roundPoints = points(userWord);
        sumOfPoints += roundPoints;

        cin.get();
        clearScreen();
        cout << "<< In the previous round you received: " << points(userWord) << " points" << endl;
        cout << "<< Your points so far are: " << sumOfPoints << endl;
        cout << endl;
    }
    return sumOfPoints;
}

void enteredOptionMenu(int numberForOption, int &letters, int &rounds) {
    int numberForSettings;

    if (numberForOption == 1) {
        int points;
        points = playGame(letters, rounds);
        cout << endl;
        cout << ">> Well done! Your total points are: " << points << endl;
        letters = DEFAULT_LETTERS;
        rounds = DEFAULT_ROUNDS;
        pressEnter();
    }
    if (numberForOption == 2) {
        cout << "1 -> Change the number of submitted letters" << endl;
        cout << "2 -> Change the number of rounds" << endl;
        cout << "3 -> Return to the menu" << endl;
        cin >> numberForSettings;

        if (numberForSettings == 1) {
            cout << ">> Enter the number of letters: ";
            cin >> letters;
        } else if (numberForSettings == 2) {
            cout << ">> Enter the number of rounds: ";
            cin >> rounds;
        } else if (numberForSettings == 3) {
            clearScreen();
            return;
        }
    }
    if (numberForOption == 3) {
        char newWord[MAX_LINE_LENGTH + 1];
        ofstream writeToFile;
        writeToFile.open("dictionary.txt", ios_base::app);
        cout << ">> Enter a new word or type 0 to return to the menu: ";
        cin.get();
        cin.getline(newWord, MAX_LINE_LENGTH);

        if (newWord[0] == '0') {
            clearScreen();
            return;
        }
        cout << endl;

        if (correctNewWord(newWord)) {
            writeToFile << endl << newWord;
            cout << ">> Your word is added successfully" << endl;
        } else {
            cout << ">> The word doesn't exist" << endl;
        }
        writeToFile.close();
    }
}

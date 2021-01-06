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

void copyArray(char arr[],char newArr[]){
    int lengthArr=length(arr);
    for(int i=0;i<lengthArr ;i++){
        newArr[i]=arr[i];
    }
    newArr[lengthArr]='\0';
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
                    similarLetters=0;
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

bool validateUserWord(char arrFromUser[], char lettersFromComputer[]) {
    char tempUser[101];
    char tempComputer[101];
    int computerLength= length(lettersFromComputer);
    int userLength= length(arrFromUser);

    if(userLength>computerLength){
        return false;
    }

    copyArray(arrFromUser,tempUser);
    copyArray(lettersFromComputer,tempComputer);
    sortWord(tempUser);
    sortWord(tempComputer);

    for(int i=0;i<computerLength;i++) {
        for (int j = 0; j < userLength; j++) {
            if (tempUser[j] == tempComputer[i]) {
                tempUser[j] = '1';
                break;
            }
        }
    }
    for (int i = 0; i < userLength; i++) {
        if(tempUser[i] != '1'){
            return false;
        }
    }
    return true;
}

bool correctNewWord(char newWord[]){
    char dictionary[150];
    ifstream readToFile;
    readToFile.open("dictionary1.txt");
    if (!readToFile.is_open()) {
        cout << "cannot be opened";
        return false;
    }
    int lengthNewWord=length(newWord);
    int counter=0;
    while (readToFile.good()) {
        readToFile.getline(dictionary, 150);
        for(int i=0;i<lengthNewWord;i++){
            if(newWord[i]==dictionary[i]){
                counter++;
            }
        }
        if(counter==lengthNewWord){
            return true;
        }
    }
    return false;
    readToFile.close();
}

int playGame(int letters,int rounds){
    char randomLetters[101];
    char userWord[101];
    int sumOfPoints=0;

    for(int i=1;i<=rounds;i++) {
        cout << "<< Round " << i << "." << "Available letters: ";
        getRandomLetters(letters, randomLetters);
        cout << randomLetters << endl;
        cout << ">> Try with: ";
        cin >> userWord;
        while (!(validateUserWord(userWord, randomLetters) && findWord(userWord))) {
            cout << ">> Try again with another word or type 0 for new letters: ";
            cin >> userWord;
            if (userWord[0] == '0') {
                cout << "<< Round " << i << "." << "New available letters: ";
                getRandomLetters(letters, randomLetters);
                cout << randomLetters << endl;
            }
            cout << endl;
        }
        sumOfPoints += points(userWord);
        pressEnter();
        cout << "<< Your points so far are: " << sumOfPoints << endl;
    }
    return sumOfPoints;
}

void enteredOptionMenu(int numberForOption, int &letters, int &rounds) {
    int numberForSettings;

    if (numberForOption == 1) {
        int points;
        points=playGame(letters,rounds);
        cout<<endl;
        cout<<"Well done! Your total points are: "<<points<<endl;
        pressEnter();
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
        if(correctNewWord(newWord)){
            writeToFile << endl << newWord;
        }else{
            cout<<"The word doesn't exist"<<endl;
        }
        writeToFile.close();
    }
}

int main() {
    displayInstructions();
    cout << endl;
    cout << "Let's start! Press Enter to open the menu.";
    pressEnter();
    int numberForOption, letters = 10, rounds = 10;
    do {
        menu();
        cin >> numberForOption;
        enteredOptionMenu(numberForOption, letters, rounds);
    } while (numberForOption != 4);

    return 0;
}

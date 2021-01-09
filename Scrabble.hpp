#define MAX_LINE_LENGTH 100
#define NEWLINE_COUNT 40
#define MAX_INSTRUCTION_LEN 150
#define MAX_TRIES 3
#define DEFAULT_ROUNDS 10
#define DEFAULT_LETTERS 10

int length(char arr[]);

void clearScreen();

void pressEnter();

void displayInstructions();

void menu();

bool checkForVowel(int number, char randomLetters[]);

void copyArray(char arr[], char newArr[]);

int points(char userWord[]);

void randomGet(int number, char randomLetters[]);

void getRandomLetters(int number, char array[]);

void sortWord(char arr[]);

bool findWord(char userWord[]);

bool validateUserWord(char arrFromUser[], char lettersFromComputer[]);

bool correctNewWord(char newWord[]);

void displayChangedLetters(int &counter, int letters, char randomLetters[]);

int playGame(int letters, int rounds);

void enteredOptionMenu(int numberForOption, int &letters, int &rounds);
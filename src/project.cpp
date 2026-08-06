#include "project.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <random>

using namespace std;

// History linked list
void addGameResult(HistoryNode*& head, const GameResult& result) {
    HistoryNode* newNode = new HistoryNode;
    newNode->data = result;
    newNode->next = head;
    head = newNode;
}

void printHistory(HistoryNode* head) {
    HistoryNode* current = head;
    if (!current) {
        cout << "No game history yet.\n";
        return;
    }
    cout << "Game History:\n";
    while (current != nullptr) {
        cout << current->data.gameName << " -> " << current->data.outcome << "\n";
        current = current->next;
    }
}

void clearHistory(HistoryNode*& head) {
    HistoryNode* current = head;
    while (current != nullptr) {
        HistoryNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

//count letters
static int countLetters(const string& word) {
    int count = 0;
    for (char c : word) {
        if (isalpha(c)) {
            count++;
        }
    }
    return count;
}

//Four is the Magic Number
string toMagicFour(const string& startWord) {
    string current = startWord;
    string result = "";

    while (true) {
        if (current == "four") {
            result += "four is the magic number";
            break;
        }

        int letters = countLetters(current);

        string next;
        switch (letters) {
            case 1: next = "one"; break;
            case 2: next = "two"; break;
            case 3: next = "three"; break;
            case 4: next = "four"; break;
            case 5: next = "five"; break;
            case 6: next = "six"; break;
            case 7: next = "seven"; break;
            case 8: next = "eight"; break;
            case 9: next = "nine"; break;
            case 10: next = "ten"; break;
            case 11: next = "eleven"; break;
            case 12: next = "twelve"; break;
            case 13: next = "thirteen"; break;
            default: next = "many"; break;
        }

        result += current + " is to " + next + ", ";
        current = next;
    }

    return result;
}

//Heads or Tails
string randomHeadsOrTails() {
    srand(time(nullptr));
    return (rand() % 2 == 0) ? "heads" : "tails";
}

bool checkGuess(const string& guess, const string& actual) {
    string g = guess;
    string a = actual;

    transform(g.begin(), g.end(), g.begin(), ::tolower);
    transform(a.begin(), a.end(), a.begin(), ::tolower);

    return g == a;
}

//High-Low Number Guess
int generateSecretNumber() {
    srand(time(nullptr));
    return (rand() % 50) + 1;
}

string evaluateGuess(int guess, int secret) {
    if (guess < secret) return "Higher!";
    if (guess > secret) return "Lower!";
    return "Correct!";
}

void playHighLowGame(HistoryNode*& history) {
    int secret = generateSecretNumber();
    int guess = 0;

    cout << "I'm thinking of a number between 1 and 50.\n";

    while (true) {
        cout << "Enter your guess: ";
        cin >> guess;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        string result = evaluateGuess(guess, secret);
        cout << result << endl;

        if (result == "Correct!") {
            GameResult gr{"High-Low Guess", "Correct in some attempts"};
            addGameResult(history, gr);
            break;
        }
    }
}

//Word Scramble
static const int WORD_COUNT = 5;
static const string WORD_LIST[WORD_COUNT] = {
    "apple", "banana", "orange", "grape", "melon"
};

string getRandomWord() {
    srand(time(nullptr));
    int index = rand() % WORD_COUNT;
    return WORD_LIST[index];
}

string scrambleWord(const string& word) {
    string scrambled = word;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(scrambled.begin(), scrambled.end(), g);

    return scrambled;
}

bool isWordInList(const string& word) {
    for (int i = 0; i < WORD_COUNT; i++) {
        if (WORD_LIST[i] == word) {
            return true;
        }
    }
    return false;
}

void playWordScramble(HistoryNode*& history) {
    string original = getRandomWord();
    string scrambled = scrambleWord(original);

    cout << "Scrambled word: " << scrambled << "\n";
    cout << "Guess the original word: ";
    string guess;
    cin >> guess;

    if (guess == original) {
        cout << "Correct!\n";
        GameResult gr{"Word Scramble", "Guessed correctly"};
        addGameResult(history, gr);
    } else {
        cout << "Nope! It was " << original << "\n";
        GameResult gr{"Word Scramble", "Guessed incorrectly"};
        addGameResult(history, gr);
    }
}

//Game Result Viewer
void playResultViewer(HistoryNode* history) {
    cout << "Viewing latest game result:\n";
    if (!history) {
        cout << "No results yet.\n";
        return;
    }
    cout << "Most recent: " << history->data.gameName
         << " -> " << history->data.outcome << "\n";
}

//Game History
void playHistoryViewer(HistoryNode* history) {
    printHistory(history);
}

//Trivia Challenge
bool loadTriviaFromFile(const string& filename,
                        string questions[], string answers[],
                        int maxItems, int& count) {
    ifstream input(filename);
    if (!input.is_open()) {
        return false;
    }

    count = 0;
    string line;
    while (count < maxItems && getline(input, line)) {
        size_t sep = line.find('|');
        if (sep == string::npos) continue;
        questions[count] = line.substr(0, sep);
        answers[count] = line.substr(sep + 1);
        count++;
    }
    return count > 0;
}

void playTrivia(HistoryNode*& history) {
    const int MAX_TRIVIA = 20;
    string questions[MAX_TRIVIA];
    string answers[MAX_TRIVIA];
    int count = 0;

    if (!loadTriviaFromFile("data/trivia.txt", questions, answers, MAX_TRIVIA, count)) {
        cout << "Could not load trivia file.\n";
        return;
    }

    srand(time(nullptr));
    int index = rand() % count;

    cout << "Trivia: " << questions[index] << "\n";
    cout << "Your answer: ";
    string guess;
    cin >> guess;

    if (guess == answers[index]) {
        cout << "Correct!\n";
        GameResult gr{"Trivia", "Answered correctly"};
        addGameResult(history, gr);
    } else {
        cout << "Nope! Correct answer was: " << answers[index] << "\n";
        GameResult gr{"Trivia", "Answered incorrectly"};
        addGameResult(history, gr);
    }
}

// Menu
void printMenu() {
    cout << "\nMini‑Game Arcade\n";
    cout << "1. Four Is the Magic Number\n";
    cout << "2. Heads or Tails\n";
    cout << "3. High-Low Number Guess\n";
    cout << "4. Word Scramble\n";
    cout << "5. View Latest Game Result\n";
    cout << "6. View Game History\n";
    cout << "7. Trivia Challenge\n";
    cout << "0. Quit\n";
    cout << "Enter choice: ";
}

int getMenuChoice() {
    int choice;
    cin >> choice;
    if (!cin) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }    return choice;
}

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

// Structs for history
struct GameResult {
    std::string gameName;
    std::string outcome;
};

struct HistoryNode {
    GameResult data;
    HistoryNode* next;
};

// History list functions
void addGameResult(HistoryNode*& head, const GameResult& result);
void printHistory(HistoryNode* head);
void clearHistory(HistoryNode*& head);

//Four is the Magic Number
std::string toMagicFour(const std::string& word);

//Heads or Tails
std::string randomHeadsOrTails();
bool checkGuess(const std::string& guess, const std::string& actual);

//High-Low Number Guess
int generateSecretNumber();
std::string evaluateGuess(int guess, int secret);
void playHighLowGame(HistoryNode*& history);

//Word Scramble
std::string getRandomWord();
std::string scrambleWord(const std::string& word);
bool isWordInList(const std::string& word);
void playWordScramble(HistoryNode*& history);

//Game Result Viewer
void playResultViewer(HistoryNode* history);

//Game History
void playHistoryViewer(HistoryNode* history);

//Trivia Challenge
bool loadTriviaFromFile(const std::string& filename,
                        std::string questions[], std::string answers[],
                        int maxItems, int& count);
void playTrivia(HistoryNode*& history);

// Shared menu functions
void printMenu();
int getMenuChoice();

#endif

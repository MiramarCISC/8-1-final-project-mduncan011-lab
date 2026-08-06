#include <cassert>
#include <iostream>
#include "project.hpp"

using namespace std;

void testMagicFour() {
    string result = toMagicFour("thirteen");
    assert(result.find("thirteen is to eight") != string::npos);
    assert(result.find("eight is to five") != string::npos);
    assert(result.find("five is to four") != string::npos);
    assert(result.find("four is the magic number") != string::npos);
}

void testHeadsOrTailsCheck() {
    assert(checkGuess("heads", "heads"));
    assert(checkGuess("HEADS", "heads"));
    assert(!checkGuess("tails", "heads"));
}

void testHighLowEvaluation() {
    assert(evaluateGuess(10, 30) == "Higher!");
    assert(evaluateGuess(40, 30) == "Lower!");
    assert(evaluateGuess(30, 30) == "Correct!");
}

void testWordListSearch() {
    assert(isWordInList("apple"));
    assert(!isWordInList("pizza"));
}

void testStructAndHistory() {
    HistoryNode* history = nullptr;
    GameResult gr{"Test Game", "Test Outcome"};
    addGameResult(history, gr);
    assert(history != nullptr);
    assert(history->data.gameName == "Test Game");
    assert(history->data.outcome == "Test Outcome");
    clearHistory(history);
    assert(history == nullptr);
}

void testTriviaLoad() {
    const int MAX_TRIVIA = 10;
    string questions[MAX_TRIVIA];
    string answers[MAX_TRIVIA];
    int count = 0;

    bool ok = loadTriviaFromFile("tests/resources/sample_trivia.txt",
                                 questions, answers, MAX_TRIVIA, count);
    assert(ok);
    assert(count > 0);
}

int main() {
    testMagicFour();
    testHeadsOrTailsCheck();
    testHighLowEvaluation();
    testWordListSearch();
    testStructAndHistory();
    testTriviaLoad();

    cout << "All tests passed!" << endl;
    return 0;
}

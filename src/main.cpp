#include "project.hpp"
#include <iostream>

using namespace std;

int main() {
    bool running = true;
    HistoryNode* history = nullptr;

    while (running) {
        printMenu();
        int choice = getMenuChoice();

        switch (choice) {
            case 1: {
                string word;
                cout << "Enter a spelled-out number (e.g., thirteen): ";
                cin >> word;
                string result = toMagicFour(word);
                cout << result << endl;
                GameResult gr{"Four is the Magic Number", result};
                addGameResult(history, gr);
                break;
            }

            case 2: {
                string actual = randomHeadsOrTails();
                string guess;
                cout << "Heads or tails? ";
                cin >> guess;

                if (checkGuess(guess, actual)) {
                    cout << "yay!" << endl;
                    GameResult gr{"Heads or Tails", "Guessed correctly"};
                    addGameResult(history, gr);
                } else {
                    cout << "nope! It was " << actual << endl;
                    GameResult gr{"Heads or Tails", "Guessed incorrectly"};
                    addGameResult(history, gr);
                }
                break;
            }

            case 3:
                playHighLowGame(history);
                break;

            case 4:
                playWordScramble(history);
                break;

            case 5:
                playResultViewer(history);
                break;

            case 6:
                playHistoryViewer(history);
                break;

            case 7:
                playTrivia(history);
                break;

            case 0:
                running = false;
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    clearHistory(history);
    cout << "Goodbye!" << endl;
    return 0;
}

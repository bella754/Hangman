#pragma once
#include <string>
#include <set>

class Game {
public:
    Game();
    void run();
    bool makeMove();
    bool isWon() const;
    bool isLost() const;

private: 
    void processGuess(char ch);

    std::string secretWord;
    std::string masked;
    std::set<char> guessed;
    int wrongGuesses = 0;
    int maxWrong = 6;
};
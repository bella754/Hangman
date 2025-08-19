#include "Game.hpp"
#include "Input.hpp"
#include "WordProvider.hpp"   
#include <cctype>    
#include <iostream>    

static std::string spaced(const std::string& s) {
    std::string out; out.reserve(s.size() * 2);
    for (char c : s) { out.push_back(c); out.push_back(' '); }
    return out;
}

Game::Game() {
    WordProvider wp;
    secretWord = wp.getWord();         
    masked = std::string(secretWord.size(), '_'); 
    guessed = {};  
    wrongGuesses = 0;
    maxWrong = 6;
}

void Game::run() {
    while (!isWon() && !isLost()) {
        std::cout << "Wort: "   << spaced(masked)
                  << "  Fehler: " << wrongGuesses << "/" << maxWrong
                  << "\n";

        makeMove();
    }

    std::cout << (isWon() ? "🎉 Gewonnen! " : "💀 Verloren! ")
              << "Das Wort war: " << secretWord << "\n";
}

bool Game::makeMove() {
    if (isWon() || isLost()) return false;

    char ch = Input::getLetter(guessed);
    processGuess(ch);

    return !(isWon() || isLost());
}

bool Game::isWon() const {
    return masked == secretWord;
}

bool Game::isLost() const {
    return wrongGuesses >= maxWrong; 
}

void Game::processGuess(char ch) {
    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));

    if (guessed.count(ch)) return;
    guessed.insert(ch);

    bool hit = false;
    for (std::string::size_type i = 0; i < secretWord.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(secretWord[i])) == ch) {
            masked[i] = secretWord[i]; 
            hit = true;
        }
    }
    if (!hit) ++wrongGuesses;
}

#include "Input.hpp"
#include <iostream>
#include <limits>
#include <cctype>

char Input::getLetter(const std::set<char>& alreadyGuessed) {
    while (true) {
        std::cout << "Bitte genau einen Buchstaben eingeben: ";
        char letter;
        if (!(std::cin >> letter)) {
            std::cout << "Ungültige Eingabe. Bitte einzelnen Buchstaben eingeben.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (alreadyGuessed.count(letter)) {
            std::cout << "Buchstabe bereits eingegeben, bitte neuen versuchen.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));

        if (!std::isalpha(static_cast<unsigned char>(letter))) {
            std::cout << "Ungültig. Erlaubt ist genau EIN Buchstabe (A–Z).\n";
            continue;
        }

        return letter;
    }
}
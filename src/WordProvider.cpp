#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include "WordProvider.hpp"

std::string WordProvider::getWord() {
    std::ifstream file("../data/words.txt");

    if (!file) {
        throw std::runtime_error("Konnte words.txt nicht öffnen!");
    }

    std::vector<std::string> words;
    std::string word;

    while(std::getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    if (words.empty()) {
        throw std::runtime_error("Keine Wörter in words.txt gefunden!");
    }

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, (int)words.size() - 1); // define the range

    return words[distr(gen)];
}
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <ctime>

#define NOOB 1
#define PRO 2
#define GENIUS 3
#define MAX_CARDS 33
typedef unsigned short int level;

class Card {
    public:
        Card();
        void LoadCard(const std::string& filename);

        // getters, because question are in .txt files
        [[nodiscard]] std::string getQuestion() const;
        [[nodiscard]] std::string getAnswer() const;
        [[nodiscard]] std::string getCategory() const;
        [[nodiscard]] level getDifficulty() const;


    private:
        std::string question;
        std::string answer;
        std::string category;
        level difficulty{};
};

#endif // CARD_H
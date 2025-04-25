#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define NOOB 1
#define PRO 2
#define GENIUS 3
typedef unsigned short int level;

class Card {
    public:
        Card();
        static Card LoadCard(std::string filename);

        // getters, because question are in .txt files
        std::string getQuestion() const;
        std::string getAnswer() const;
        std::string getCategory() const;
        level getDifficulty() const;


    private:
        std::string question;
        std::string answer;
        std::string category;
        level difficulty;
};

#endif // CARD_H
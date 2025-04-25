#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>
#include <algorithm>

class Deck {
    public:
        Deck();
        static Deck LoadDeck(std::string filename);
        Card DrawCard();
    private:
        std::vector<Card> cards;
        std::size_t size;
        std::size_t currentCardIndex;
};

#endif // DECK_H
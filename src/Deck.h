#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>
#include <algorithm>

class Deck {
    public:
        Deck();

        void SetSize(size_t s);
        void SetCurrent(size_t c);
        size_t GetSize() const;
        size_t GetCurrent() const;

        void LoadDeck(int easy_questions, int medium_questions, int hard_questions);
        void LoadBasicDeck(); // 4noob-3pro-2genius
        void LoadNoobDeck();
        void LoadProDeck();
        void LoadGeniusDeck();

        Card DrawCard(int curr);
    private:
        std::vector<Card> cards;
        std::size_t size;
        std::size_t currentCardIndex;
};

#endif // DECK_H
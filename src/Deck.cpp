#include "Deck.h"

Deck::Deck() : size(0), currentCardIndex(0) {
    cards.reserve(MAX_CARDS);
}
void Deck::SetSize(const size_t s) {
    size = s;
}
void Deck::SetCurrent (const size_t c) {
    currentCardIndex = c;
}
size_t Deck::GetSize() const {
    return size;
}
size_t Deck::GetCurrent() const {
    return currentCardIndex;
}
void Deck::LoadDeck(const int easy_questions,const int medium_questions,const int hard_questions) {
    this->size = easy_questions+medium_questions+hard_questions;
    for (size_t i = 0; i < size; i++) {
        Card card;
        if (i < easy_questions) {
            card.LoadCard("questions/easy.txt");
        }
        else if (i < easy_questions+medium_questions) {
            card.LoadCard("questions/medium.txt");
        }
        else {
            card.LoadCard("questions/hard.txt");
        }
        cards.push_back(card);
    }
}
void Deck::LoadBasicDeck() {
    LoadDeck(4, 3, 2);
}
void Deck::LoadNoobDeck() {
    LoadDeck(9, 0, 0);
}
void Deck::LoadProDeck() {
    LoadDeck(0, 9, 0);
}
void Deck::LoadGeniusDeck() {
    LoadDeck(0,0,9);
}
Card Deck::DrawCard(const int curr) {
    if (curr >= size) {
        std::cerr << "no more cards to draw" << std::endl;
        return {};
    }
    return cards[curr];
}
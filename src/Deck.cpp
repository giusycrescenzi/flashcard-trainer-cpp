#include "Deck.h"

Deck::Deck() : size(0), currentCardIndex(0) {
    cards.reserve(MAX_CARDS);
}
void Deck::SetSize(size_t s) {
    size = s;
}
void Deck::SetCurrent (size_t c) {
    currentCardIndex = c;
}
size_t Deck::GetSize() const {
    return size;
}
size_t Deck::GetCurrent() const {
    return currentCardIndex;
}
void Deck::LoadDeck(int easy_questions, int medium_questions, int hard_questions) {
    Deck deck;
    deck.size = easy_questions+medium_questions+hard_questions;
    deck.currentCardIndex = 0;
    for (size_t i = 0; i < size; i++) {
        Card card;
        if (i < easy_questions) {
            card.LoadCard("easy.txt");
        }
        else if (i < easy_questions+medium_questions) {
            card.LoadCard("medium.txt");
        }
        else {
            card.LoadCard("hard.txt");
        }
        cards.push_back(card);
    }
}
void Deck::LoadBasicDeck() {
    Deck::LoadDeck(4, 3, 2);
}
void Deck::LoadNoobDeck() {
    Deck::LoadDeck(9, 0, 0);
}
void Deck::LoadProDeck() {
    Deck::LoadDeck(0, 9, 0);
}
void Deck::LoadGeniusDeck() {
    Deck::LoadDeck(0,0,9);
}
Card Deck::DrawCard(int curr) {
    if (curr >= size) {
        std::cerr << "no more cards to draw" << std::endl;
        return Card();
    }
    return cards[curr];
}
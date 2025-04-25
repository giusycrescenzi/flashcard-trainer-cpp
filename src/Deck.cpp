#include "Deck.h"

Deck Deck::LoadDeck(std::string filename) {
    for (int i = 0; i < size; i++) {
        Card::LoadCard(filename);
    }
}
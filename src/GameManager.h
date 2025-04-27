#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Card.h"
#include "Deck.h"

class GameManager {
    public:
        GameManager();
        void start();

        void SetPlayers(int p);
    private:
        int players;
        int GetPlayers() const;
        void DisplayHelp();
};

#endif //GAMEMANAGER_H
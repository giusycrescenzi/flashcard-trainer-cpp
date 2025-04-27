#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Card.h"
#include "Deck.h"

class GameManager {
    public:
        GameManager();
        void run();

        void SetNumPlayers(int p);
        void SetPlayerName(int n,const std::string& name); //NB takes the player index
        void SetScore(int n, int s);
    private:
        int players;
        int* Score;
        std::vector<std::string> names;
        int GetNumPlayers() const;
        std::string GameManager::GetPlayerName(int n,const std::string& name) const;
        int GetScore(int n, int s) const;
        

        // all commands will be private, calls will be handled at run time by run method
        void DisplayHelp() const;
        void DisplayScore() const;
        void SkipQuestion() const;
        void restart(int n, std::vector<Deck>& decks);
};

#endif //GAMEMANAGER_H
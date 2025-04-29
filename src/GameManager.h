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
        int * Score;
        std::vector<std::string> names;
        std::vector<Deck> decks;

        bool AllocateScore (int * ptr, const int n);
        int GetNumPlayers() const;
        std::string GameManager::GetPlayerName(int n,const std::string& name) const;
        int GetScore(int n, int s) const;
        Deck GetDeck(int n) const;

        

        // all commands will be private, calls will be handled at run time by run method
        // commands give different return values
        // 0 = command executed
        // 1 = quit
        // -1 = invalid command
        // 2 = add a point (the answer was right)
        // 3 = restart game
        // 4 = skip question
        int HandleCommand(const std::string& answer, Card currentCard) const;
        void DisplayHelp() const;
        void DisplayScore() const;
        void SkipQuestion() const;
        void RestartGame(int n);
};

#endif //GAMEMANAGER_H
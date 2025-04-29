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
        std::vector<int> Score;
        std::vector<std::string> names;
        std::vector<Deck> decks;

        int GetNumPlayers() const;
        std::string GameManager::GetPlayerName(int n,const std::string& name) const;
        int GetScore(int n, int s) const;
        Deck GetDeck(int n) const;

        

        // all commands will be private, calls will be handled at run time by run method
        // commands give different return values
        // 0 = command executed
        // 1 = quit
        // 2 = add a point (the answer was right)
        // 3 = restart game
        // 4 = skip question
        int HandleCommand(const std::string& answer, Card currentCard);
        void DisplayHelp() const;
        void DisplayScore() const;
        void SkipQuestion() const;
        void RestartGame();
        int FindWinner(const std::vector<int>& scores) const;
        void DisplayAbout() const;
};

#endif //GAMEMANAGER_H
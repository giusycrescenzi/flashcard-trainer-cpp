#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Deck.h"

class GameManager {
    public:
        GameManager();
        void run();

        void SetNumPlayers(int p);
        void SetPlayerName(const std::string& name);
        void SetScore(int s);
    private:
        int players;
        std::vector<int> Score;
        std::vector<std::string> names;
        std::vector<Deck> decks;

        [[nodiscard]]int GetNumPlayers() const;
        [[nodiscard]]std::string GetPlayerName(int n) const;
        [[nodiscard]]int GetScore(int n, int s) const;
        [[nodiscard]]Deck GetDeck(int n) const;

        

        // all commands will be private, calls will be handled at run time by run method
        // commands give different return values
        // 0 = command executed
        // 1 = quit
        // 2 = add a point (the answer was right)
        // 3 = restart game
        // 4 = skip question
        int HandleCommand(const std::string& answer, Card currentCard);
        static void DisplayHelp() ;
        void DisplayScore() const;
        void SkipQuestion() const;
        void RestartGame();
        [[nodiscard("you need it to declare the winner")]]
        int FindWinner(const std::vector<int>& scores) const;
        static void DisplayAbout() ;
        static void ClearScreen();
};

#endif //GAMEMANAGER_H
#include "GameManager.h"

void GameManager::SetNumPlayers(int p) {
    players = p;
}
int GameManager::GetNumPlayers() const {
    return players;
}
void GameManager::SetPlayerName(int n,const std::string& name) {
    names[n] = name;
}
std::string GameManager::GetPlayerName(int n,const std::string& name) const {
    return names[n];
}

void GameManager::run() {
    bool running = true;
    while (running) {
        // first thing is getting every player info in the manager
        do {
            std::cout << "insert number of players ";
            std::cin >> players;
        } while (players < 1);
        if (players == 1) {
            SetPlayerName(0, "You");
            std::cout << "There we go, best of luck pal" << std::endl;
        }
        else {
            std::cout << "game for " << players << " initialized, good luck";
            for (int i = 0; i < players; i++) {
                std::string name;
                std::cout << "player number " << i+1 << " insert your name";
                std::getline (std::cin, name);
                std::cout << name << " added" << std::endl;
                SetPlayerName (i, name);
            }
        }
    }
    
}

void GameManager::DisplayHelp() const{
    std::cout << "[ Commands ]" << std::endl;
    std::cout << "help          if you need to see this again"<< std::endl;
    std::cout << "about         show app info" << std::endl;
    std::cout << "score         show every player and his score" << std::endl;
    std::cout << "restart       to start a new game" << std::endl;
    std::cout << "quit          to exit the game" << std::endl;
}
void GameManager::DisplayScore() const {
    for (int i = 0; i < players; i++) {
        std::cout<<names[i]<<": ";
    }
}
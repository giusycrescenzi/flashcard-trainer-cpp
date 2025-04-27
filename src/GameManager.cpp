#include "GameManager.h"

void GameManager::SetPlayers(int p) {
    players = p;
}
int GameManager::GetPlayers() const {
    return players;
}

void GameManager::start() {

}

void GameManager::DisplayHelp() {
    std::cout << "[ Commands ]"
        << "H" <<std::endl;
}
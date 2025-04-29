#include "GameManager.h"

bool GameManager::AllocateScore (int * ptr, const int n) {
    ptr = (int*)malloc(n * sizeof(int));
    if (ptr == NULL)
        return false;
    return true;
}
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
Deck GameManager::GetDeck(int n) const {
    return decks[n];
}
void GameManager::SetScore(int n, int s) {
    Score[n] = s;
}
int GameManager::GetScore(int n, int s) const {
    return Score[n];
}

void GameManager::run() {
    bool running = true;
    // first thing is getting every player info in the manager
    {
    do {
        std::cout << "insert number of players ";
        std::cin >> players;
    } while (players < 1);
    if (players == 1) {
        SetPlayerName(0, "You");
        AllocateScore(Score, 1);
        std::cout << "There we go, best of luck pal" << std::endl;
    }
    else {
        std::cout << "game for " << players << " initialized, good luck";
        AllocateScore(Score, players);
        for (int i = 0; i < players; i++) {
            std::string name;
            std::cout << "player number " << i+1 << " insert your name";
            std::getline (std::cin, name);
            std::cout << name << " added" << std::endl;
            SetPlayerName (i, name);
        }
    }
    }
    // generate the desired deck of cards for every player
    deck_creation: {
        std::string inputcommand;
        std::cout << "There will be a deck of flashcards for each of you:";
        std::cout << "(please select the game mode using one the following commands)";
        std::cout << "easy      9 no-brainer questions";
        std::cout << "medium    9 question for normal-sized brains";
        std::cout << "hard      9 nearly impossible questions";
        std::cout << "go        4 easy, 3 medium and 2 hard questions";
        std::cout << "custom    choose yourself the composition of your decks";
        std::getline(std::cin, inputcommand);
        if (inputcommand == "easy") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadNoobDeck();
                decks[i] = deck;
            }
        }
        else if (inputcommand == "medium") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadProDeck();
                decks[i] = deck;
            }
        }
        else if (inputcommand == "hard") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadGeniusDeck();
                decks[i] = deck;
            }
        }
        else if (inputcommand == "go") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadBasicDeck();
                decks[i] = deck;
            }
        }
        else if (inputcommand == "custom") {
            int e, m, h;
            std::cout << "how many easy questions? ";
            std::cin >> e;
            std:: cout << "how many medium questions?";
            std::cin >> m;
            std::cout << "how many hard questions? ";
            std::cin >> h;
            std::cout << "created your customized deck" << std::endl;
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadDeck(e, m, h);
                decks[i] = deck;
            }
        }
        else {
            std::cout << "error: invalid command, please retry" << std::endl;
            goto deck_creation;
        }
    }
    // now the gameflow
    while (running) {
        int commandOutput = 0;
        for (int i = 1; i <= players; i++) {
            std::cout << "player " << i << " turn" << std::endl;
            std::cout << decks[i-1].DrawCard().getQuestion() << std::endl;
            std::string answer;
            std::getline(std::cin, answer);
            commandOutput = HandleCommand(answer, decks[i-1].DrawCard());
        }
    }
}
int GameManager::HandleCommand(const std::string& answer, Card currentCard) const {
    if (answer == "help") {
        DisplayHelp();
        return 0;
    } else if (answer == "about") {
        std::cout << "This is a flashcard game made by me, a noob programmer" << std::endl;
        std::cout << "I hope you enjoy it" << std::endl;
        return 0;
    } else if (answer == "score") {
        DisplayScore();
        return 0;
    } else if (answer == "restart") {
        RestartGame(players);
        return 3;
    } else if (answer == "quit") {
        std::cout << "Thanks for playing!" << std::endl;
        return 1;
    } else if (answer == currentCard.getAnswer()) {
        std::cout << "correct!" << std::endl;
        return 2;
    } else if (answer == "skip") {
        SkipQuestion();
        return 4;
    } else {
        std::cout << "Invalid command. Type 'help' for a list of commands." << std::endl;
        return -1;
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
        std::cout<<names[i] << ": " << Score[i] << std::endl;
    }
}
void GameManager::SkipQuestion() const {
    
    std::cout << "Question skipped." << std::endl;
}
void GameManager::RestartGame(int n) {
    for (int i = 0; i < n; i++) {
        decks[i].SetCurrent(0);
        Score[i] = 0;
    }
    std::cout << "Game restarted." << std::endl;
}
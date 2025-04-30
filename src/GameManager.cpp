#include "GameManager.h"

GameManager::GameManager() : players(0) {
}

void GameManager::SetNumPlayers(int p) {
    players = p;
}
int GameManager::GetNumPlayers() const {
    return players;
}
void GameManager::SetPlayerName(const std::string& name) {
    names.push_back(name);
}
std::string GameManager::GetPlayerName(int n) const {
    if (n >= 0 && n < names.size()) {
        return names[n];
    } else {
        std::cout << "Invalid player index." << std::endl;
        return "";
    }
}
Deck GameManager::GetDeck(int n) const {
    return decks[n];
}
void GameManager::SetScore(int n, int s) {
    Score.push_back(s);
}
int GameManager::GetScore(int n, int s) const {
    return Score[n];
}

void GameManager::run() {
    bool running = true;
    // first thing is getting every player info in the manager
    do {
        std::cout << "Insert number of players: ";
        std::cin >> players;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(10000, '\n'); // Ignore any remaining input
        }
    } while (players < 1 || std::cin.fail());
    if (players == 1) {
        SetPlayerName("You");
        SetScore(0, 0);
        std::cout << "There we go, best of luck pal" << std::endl;
    }
    else {
        std::cout << "game for " << players << " initialized, good luck";
        for (int i = 0; i < players; i++) {
            SetScore(i, 0);
            std::string name;
            std::cout << "player " << i+1 << " insert your name";
            std::getline (std::cin, name);
            std::cout << name << " added" << std::endl;
            SetPlayerName (name);
        }
    }
    // generate the desired deck of cards for every player
    deck_creation: {
        std::string inputcommand;
        std::cout << "There will be a deck of flashcards for each of you:" << std::endl;
        std::cout << "(please select the game mode using one the following commands)"<< std::endl;
        std::cout << "easy      9 no-brainer questions"<< std::endl;
        std::cout << "medium    9 question for normal-sized brains"<< std::endl;
        std::cout << "hard      9 nearly impossible questions"<< std::endl;
        std::cout << "go        4 easy, 3 medium and 2 hard questions"<< std::endl;
        std::cout << "custom    choose yourself the composition of your decks"<< std::endl;
        std::getline(std::cin, inputcommand);
        if (inputcommand == "easy") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadNoobDeck();
                decks.push_back(deck);
            }
        }
        else if (inputcommand == "medium") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadProDeck();
                decks.push_back(deck);
            }
        }
        else if (inputcommand == "hard") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadGeniusDeck();
                decks.push_back(deck);
            }
        }
        else if (inputcommand == "go") {
            for (int i = 0; i < players; i++) {
                Deck deck;
                deck.LoadBasicDeck();
                decks.push_back(deck);
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
                decks.push_back(deck);
            }
        }
        else {
            std::cout << "error: invalid command, please retry" << std::endl;
            goto deck_creation;
        }
    }
    // now the gameflow
    while (running) {
        // check if the player has finished his deck
        int commandOutput = 0;
        for (int i = 1; i <= players; i++) {
            // check if the player has finished his deck
            if (decks[i-1].GetCurrent() >= decks[i-1].GetSize()) {
                std::cout << "there are no more cards" << std::endl;
                running = false;
                break;
            }
            //player turn
            std::cout << "player " << i << " turn" << std::endl;
            question:{
                std::cout << decks[i-1].DrawCard(decks[i-1].GetCurrent()).getQuestion() << std::endl;
                std::string answer;
                std::getline(std::cin, answer);
                commandOutput = HandleCommand(answer, decks[i-1].DrawCard(decks[i-1].GetCurrent()));

                // handle the Command Output
                if (commandOutput == 1) {
                    running = false;
                    break;
                }
                else if (commandOutput == 2) {
                    Score[i-1]++;
                }
                else if (commandOutput == 3) {
                    goto deck_creation;
                }
                else if (commandOutput == 0) {
                    std::cout << "command executed, now you can give another or your answer" << std::endl;
                    goto question;
                }   
            }
            // increment the current card index
            decks[i-1].SetCurrent(decks[i-1].GetCurrent() + 1);
        }
    }
    // end of game
    std::cout << "game over" << std::endl;
    std::cout << "here are the scores" << std::endl;
    DisplayScore();
    std::cout << "the winner is" << names[FindWinner(Score)] << std::endl;
    //rematch ?
    std::cout << "want a rematch? (yes/no)";
    std::string rematch;
    std::getline(std::cin, rematch);
    if (rematch == "yes") {
        std::cout << "ok, let's go" << std::endl;
        RestartGame();
        goto deck_creation;
    }
    else if (rematch == "no") {
        std::cout << "thanks for playing!" << std::endl;
    }
    else {
        std::cout << "invalid command, exiting game" << std::endl;
    }
}
int GameManager::HandleCommand(const std::string& answer, Card currentCard) {
    if (answer == "help") {
        DisplayHelp();
        return 0;
    } else if (answer == "about") {
        DisplayAbout();
        return 0;
    } else if (answer == "score") {
        DisplayScore();
        return 0;
    } else if (answer == "restart") {
        RestartGame();
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
        return 0;
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
    // i know it's useless but i wanted it anyway
}
void GameManager::RestartGame() {
    for (int i = 0; i < players; i++) {
        decks[i].SetCurrent(0);
        Score[i] = 0;
    }
    std::cout << "Game restarted." << std::endl;
}
int GameManager::FindWinner(const std::vector<int>& scores) const {
    int maxScore = -1;
    int winnerIndex = -1;
    for (int i = 0; i < players; i++) {
        if (scores[i] > maxScore) {
            maxScore = scores[i];
            winnerIndex = i;
        }
    }
    return winnerIndex;
}
void GameManager::DisplayAbout() const {
    std::cout << "[ Mr. KnowItAll ]" << std::endl;
    std::cout << "this is a flashcard trainer, a trivia game:" << std::endl;
    std::cout << "you will answer different questions and earn points" << std::endl;
    std::cout << "who gets the highest score wins" << std::endl;
    std::cout << "VERSION 1.0" << std::endl;
    std::cout << "CREATOR: Giuseppe Crescenzi, giusycrescenzi on GitHub" << std::endl;
}
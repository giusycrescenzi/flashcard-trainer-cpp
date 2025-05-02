#include "Card.h"

Card::Card() = default;

void Card::LoadCard(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Estrai indice casuale della riga da caricare
    static std::mt19937 rng(std::random_device{}()); // generatore statico, una volta sola
    std::uniform_int_distribution dist(0, MAX_CARDS - 1);
    int targetLine = dist(rng); // diverso ad ogni chiamata

    std::string line;
    int currentLine = 0;
    while (std::getline(file, line)) {
        if (currentLine == targetLine) {
            std::stringstream ss(line);
            std::string q, a, c, d_intcast;

            if (std::getline(ss, q, '|') &&
                std::getline(ss, a, '|') &&
                std::getline(ss, c, '|') &&
                std::getline(ss, d_intcast)) {
                
                this->question = q;
                this->answer = a;
                this->category = c;
                this->difficulty = static_cast<level>(std::stoi(d_intcast));
            } else {
                std::cerr << "Failed to parse line: " << line << std::endl;
            }
            break;
        }
        ++currentLine;
    }
    file.close();
}

std::string Card::getQuestion() const {
    return question;
}
std::string Card::getAnswer() const {
    return answer;
}
std::string Card::getCategory() const {
    return category;
}
level Card::getDifficulty() const {
    return difficulty;
}
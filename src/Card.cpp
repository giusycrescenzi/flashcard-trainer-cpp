#include "Card.h"

void Card::LoadCard(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line, q, a, c, d_intcast;
    Card card;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (std::getline(ss, q, '|') &&
            std::getline(ss, a, '|') &&
            std::getline(ss, c, '|') &&
            std::getline(ss, d_intcast)) { // need to parse the line in the .txt
            card.question = q;
            card.answer = a;
            card.category = c;
            card.difficulty = static_cast<level>(std::stoi(d_intcast));
            // now i have a card object with all the data
        }
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
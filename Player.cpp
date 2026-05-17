#include "Player.h"
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;

Player::Player(const string& n) : name(n) {}

Player::~Player() {
    for (int i = 0; i < hand.size(); i++) {
        delete hand[i];
    }
    hand.clear();

    for (int i = 0; i < wonCards.size(); i++) {
        delete wonCards[i];
    }
    wonCards.clear();
}

void Player::addCard(Card* c) {
    hand.push_back(c);
}

Card* Player::playCard(int index) {
    Card* c = hand[index];
    hand.erase(hand.begin() + index);
    return c;
}

void Player::captureCards(vector<Card*>& captured) {
    for (int i = 0; i < captured.size(); i++) {
        wonCards.push_back(captured[i]);
    }
    captured.clear();
}

int Player::calculateScore() const {
    int score = 0;

    for (int i = 0; i < wonCards.size(); i++) {
        Card* card = wonCards[i];

        if (card->value == 10 && card->suit == "Diamonds") {
            score += 3;
        }
        else if (card->value == 2 && card->suit == "Clubs") {
            score += 2;
        }
        else if (card->suit == "Clubs") {
            score += 1;
        }
    }
    return score;
}
const vector<Card*>& Player::getHand() const { return hand; }
const vector<Card*>& Player::getWonCards() const { return wonCards; }

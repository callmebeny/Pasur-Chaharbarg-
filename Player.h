#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"

using std::string;
using std::vector;

class Player {
private:
    vector<Card*> hand;
    vector<Card*> wonCards;

public:
    string name;
    Player(const string& n = "");
    ~Player();

    void addCard(Card* c);
    Card* playCard(int index);
    void captureCards(vector<Card*>& captured);
    int calculateScore() const;

    const vector<Card*>& getHand() const;
    const vector<Card*>& getWonCards() const;
};

#endif

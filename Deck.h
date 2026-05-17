#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"
#include "DerivedCards.h"

using std::vector;
using std::size_t;

class Deck {
private:
    vector<Card*> deck;

public:
    Deck();
    ~Deck();

    void createDeck();
    void shuffleDeck(int seed);
    bool isEmpty() const;
    size_t size() const;
    Card* drawCard();
};

#endif

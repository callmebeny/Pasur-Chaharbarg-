#include "Deck.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::swap;

Deck::Deck() {
    createDeck();
}

Deck::~Deck() {
    for (int i = 0; i < deck.size(); i++) {
        delete deck[i];
    }
    deck.clear();
}

void Deck::createDeck() {
    for (int i = 0; i < deck.size(); i++) {
        delete deck[i];
    }
    deck.clear();

    string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};

    for (int i = 0; i < 4; i++) {
        string s = suits[i];

        for (int v = 1; v <= 13; v++) {
            string img = getCardImage(v, s);

            if (v == 1) {
                deck.push_back(new AceCard(s, img));
            }
            else if (v >= 2 && v <= 10) {
                deck.push_back(new NumberCard(v, s, img));
            }
            else if (v == 11) {
                deck.push_back(new JackCard(s, img));
            }
            else if (v == 12) {
                deck.push_back(new QueenCard(s, img));
            }
            else {
                deck.push_back(new KingCard(s, img));
            }
        }
    }
}

void Deck::shuffleDeck(int seed) {
    std::srand(seed);

    for (int i = deck.size() - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(deck[i], deck[j]);
    }
}

bool Deck::isEmpty() const {
    return deck.empty();
}

size_t Deck::size() const {
    return deck.size();
}

Card* Deck::drawCard() {
    Card* c = deck.back();
    deck.pop_back();
    return c;
}

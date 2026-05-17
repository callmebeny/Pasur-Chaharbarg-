#include "Game.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using std::cout;
using std::vector;
using std::size_t;

Game::Game(const string& n1, const string& n2, int seed)
	: p1(n1), p2(n2)
{

    unsigned int finalSeed;
    if (seed == 0) {
        finalSeed = static_cast<unsigned int>(std::time(nullptr));
    } else {
        finalSeed = static_cast<unsigned int>(seed);
    }

    this->currentSeed = finalSeed;


    deck.createDeck();
    deck.shuffleDeck(finalSeed);

	deal4Cards();

    if (table.empty()) {
        for (int i = 0; i < 4; i++) {
            if (!deck.isEmpty()) {
                table.push_back(deck.drawCard());
            }
        }
    }
}

Game::~Game() {

	for (int i = 0; i < table.size(); i++) {
        delete table[i];
    }
    table.clear();
}

void Game::deal4Cards() {

    if (deck.isEmpty()) return;

    for (int i = 0; i < 4; ++i) {
        if (!deck.isEmpty()) {
            p1.addCard(deck.drawCard());
        }
    }

	for (int i = 0; i < 4; ++i) {
        if (!deck.isEmpty()) {
            p2.addCard(deck.drawCard());
        }
    }
}

void Game::nextRound() {

	if (p1.getHand().empty() && p2.getHand().empty()) {
		deal4Cards();

	}
}

bool Game::attemptCapture(Player& player, int handIndex, int tableIndex) {

	if (handIndex < 0 || handIndex >= player.getHand().size()) {
		return false;
	}
	Card* cardFromHand = player.getHand()[handIndex];
	Card* cardOnTable = nullptr;
	bool captureSuccess = false;

	if (tableIndex >= 0 && tableIndex < table.size()) {
		cardOnTable = table[tableIndex];
	}

	if (cardOnTable != nullptr && cardFromHand->canCapture(*cardOnTable)) {
		vector<Card*> capturedPile;

		Card* playedCard = player.playCard(handIndex);

		capturedPile.push_back(table[tableIndex]);
		table.erase(table.begin() + tableIndex);
		playedCard->captureEffect(table, capturedPile);
		capturedPile.push_back(playedCard);
		player.captureCards(capturedPile);

		captureSuccess = true;
	}

	if (!captureSuccess) {
		Card* playedCard = player.playCard(handIndex);
		table.push_back(playedCard);
	}

	return true;
}

int Game::getSeed() { return currentSeed; }
Player& Game::getPlayer1() { return p1; }
Player& Game::getPlayer2() { return p2; }
vector<Card*>& Game::getTable() { return table; }
Deck& Game::getDeck() { return deck; }

bool Game::isGameOver() const {
    return deck.isEmpty() && p1.getHand().empty() && p2.getHand().empty();
}

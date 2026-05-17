#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Game {
private:
    Deck deck;
    Player p1;
    Player p2;
    vector<Card*> table;
    int currentSeed;

public:
    Game(const string& n1, const string& n2, int seed = 0);
    ~Game();

    int getSeed();
    void deal4Cards();
    bool attemptCapture(Player& player, int handIndex, int tableIndex);
    bool isGameOver() const;
    void nextRound();

    Player& getPlayer1();
    Player& getPlayer2();
    vector<Card*>& getTable();
    Deck& getDeck();
};

#endif

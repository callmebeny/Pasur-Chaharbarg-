#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Card {
public:
    int value;
    string suit;
    string image;

    Card(int v, const string& s, const string& img);
    virtual ~Card();

    virtual bool canCapture(const Card& tableCard) const;
    virtual void captureEffect(vector<Card*>& table, vector<Card*>& captured) const;

    virtual string toString() const;
};

string getCardImage(int value, const string& suit);

#endif

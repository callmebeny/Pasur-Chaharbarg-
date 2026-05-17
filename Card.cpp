#include "Card.h"
#include <algorithm>
#include <cctype>

using std::string;
using std::vector;
using std::to_string;

Card::Card(int v, const string& s, const string& img)
    : value(v), suit(s), image(img) {}

Card::~Card() {}

bool Card::canCapture(const Card& tableCard) const {
    return (value + tableCard.value == 11);
}

void Card::captureEffect(vector<Card*>& table, vector<Card*>& captured) const {
    captured.push_back(table.back());
    table.pop_back();
}

string Card::toString() const {
    if (value == 1) return "A" + suit.substr(0,1);
    if (value == 11) return "J" + suit.substr(0,1);
    if (value == 12) return "Q" + suit.substr(0,1);
    if (value == 13) return "K" + suit.substr(0,1);
    return to_string(value) + suit.substr(0,1);
}

string getCardImage(int value, const string& suit) {
    string v;

    if (value == 1) v = "Ace";
    else if (value == 11) v = "Jack";
    else if (value == 12) v = "Queen";
    else if (value == 13) v = "King";
    else v = to_string(value);

    string s = suit;
    for (auto &c : s) c = tolower(c);

	return ExtractFilePath(Application->ExeName) + "Pozecarti\\" + v + "_of_" + s + ".png";

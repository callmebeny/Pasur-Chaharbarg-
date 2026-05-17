#include "DerivedCards.h"
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::to_string;


NumberCard::NumberCard(int v, const string& s, const string& img)
    : Card(v, s, img) {}

bool NumberCard::canCapture(const Card& tableCard) const {

    return value + tableCard.value == 11;
}

void NumberCard::captureEffect(vector<Card*>&, vector<Card*>&) const {

}

string NumberCard::toString() const {
    return to_string(value) + suit.substr(0, 1);
}

JackCard::JackCard(const string& s, const string& img)
    : Card(11, s, img) {}

bool JackCard::canCapture(const Card& tableCard) const {
	return (tableCard.value != 12 && tableCard.value != 13);
}

void JackCard::captureEffect(vector<Card*>& table, vector<Card*>& captured) const {
    auto it = table.begin();
    while (it != table.end()) {

		if ((*it)->value != 12 && (*it)->value != 13) {

			captured.push_back(*it);
			it = table.erase(it);
        } else {

            ++it;
        }
    }
}

string JackCard::toString() const {
    return "J" + suit.substr(0, 1);
}

QueenCard::QueenCard(const string& s, const string& img)
    : Card(12, s, img) {}

bool QueenCard::canCapture(const Card& tableCard) const {

	return value == tableCard.value;
}

void QueenCard::captureEffect(vector<Card*>&, vector<Card*>&) const {
}

string QueenCard::toString() const {
    return "Q" + suit.substr(0, 1);
}

KingCard::KingCard(const string& s, const string& img)
    : Card(13, s, img) {}

bool KingCard::canCapture(const Card& tableCard) const {

    return value == tableCard.value;
}

void KingCard::captureEffect(vector<Card*>&, vector<Card*>&) const {

}

string KingCard::toString() const {
    return "K" + suit.substr(0, 1);
}
AceCard::AceCard(const string& s, const string& img)
    : Card(1, s, img) {}

bool AceCard::canCapture(const Card& tableCard) const {
	return (value == tableCard.value) || (tableCard.value == 10);
}

void AceCard::captureEffect(vector<Card*>&, vector<Card*>&) const {
}

string AceCard::toString() const {
    return "A" + suit.substr(0, 1);
}

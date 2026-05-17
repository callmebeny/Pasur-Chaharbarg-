#ifndef DERIVEDCARDS_H
#define DERIVEDCARDS_H

#include "Card.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class NumberCard : public Card {
public:
    NumberCard(int v, const string& s, const string& img);
    bool canCapture(const Card& tableCard) const override;
    void captureEffect(vector<Card*>& table, vector<Card*>& captured) const override;
    string toString() const override;
};

class JackCard : public Card {
public:
    JackCard(const string& s, const string& img);

    bool canCapture(const Card& tableCard) const override;
    void captureEffect(vector<Card*>& table, vector<Card*>& captured) const override;
    string toString() const override;
};

class QueenCard : public Card {
public:
    QueenCard(const string& s, const string& img);

    bool canCapture(const Card& tableCard) const override;
    void captureEffect(vector<Card*>& table, vector<Card*>& captured) const override;
    string toString() const override;
};

class KingCard : public Card {
public:
    KingCard(const string& s, const string& img);

    bool canCapture(const Card& tableCard) const override;
    void captureEffect(vector<Card*>& table, vector<Card*>& captured) const override;
    string toString() const override;
};

class AceCard : public Card {
public:
    AceCard(const string& s, const string& img);

    bool canCapture(const Card& tableCard) const override;
    void captureEffect(vector<Card*>& table, vector<Card*>& captured) const override;
    string toString() const override;
};

#endif

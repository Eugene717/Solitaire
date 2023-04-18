#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

enum Suit
{
	diamond, heart, spade, club
};

class Card
{
	Suit m_suit;
	int m_value;
	bool m_isFaceUp;
public:
	Card(Suit suit, int value);
	friend std::ostream& operator<<(std::ostream& os, Card card);
	bool operator==(const Card& other);
	void Flip();
	bool isFaceUp();
	Suit suit();
	int value();
};

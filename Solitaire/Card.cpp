#include "Card.h"

#include <Windows.h>

Card::Card(Suit suit, int value) :m_suit(suit), m_value(value), m_isFaceUp(false)
{ }

void Card::Flip()
{
	m_isFaceUp = true;
}

bool Card::isFaceUp()
{
	return m_isFaceUp;
}

Suit Card::suit()
{
	return m_suit;
}

int Card::value()
{
	return m_value;
}

bool Card::operator==(const Card& other)
{
	return m_value == other.m_value && m_suit == other.m_suit;
}

std::ostream& operator<<(std::ostream& os, Card card)
{
	if (card.m_isFaceUp)
	{
		if (card.m_value == 1)
		{
			os << 'A';
		}
		else if (card.m_value == 10)
		{
			os << '\b' << "10";
		}
		else if (card.m_value == 11)
		{
			os << 'J';
		}
		else if (card.m_value == 12)
		{
			os << 'Q';
		}
		else if (card.m_value == 13)
		{
			os << 'K';
		}
		else
		{
			os << card.m_value;
		}
		_setmode(_fileno(stdout), _O_U16TEXT);
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (card.m_suit)
		{
		case diamond:
			SetConsoleTextAttribute(handle, FOREGROUND_RED);
			std::wcout << L"\u2666";
			SetConsoleTextAttribute(handle, 0x0007);
			break;
		case heart:
			SetConsoleTextAttribute(handle, FOREGROUND_RED);
			std::wcout << L"\u2665";
			SetConsoleTextAttribute(handle, 0x0007);
			break;
		case spade:
			std::wcout << L"\u2660";
			break;
		case club:
			std::wcout << L"\u2663";
			break;
		default:
			break;
		}
		_setmode(_fileno(stdout), _O_TEXT);
	}
	else
	{
		os << " *";
	}
	return os;
}

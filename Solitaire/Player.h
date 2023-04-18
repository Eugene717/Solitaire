#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>
#include "Card.h"

using VecCard = std::vector<Card>;

class Player
{
	VecCard m_hand;
	std::vector<VecCard> m_collums{ VecCard(),VecCard(),VecCard(),VecCard(),VecCard(),VecCard(),VecCard() };
	VecCard::iterator m_openCardOne/*, m_openCardTwo, m_openCardThree*/;
	Card* m_aceDiamond, * m_aceHeart, * m_aceSpade, * m_aceClub;

	void FillColl(std::vector<Card>& deck, std::vector<Card>& coll,const int& cards);
	void choiceCard(int& col, int& row);
	void NewCard();
	bool cardCheck(const int& col, const int& row);
	bool aceAction(const int& col, const int& row);
	void choicePlace(const int& col, const int& row);
	void openCard(const int& col);
public:
	Player();
	void RearrangeCard();
	bool CheckWin();
	void Draw();
};


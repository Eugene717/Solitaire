#include "Player.h"

using namespace std;

void Player::FillColl(std::vector<Card>& deck, std::vector<Card>& coll, const int& cards)
{
	coll.reserve(13);
	for (size_t i = 0; i < cards; i++)
	{
		coll.push_back(std::move(deck[deck.size() - 1]));
		deck.pop_back();
	}
}

Player::Player()
{
	m_hand.reserve(52);
	for (size_t value = 1; value < 14; value++)
	{
		for (size_t suit = diamond; suit < club + 1; suit++)
		{
			m_hand.push_back(Card(static_cast<Suit>(suit), value));
		}
	}

	std::random_device rd;
	std::mt19937 eng(rd());
	std::shuffle(m_hand.begin(), m_hand.end(), eng);

	for (size_t i = 0; i < m_collums.size(); i++)
	{
		FillColl(m_hand, m_collums[i], i + 1);
		(m_collums[i])[m_collums[i].size() - 1].Flip();  //вызвать у последней карты [i] елемента вектора m_collums метод Flip()
	}

	m_openCardOne = m_hand.end();

	for (auto& i : m_hand)
	{
		i.Flip();
	}
}

void Player::NewCard()
{
	if (m_openCardOne != m_hand.end())
	{
		++m_openCardOne;
	}
	else
		m_openCardOne = m_hand.begin();
	
}

void Player::choiceCard(int& col,int& row)
{
	cout << "Для взятия карты из колоды в руку нажмите \"N\"\n";
	cout << "Для перемещения карты из руки нажмите\"С\"\n";
	cout << "Введите номер колонки для перемещенния карты(1-7): ";
	do
	{
		char key;
		switch (cin >> key; key)
		{
		case 'N': case 'n':
			NewCard();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			col = 8;
			return;
		case 'C': case 'c':
			col = 7;  //7 = m_openCardOne
			return;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7':
			col = (key - '0') - 1;
			break;
		default:
			cout << "Неправильная кнопка!\n";
			col = -1;
			break;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (col < 0 || col > 7);

	cout << "Введите номер строки, где находиться нужная карта(1-15): ";
	while (true)
	{
		cin >> row;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Ошибка ввода!\n";
		}
		--row;
		if (row < 0 || row > 15)
			cout << "Неправильная цифра\n";
		else
			break;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool Player::cardCheck(const int& col, const int& row)
{
	if (col != 7)
	{
		if (m_collums[col].size() <= row)
		{
			cout << "Карты с таким положением нет!\n";
			system("pause");
			Draw();
			return false;
		}
		else if (!(m_collums[col])[row].isFaceUp())
		{
			cout << "Карта недоступна\n";
			system("pause");
			Draw();
			return false;
		}
		else
			return true;
	}
	else if (m_openCardOne == m_hand.end())
	{
		cout << "Карты в руке нет!\n";
		return false;
	}
	else
		return true;
}

bool Player::aceAction(const int& col, const int& row)
{	
	if (col != 7)
	{
		if (char key; (m_collums[col])[row].value() == 1)  //если туз
		{
			cout << "Поместить туз на базу(y/n)? ";
			while (true)
			{
				cin >> key;
				if (key == 'y')
				{
					switch (m_collums[col][row].suit())
					{
					case diamond:
						m_aceDiamond = new Card(diamond, 0);
						copy(m_collums[col].end() - 1, m_collums[col].end(), m_aceDiamond);
						m_collums[col].erase(m_collums[col].end() - 1, m_collums[col].end());
						openCard(col);
						break;
					case heart:
						m_aceHeart = new Card(diamond, 0);
						copy(m_collums[col].end() - 1, m_collums[col].end(), m_aceHeart);
						m_collums[col].erase(m_collums[col].end() - 1, m_collums[col].end());
						openCard(col);
						break;
					case spade:
						m_aceSpade = new Card(diamond, 0);
						copy(m_collums[col].end() - 1, m_collums[col].end(), m_aceSpade);
						m_collums[col].erase(m_collums[col].end() - 1, m_collums[col].end());
						openCard(col);
						break;
					case club:
						m_aceClub = new Card(diamond, 0);
						copy(m_collums[col].end() - 1, m_collums[col].end(), m_aceClub);
						m_collums[col].erase(m_collums[col].end() - 1, m_collums[col].end());
						openCard(col);
						break;
					}
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					return true;
				}
				else if (key == 'n')
				{
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					return false;
				}
				else
				{
					cout << "Неправильная кнопка!\n";
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
	return false;
}

void Player::choicePlace(const int& col, const int& row)
{
	int col2;
	cout << "Введите колонку на которую нужно переместить(1-7): ";
	while (true)
	{
		cin >> col2;
		--col2;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Ошибка ввода!\n";
		}
		else if (col2 >= 0 && col2 <= 6)
		{
			if (col != 7)  //если карта не в руке
			{
				if ((m_collums[col])[row].value() == 13 && m_collums[col2].empty())  //если король
				{
					copy(m_collums[col].begin() + row, m_collums[col].end(), back_inserter(m_collums[col2]));
					m_collums[col].erase(m_collums[col].begin() + row, m_collums[col].end());

					openCard(col);

					return;
				}
				else if (!m_collums[col2].empty())
				{
					if ((m_collums[col][row].suit() == diamond || m_collums[col][row].suit() == heart &&
						(m_collums[col2][(m_collums[col2].size() - 1)].suit() == spade || (m_collums[col2])[(m_collums[col2].size() - 1)].suit() == club)) ||
						(m_collums[col][row].suit() == spade || m_collums[col][row].suit() == club &&
							(m_collums[col2][m_collums[col2].size() - 1].suit() == diamond || m_collums[col2][m_collums[col2].size() - 1].suit() == heart)))  //если масти противоположны по цвету
					{
						if (((m_collums[col])[row].value() + 1) == (m_collums[col2])[m_collums[col2].size() - 1].value())  //если перемещаемая карта слабее чем последняя карта во второй колонке
						{
							copy(m_collums[col].begin() + row, m_collums[col].end(), back_inserter(m_collums[col2]));
							m_collums[col].erase(m_collums[col].begin() + row, m_collums[col].end());

							openCard(col);

							return;
						}
					}
				}
			}
			else  //карта в руке
			{
				if (m_openCardOne->value() == 13 && m_collums[col2].empty())  //если король в руке
				{
					copy(m_openCardOne, m_openCardOne + 1, back_inserter(m_collums[col2]));

					remove(m_hand.begin(), m_hand.end(), *m_openCardOne);
					m_hand.pop_back();

					if (!m_hand.empty())
					{
						if (m_openCardOne != m_hand.begin())
						{
							--m_openCardOne;
						}
						else
							m_openCardOne = m_hand.end();
					}

					return;
				}
				else if (!m_collums[col2].empty())
				{
					if ((m_openCardOne->suit() == diamond || m_openCardOne->suit() == heart &&
						(m_collums[col2][(m_collums[col2].size() - 1)].suit() == spade || m_collums[col2][(m_collums[col2].size() - 1)].suit() == club)) ||
						(m_openCardOne->suit() == spade || m_openCardOne->suit() == club &&
							((m_collums[col2])[(m_collums[col2].size() - 1)].suit() == diamond || (m_collums[col2])[(m_collums[col2].size() - 1)].suit() == heart)))  //если масти противоположны по цвету
					{
						if (m_openCardOne->value() + 1 == (m_collums[col2])[m_collums[col2].size() - 1].value()) //проверка карты в руке на value
						{
							copy(m_openCardOne, m_openCardOne + 1, back_inserter(m_collums[col2]));

							remove(m_hand.begin(), m_hand.end(), *m_openCardOne);
							m_hand.pop_back();

							if (!m_hand.empty())
							{
								if (m_openCardOne != m_hand.begin())
								{
									--m_openCardOne;
								}
								else
									m_openCardOne = m_hand.end();
							}

							return;
						}
					}
				}
			}
			cout << "Карта не может здесь находится!\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Хотите поменять карту(y/n)? ";
			while (true)
			{
				if (char key(getchar()); key == 'y')
				{
					return;
				}
				else if (key == 'n')
				{
					cout << "Введите колонку на которую нужно переместить(0-6): ";
					break;
				}
			}
		}
		else
			cout << "Неправильное число!\n";
	}
}

void Player::openCard(const int& col)
{
	if (m_collums[col].size() != 0)
	{
		if (!(m_collums[col])[m_collums[col].size() - 1].isFaceUp())
		{
			(m_collums[col])[m_collums[col].size() - 1].Flip();
		}
	}
}

void Player::RearrangeCard()
{
	int col;
	int row;

	do
	{
		choiceCard(col, row);
		if (col == 8)  //NewCard() произошел
			return;		
	} while (!cardCheck(col, row));  //проверка карты

	if (aceAction(col, row))  //true при перемещении туза на базу
		return;

	choicePlace(col, row);	
}

bool Player::CheckWin()
{
	int collected = 0;

	for (size_t i = 0; i < 7; i++)
	{
		if (m_collums[i].size() == 12 || m_collums[i].size() == 13)
		{
			if (m_collums[i].front().value() == 13 && (m_collums[i].back().value() == 2 || m_collums[i].back().value() == 1))
			{
				++collected;
			}
		}
	}
	if (collected == 4)
		return true;
	else
		return false;
}

void Player::Draw()
{
	system("cls");
	cout << endl << ' ';
	if (m_openCardOne != m_hand.end())
	{
		if (m_openCardOne == m_hand.begin())
			cout << setw(3) << *m_openCardOne << ' ';
		else if (m_openCardOne == m_hand.begin() + 1)
			cout << setw(3) << *m_openCardOne << ' ' << setw(3) << *(m_openCardOne - 1) << ' ';
		else
			cout << setw(3) << *m_openCardOne << ' ' << setw(3) << *(m_openCardOne - 1) << ' ' << setw(3) << *(m_openCardOne - 2) << ' ';
	}
	else
		cout << "      ";

	cout << "\t\t";
	m_aceDiamond == nullptr ? cout << ' ' : cout << *m_aceDiamond;
	m_aceHeart == nullptr ? cout << ' ' : cout << *m_aceHeart;
	m_aceSpade == nullptr ? cout << ' ' : cout << *m_aceSpade;
	m_aceClub == nullptr ? cout << ' ' : cout << *m_aceClub;
	cout << endl << endl;
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 7; j++)
		{			
			if (i < (m_collums[j]).size())
				cout << "        " << (m_collums[j])[i];
			else
				cout << setw(10) << " ";
		}
		cout << endl;
	}
}

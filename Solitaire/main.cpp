#include "pch.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	while (true)
	{
		cout << "������ ���� Solitaire\n";
		system("pause");
		while (true)
		{
			Player you;
			do
			{
				you.Draw();
				you.RearrangeCard();
			} while (!you.CheckWin());
			cout << "�� ��������� ����\n";
			system("pause");
			break;
		}
	}
}

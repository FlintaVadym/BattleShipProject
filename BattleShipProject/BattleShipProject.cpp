// BattleShipProject.cpp : Defines the entry point for the console application.
//

#include "Header.h"


using namespace std;

void Menu();

int main()
{	
	
	Menu();

    return 0;
}

//0 - в поле пусто (по нему не стреляли) ' '
//1 - корабль 'Z'
//2 - корабль подбит 'X'
//3 - промах '*'


void Menu()
{
	int PlayerChoose;
	classPlayer* PC = nullptr;
	classPlayer* Player = nullptr;

	while (true)
	{
		system("cls");
		cout << "---------Menu---------\n\n";
		cout << "1 New Game\n";
		cout << "2 Continium game\n";
		cout << "3 Exit\n\n";

		cout << "Enter your choice: ";
		cin >> PlayerChoose;


		switch (PlayerChoose)
		{
		case 1:
		{
			system("cls");
			// BUG !!!
			// когда создается класс PC - в консольвыводится поле  PC с отрисовкаой !
			PC = new classPlayer("PC", false);

			

			string newName;
			cout << "Input your name: ";
			cin >> newName;
			Player = new classPlayer(newName, true);
			
			// BUG !!!
			// Паузу вставил временно - чтобы видеть что поле плеера создалось так же
			system("pause");

			if (!Player->DrawField(true))
				cout << "Broken field!\n";

			cout << "\n\n";

			if (!Player->DrawField(false))
				cout << "Broken field!\n";			

			//Shoot(fieldPC, 10, 10);
			// тут нужно зацикливать пока все корабли одной из сторон не подбиты или пока все поля не обстреляны?

			while (Player->CheckSheeps() && PC->CheckSheeps())
			{
				static bool repeat(false);
				do {
					repeat = Player->Shoot();
				} while (repeat);

				do {
					repeat = PC->Shoot();
				} while (repeat);
			}

			cout << "\n\n";
			system("pause");
			break;
		}
		case 2:
		{
			cout << "Continium game\n";
			break;
		}
		case 3:
		{
			return;
		}
		default:
			cout << "Incorrect value !\n";
			break;
		}
	}
}



#include "Header.h"

classPlayer::classPlayer(string newName, bool player) : Name(newName), isPlayer(player)
{
	Field = new int*[amountRows];

	for (int i = 0; i < amountRows; i++)
	{
		Field[i] = new int[amountColumns];
	}

	FeelField();
}

bool classPlayer::Shoot()
{
	bool result;

	if (isPlayer)
		result = this->PlayerShoot();
	else
		result = this->EnemyShoot();

	return result;
}

bool classPlayer::CheckFieldForShip(int HorisontalPos, int VerticalPos, int Arrow, int SheepFloorsAmount)
{
	bool isCanPlaced = true;

	switch (Arrow)
	{
	case 0:// left
	{
		if (HorisontalPos >= SheepFloorsAmount)// ���� ������� ����� ��������� �����
		{
			for (int i = VerticalPos - 1; i <= VerticalPos + 1; i++)// i = Y , j=X
			{
				if (i >= 0 && i <= amountRows - 1)// �� ������� �� ������� �������
				{
					for (int j = HorisontalPos - SheepFloorsAmount; j <= HorisontalPos + 1; j++)
					{
						if (j >= 0 && j <= amountColumns - 1)// �� ������� �� ������� �������
						{
							//cout << "i=" << i << "j=" << j << "\n";

							if (Field[i][j] == 1)
							{
								isCanPlaced = false;
							}
						}
					}
				}
			}
		}
		else
		{
			isCanPlaced = false;
		}
		break;
	}
	case 1://up
	{
		if (VerticalPos >= SheepFloorsAmount)// ���� ������� ����� ��������� �����
		{
			for (int i = VerticalPos - SheepFloorsAmount; i <= VerticalPos + 1; i++)// i = VerticalPos , j=X
			{
				if (i >= 0 && i <= amountRows - 1)// �� ������� �� ������� �������
				{
					for (int j = HorisontalPos - 1; j <= HorisontalPos + 1; j++)
					{
						if (j >= 0 && j <= amountColumns - 1)// �� ������� �� ������� �������
						{
							if (Field[i][j] == 1)
							{
								isCanPlaced = false;
							}
						}
					}
				}
			}
		}
		else
		{
			isCanPlaced = false;
		}
		break;
	}
	case 2://right
	{
		if (HorisontalPos - 1 + SheepFloorsAmount <= amountColumns)// ���� ������� ����� ��������� ������
		{
			for (int i = VerticalPos - 1; i <= VerticalPos + 1; i++)// i = VerticalPos , j=X
			{
				if (i >= 0 && i <= amountRows - 1)// �� ������� �� ������� �������
				{
					for (int j = HorisontalPos - 1; j <= HorisontalPos + SheepFloorsAmount; j++)
					{
						if (j >= 0 && j <= amountColumns - 1)// �� ������� �� ������� �������
						{
							if (Field[i][j] == 1)
							{
								isCanPlaced = false;
							}
						}
					}
				}
			}
		}
		else
		{
			isCanPlaced = false;
		}
		break;
	}
	case 3://down
	{
		if (VerticalPos - 1 + SheepFloorsAmount <= amountRows)// ���� ������� ����� ��������� ����
		{
			for (int i = VerticalPos - 1; i <= VerticalPos + SheepFloorsAmount; i++)// i = VerticalPos , j=X
			{
				if (i >= 0 && i <= amountRows - 1)// �� ������� �� ������� �������
				{
					for (int j = HorisontalPos - 1; j <= HorisontalPos + 1; j++)
					{
						if (j >= 0 && j <= amountColumns - 1)// �� ������� �� ������� �������
						{
							if (Field[i][j] == 1)
							{
								isCanPlaced = false;
							}
						}
					}
				}
			}
		}
		else
		{
			isCanPlaced = false;
		}
		break;
	}
	default:
		break;
	}
	return isCanPlaced;
}

bool classPlayer::PlayerShoot()
{
	system("cls");

	cout << "\n\n\n";
	DrawField(true);


	int RowNumber;
	int ColumnNumber;

	bool repeat = true;

	while (repeat)
	{
		cout << "\n\n";
		cout << "Shoot Row" << "  " << "Shoot Column" << "\n";
		cout << "Row" << "  ";
		cin >> RowNumber;
		cout << "Column" << "  ";
		cin >> ColumnNumber;
		cout << "\n";

		if (!(RowNumber >= 0 && RowNumber < amountRows) || !(ColumnNumber >= 0 && ColumnNumber < amountColumns))
		{
			cout << "repeat again";
		}
		else
		{
			switch (Field[RowNumber][ColumnNumber])
			{
			case 0:
			{
				Field[RowNumber][ColumnNumber] = 3; // ��� 0 - ������ ���� - ���������
				repeat = false;
				break;
			}
			case 1:
			{
				Field[RowNumber][ColumnNumber] = 2;// 1 - ������� - ������
				repeat = false;
				CheckDeath(RowNumber, ColumnNumber);
				return true;
				break;
			}
			default:
				break;
			}
		}
	}

	return false;
}


bool classPlayer::EnemyShoot()
{

	system("cls");

	cout << "\n\n\n";
	DrawField(true);


	int ShootRowNumber;
	int ShootColumnNumber;

	bool repeat = true;

	while (repeat)
	{
		bool repeatRandom = true;

		do
		{
			ShootRowNumber = rand() % amountRows;
			ShootColumnNumber = rand() % amountColumns;
			if (fieldEnemyShoot[ShootRowNumber][ShootColumnNumber] == 0)
			{
				repeatRandom = false;
			}

		} while (repeatRandom);

		cout << "\n" << "\n";
		cout << "ShootRowNumber  :" << ShootRowNumber << "  ShootColumnNumber  :" << ShootColumnNumber << "\n";


		if (!(ShootRowNumber > 0 && ShootRowNumber < amountRows) || !(ShootColumnNumber > 0 && ShootColumnNumber < amountColumns))
		{
			cout << "repeat again";
		}
		else
		{

			fieldEnemyShoot[ShootRowNumber][ShootColumnNumber] = 1; // ��� ������� � ������� ������� ���� ������

			switch (Field[ShootRowNumber][ShootColumnNumber])
			{
			case 0:
			{
				Field[ShootRowNumber][ShootColumnNumber] = 3; // ��� 0 - ������ ���� - ���������
				repeat = false;
				system("cls");
				DrawField(false);
				cout << "\n" << "\n";
				system("pause");
				break;
			}
			case 1:
			{
				Field[ShootRowNumber][ShootColumnNumber] = 2;// 1 - ������� - ������
				CheckDeath(ShootRowNumber, ShootColumnNumber);
				repeat = false;
				system("cls");
				DrawField(false);
				cout << "\n" << "\n";
				system("pause");
				return true;
				break;
			}
			default:
				break;
			}
		}
	}

	return false;


}
void classPlayer::FeelShip(int HorisontalPos, int VerticalPos, int Arrow, int SheepFloorsAmount)
{
	int Counter = 0;

	while (Counter < SheepFloorsAmount)
	{
		Counter += 1;

		Field[VerticalPos][HorisontalPos] = 1;
		switch (Arrow)
		{
		case 0:// left
		{
			HorisontalPos--;
			break;
		}
		case 1://up
		{
			VerticalPos--;
			break;
		}
		case 2://right
		{
			HorisontalPos++;
			break;
		}
		case 3://down
		{
			VerticalPos++;
			break;
		}
		default:
			break;
		}
	}

}
void classPlayer::FeelFieldPCshooting()
{
	for (int i = 0; i < amountRows; i++)
	{
		for (int j = 0; j < amountColumns; j++)
		{
			Field[i][j] = 0;
		}
	}
}
bool classPlayer::CheckSheeps()
{
	for (int i = 0; i < amountRows; i++)
	{
		for (int j = 0; j < amountColumns; j++)
		{
			if (Field[i][j] == 1)
				return true;
		}
	}
	return false;
}

bool classPlayer::CheckDeath(int RowsNum, int ColumnsNum)
{

	if ((RowsNum + 1) <= amountRows)	// no exit from fielsd
	{
		if (Field[RowsNum + 1][ColumnsNum] == 1 || Field[RowsNum + 1][ColumnsNum] == 2) // if nearest cell not have sheep
		{
			return VerticalSheep(RowsNum, ColumnsNum);
		}
	}


	if ((RowsNum - 1) > 0)	// no exit from fielsd
	{
		if (Field[RowsNum - 1][ColumnsNum] == 1 || Field[RowsNum - 1][ColumnsNum] == 2) // if nearest cell not have sheep
		{
			return VerticalSheep(RowsNum, ColumnsNum);
		}
	}


	if ((ColumnsNum + 1) <= amountColumns)
	{
		if (Field[RowsNum][ColumnsNum + 1] == 1 || Field[RowsNum][ColumnsNum + 1] == 2) // if nearest cell not have sheep
		{
			return HorisontalSheep(RowsNum, ColumnsNum);
		}
	}

	if (ColumnsNum - 1 > 0)
	{
		if (Field[RowsNum][ColumnsNum - 1] == 1 || Field[RowsNum][ColumnsNum - 1] == 2) // if nearest cell not have sheep
		{
			return HorisontalSheep(RowsNum, ColumnsNum);
		}
	}

	// ���� ����� ���� - � �������� ������� ������ �� ������� . ������ ������� ������������ � ����� ����������� ���� ������

	for (int i = (RowsNum - 1); i < (RowsNum + 2); i++)
	{
		if (i > 0 && i < amountRows)
		{
			for (int j = (ColumnsNum - 1); j < (ColumnsNum + 2); j++)
			{
				if (j > 0 && j < amountColumns)
				{
					if (i != RowsNum && j != ColumnsNum)
					{
						Field[i][j] = 3;
					}
				}
			}
		}
	}

	return true;
}
bool classPlayer::VerticalSheep(int RowsNum, int ColumnsNum)
{
	int FirstRow = 0;
	int LastRow = 0;

	bool isInField = true;
	bool isDead = false;
	int CurrentRowNum;



	//  ���� �� ��������� . ������ ������� � ����������� ������ �������� ��� ����� ������? ���� ���� - �� �������� �� ����� ���� ������
	// ���� ����� ������ ��� - �� ����� �������� �� ����� �� ������� � ����� ���������� ���, ��� �� ������������ ����
	CurrentRowNum = RowsNum - 1;

	if (CurrentRowNum > 0)
	{
		if (Field[CurrentRowNum][ColumnsNum] == 1)
		{
			isDead = false;
		}

		while (Field[CurrentRowNum][ColumnsNum] == 2 && isInField)// ���� ���� ����� ������ ������� ������  (up)
		{
			isDead = true;
			if ((ColumnsNum - 1) >= 0) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum][ColumnsNum - 1] = 3;
				Field[CurrentRowNum][ColumnsNum - 1] = 3;
			}
			if ((ColumnsNum + 1) < amountColumns) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum][ColumnsNum + 1] = 3;
				Field[CurrentRowNum][ColumnsNum + 1] = 3;
			}

			CurrentRowNum -= 1;
			if (CurrentRowNum <= 0)
			{
				isInField = false;
			}
		}
	}
	FirstRow = CurrentRowNum; // ��������� �������� CurrentRowNum ����� ���������� �� 2 � ���� ����� isDead - �� ��� ������ �����������

							  // ����� ��������� , ���� ����
	isInField = true;
	CurrentRowNum = RowsNum + 1;

	if (CurrentRowNum < amountRows)
	{
		if (Field[CurrentRowNum][ColumnsNum] == 1)
		{
			isDead = false;
		}

		while (Field[CurrentRowNum][ColumnsNum] == 2 && isInField)// ���� ���� ����� ������ ������� ������  (up)
		{
			isDead = true;
			if ((ColumnsNum - 1) >= 0) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum][ColumnsNum - 1] = 3;
				Field[CurrentRowNum][ColumnsNum - 1] = 3;
			}
			if ((ColumnsNum + 1) < amountColumns) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum][ColumnsNum + 1] = 3;
				Field[CurrentRowNum][ColumnsNum + 1] = 3;
			}
			CurrentRowNum += 1;
			if (CurrentRowNum >= amountRows)
			{
				isInField = false;
			}
		}
	}
	LastRow = CurrentRowNum;// ��������� �������� CurrentRowNum ����� ���������� �� 2 � ���� ����� isDead - �� ��� ������ �����������


	if (isDead)
	{
		cout << "    isDead    :" + isDead << "\n";
		system("pause");

		for (int i = ColumnsNum - 1; i < ColumnsNum + 2; i++)
		{
			if (i >= 0 && i < amountColumns)
			{
				Field[FirstRow][i] = 3;
				Field[LastRow][i] = 3;
			}
		}
	}
	return isDead;
}
bool classPlayer::HorisontalSheep(int RowsNum, int ColumnsNum)
{
	int FirstColumn = 0;
	int LastColumn = 0;

	bool isInField = true;
	bool isDead = false;
	int CurrentColumnNum;



	//  ���� �� ��������� . ������ ������� � ����������� ������ �������� ��� ����� ������? ���� ���� - �� �������� �� ����� ���� ������
	// ���� ����� ������ ��� - �� ����� �������� �� ����� �� ������� � ����� ���������� ���, ��� �� ������������ ����
	CurrentColumnNum = ColumnsNum - 1;

	if (CurrentColumnNum > 0)
	{
		if (Field[RowsNum][CurrentColumnNum] == 1)
		{
			isDead = false;
		}

		while (Field[RowsNum][CurrentColumnNum] == 2 && isInField)// ���� ���� ����� ������ ������� ������  (up)
		{
			isDead = true;
			if ((RowsNum - 1) >= 0) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum - 1][ColumnsNum] = 3;
				Field[RowsNum - 1][CurrentColumnNum] = 3;
			}
			if ((RowsNum + 1) < amountColumns) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum + 1][ColumnsNum] = 3;
				Field[RowsNum + 1][CurrentColumnNum] = 3;
			}

			CurrentColumnNum -= 1;
			if (CurrentColumnNum <= 0)
			{
				isInField = false;
			}
		}
	}
	FirstColumn = CurrentColumnNum; // ��������� �������� CurrentRowNum ����� ���������� �� 2 � ���� ����� isDead - �� ��� ������ �����������

									// ����� ��������� , ���� ����
	isInField = true;
	CurrentColumnNum = ColumnsNum + 1;

	if (CurrentColumnNum < amountColumns)
	{
		if (Field[RowsNum][CurrentColumnNum] == 1)
		{
			isDead = false;
		}

		while (Field[RowsNum][CurrentColumnNum] == 2 && isInField)// ���� ���� ����� ������ ������� ������  (up)
		{
			isDead = true;
			if ((RowsNum - 1) >= 0) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum - 1][ColumnsNum] = 3;
				Field[RowsNum - 1][CurrentColumnNum] = 3;
			}
			if ((ColumnsNum - 1) < amountColumns) // ����������� �������� ������ � ������� �������
			{
				Field[RowsNum + 1][ColumnsNum] = 3;
				Field[RowsNum + 1][CurrentColumnNum] = 3;
			}
			CurrentColumnNum += 1;
			if (CurrentColumnNum >= amountColumns)
			{
				isInField = false;
			}
		}
	}
	LastColumn = CurrentColumnNum;// ��������� �������� CurrentRowNum ����� ���������� �� 2 � ���� ����� isDead - �� ��� ������ �����������


	if (isDead)
	{
		for (int i = RowsNum - 1; i < RowsNum + 2; i++)
		{
			if (i >= 0 && i < amountRows)
			{
				Field[i][FirstColumn] = 3;
				Field[i][LastColumn] = 3;
			}
		}
	}
	return isDead;
}
void classPlayer::FeelField()
{
	int HorisontalPos; // X coordinate of field
	int VerticalPos; // VerticalPos coordinate of field
	int Arrow; // arrow ship
	int SheepFloorsAmount;
	int SheepCount = 0;

	// ������� ������ ������� �������� - ���� ���������
	SheepFloorsAmount = 4;
	while (SheepCount < 1)
	{
		SheepCount += 1;

		do // ���������� ���������� � ��������� ����� �� �� ���������� �������. ���� ��� ��������� ������� ���� �� ������� ���
		{
			HorisontalPos = rand() % amountRows;
			VerticalPos = rand() % amountColumns;
			Arrow = rand() % 3;
		} while (!CheckFieldForShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount));


		FeelShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount);
	}

	//��� ���� ��������� 
	SheepCount = 0;
	SheepFloorsAmount = 3;
	while (SheepCount < 2)
	{
		SheepCount += 1;

		do // ���������� ���������� � ��������� ����� �� �� ���������� �������. ���� ��� ��������� ������� ���� �� ������� ���
		{
			HorisontalPos = rand() % amountRows;
			VerticalPos = rand() % amountColumns;
			Arrow = rand() % 3;
		} while (!CheckFieldForShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount));;

		FeelShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount);
	}

	//��� ���� ���������
	SheepCount = 0;
	SheepFloorsAmount = 2;
	while (SheepCount < 3)
	{
		SheepCount += 1;

		do // ���������� ���������� � ��������� ����� �� �� ���������� �������. ���� ��� ��������� ������� ���� �� ������� ���
		{
			HorisontalPos = rand() % amountRows;
			VerticalPos = rand() % amountColumns;
			Arrow = rand() % 3;
		} while (!CheckFieldForShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount));

		FeelShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount);
	}

	//������ ������������
	SheepCount = 0;
	SheepFloorsAmount = 1;
	while (SheepCount < 4)
	{
		SheepCount += 1;

		do // ���������� ���������� � ��������� ����� �� �� ���������� �������. ���� ��� ��������� ������� ���� �� ������� ���
		{
			HorisontalPos = rand() % amountRows;
			VerticalPos = rand() % amountColumns;
			Arrow = rand() % 3;
		} while (!CheckFieldForShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount));

		FeelShip(HorisontalPos, VerticalPos, Arrow, SheepFloorsAmount);
	}

	// ������� ����������� - �������� ���������� ����

	for (int i = 0; i < amountRows; i++)
	{
		for (int j = 0; j < amountColumns; j++)
		{
			if (Field[i][j] != 1)
			{
				Field[i][j] = 0;
			}

		}
	}

	//  Draw Field for test

	for (int i = 0; i < amountRows; i++)
	{
		cout << "\n";
		for (int j = 0; j < amountColumns; j++)
		{
			cout << Field[i][j];
		}
	}
	cout << "\n";


}
void classPlayer::DrawCell(int& cell, bool isEnemy)
{
	switch (cell)
	{
	case 0: cout << " "; break;
	case 1: {
		if (isEnemy)
			cout << " ";
		else
			cout << "Z";
	} break;
	case 2: cout << "X"; break;
	case 3: cout << "*"; break;
	default:
		break;
	}
}
int classPlayer::DrawField(bool isEnemy)
{
	if (amountRows < 1 || amountColumns < 1)
		return 0;

	cout << "	" << Name << "\n\n";

	for (int i = 0; i < amountColumns; i++)
	{
		if (i == 0)
		{
			cout << "    ";
		}
		cout << i;
	}

	cout << "\n";

	for (int i = 0; i < amountColumns; i++)
	{
		if (i == 0)
		{
			cout << "    ";
		}
		cout << "-";
	}

	for (int i = 0; i < amountRows; i++)
	{
		cout << "\n";
		for (int j = 0; j < amountColumns; j++)
		{
			if (j == 0)
			{
				cout << " " << i << " |";
				DrawCell(Field[i][j], isEnemy);
			}
			else
			{
				if (j != amountColumns - 1)
				{
					DrawCell(Field[i][j], isEnemy);
				}
				else
				{
					DrawCell(Field[i][j], isEnemy);
					cout << "|";
				}
			}
		}
	}

	cout << "\n";

	for (int i = 0; i < amountColumns; i++)
	{
		if (i == 0)
		{
			cout << "    ";
		}
		cout << "-";
	}

	return 1;
}

classPlayer::~classPlayer()
{
	for (int i = 0; i < amountRows; i++)
	{
		delete[] Field[amountColumns];
	}
	delete[] Field;
}
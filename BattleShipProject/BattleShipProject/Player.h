#pragma once

using namespace std;

class classPlayer
{
private:
	/*DATA*/
	string Name;
	int** Field;
	const int amountRows = 10;
	const int amountColumns = 10;
	bool isPlayer;

	/*METHODS*/
	void FeelField();
	bool PlayerShoot();
	bool EnemyShoot();
	void DrawCell(int& cell, bool isEnemy);
	bool CheckFieldForShip(int HorisontalPos, int VerticalPos, int Arrow, int SheepFloorsAmount);
	void FeelShip(int HorisontalPos, int VerticalPos, int Arrow, int SheepFloorsAmount);
	bool CheckDeath(int RowsNum, int ColumnsNum);
	bool VerticalSheep(int RowsNum, int ColumnsNum);
	bool HorisontalSheep(int RowsNum, int ColumnsNum);
public:
	
	classPlayer(string newName, bool player);

	bool Shoot();	
	
	void FeelFieldPCshooting();	
	bool CheckSheeps();		
				
	int DrawField(bool isEnemy);	

	~classPlayer();
};



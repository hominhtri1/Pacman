#include "Game.h"
#include "Agent1.h"
#include "Environment1.h"
#include "Agent2.h"
#include "Environment2.h"
#include "Agent3.h"
#include "Environment3.h"
#include "Agent4.h"
#include "Environment4.h"

Game::Game()
{}

void Game::start()
{
	setColor(11);

	srand(time(NULL));

	int choice;

	cout << "Enter 1 to generate a random map" << endl;
	cout << "Enter 2 to test a level's algorithm" << endl;
	cout << "Enter: ";

	cin >> choice;
	cin.get();

	if (choice == 1)
		generateMap();
	else if (choice == 2)
		levelMenu();
}

void Game::generateMap()
{
	string mapName;

	system("cls");

	cout << "Enter the name of the map file:" << endl;
	getline(cin, mapName);

	string mapPath = "Map/" + mapName + ".txt";

	ofstream fout;
	fout.open(mapPath);

	int M, N;

	cout << endl;
	cout << "Enter M and N: ";
	cin >> M >> N;

	fout << M << " " << N << endl;

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			char ch;

			int rng = rand() % 100;

			if (rng < 65)
				ch = '0';
			else if (rng < 80)
				ch = '1';
			else if (rng < 97)
				ch = '2';
			else
				ch = '3';

			fout << ch << " ";
		}

		fout << endl;
	}

	int Px, Py;

	cout << endl;
	cout << "Enter x and y coordinates of Pac-man: ";
	cin >> Px >> Py;

	fout << Px << " " << Py << endl;

	fout.close();

	cout << endl;
	cout << "Done" << endl;
}

void Game::levelMenu()
{
	string mapName;

	system("cls");

	cout << "Enter the name of the map file:" << endl;
	getline(cin, mapName);

	string mapPath = "Map/" + mapName + ".txt";

	int choice;

	cout << endl;
	cout << "Enter 1 for level 1" << endl;
	cout << "Enter 2 for level 2" << endl;
	cout << "Enter 3 for level 3" << endl;
	cout << "Enter 4 for level 4" << endl;
	cout << "Enter: ";

	cin >> choice;
	cin.get();

	showConsoleCursor(false);
	system("cls");

	ifstream fin;
	fin.open(mapPath);

	fin >> M >> N;

	vector<vector<int>> tempMap(M, vector<int>(N));
	map = tempMap;

	monsterCount = 0;

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			fin >> map[i][j];

			if (map[i][j] == 3)
				monsterCount += 1;
		}
	}

	fin >> Px >> Py;

	map[Px][Py] = 4;

	fin.close();

	if (choice == 1)
		level1();
	else if (choice == 2)
		level2();
	else if (choice == 3)
		level3();
	else if (choice == 4)
		level4();
}

void Game::level1()
{
	Agent1 agent(map);

	Environment1 environment(map);

	draw(map);

	bool ok = false;

	while (true)
	{
		Pos curPos = agent.interact();

		bool ok = environment.interact(curPos);

		if (!ok)
			break;
	}
}

void Game::level2()
{
	Agent2 agent(map);

	Environment2 environment(map);

	draw(map);

	bool ok = false;

	while (true)
	{
		Pos curPos = agent.interact();

		bool ok = environment.interact(curPos);

		if (!ok)
			break;
	}
}

void Game::level3()
{
	Agent3 agent(M, N, Px, Py, monsterCount);

	Environment3 environment(map);

	vector<vector<int>> vision = environment.curVision();
	environment.drawVision(vision);

	vector<Pos> monsterPos = environment.curMonsterPos();

	bool ok = false;

	ofstream fout;
	fout.open("Log/log.txt");

	while (true)
	{
		Pos curPos = agent.interact(vision, monsterPos, fout);

		bool ok = environment.interact(curPos, vision, monsterPos);

		if (!ok)
			break;
	}

	fout.close();
}

void Game::level4()
{
	Agent4 agent(map, monsterCount);

	Environment4 environment(map);

	environment.drawMonsters();

	vector<Pos> monsterPos = environment.curMonsterPos();

	bool ok = false;

	ofstream fout;
	fout.open("Log/log.txt");

	while (true)
	{
		Pos curPos = agent.interact(monsterPos, fout);

		bool ok = environment.interact(curPos, monsterPos);

		if (!ok)
			break;
	}

	fout.close();
}
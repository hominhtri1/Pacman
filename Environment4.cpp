#include "Environment4.h"
#include "Monster4.h"

Environment4::Environment4(vector<vector<int>> map)
{
	this->map = map;

	M = map.size();
	N = map[0].size();

	foodCount = 0;
	int monsterId = 0;

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (map[i][j] == 4)
			{
				Px = i;
				Py = j;
			}

			if (map[i][j] == 2)
				foodCount += 1;

			if (map[i][j] == 3)
			{
				Monster4* curMonster = new Monster4(map, i, j);
				monsterId += 1;

				monsters.push_back(curMonster);

				this->map[i][j] = 0;
			}
		}
	}
}

bool Environment4::interact(Pos curPos, vector<Pos> & outMonsterPos)
{
	if (curPos.x == -1)
		return false;

	score -= 1;

	if (map[curPos.x][curPos.y] == 2)
		score += 20;

	if (map[curPos.x][curPos.y] == 2)
		foodCount -= 1;

	map[Px][Py] = 0;
	map[curPos.x][curPos.y] = 4;

	Px = curPos.x;
	Py = curPos.y;

	for (int i = 0; i < monsters.size(); ++i)
	{
		Pos monsterCurPos = monsters[i]->getPos();
		Pos monsterNewPos = monsters[i]->interact(Px, Py);

		if (monsterNewPos.x == curPos.x && monsterNewPos.y == curPos.y)
		{
			cout << "You are dead" << endl;

			return false;
		}
	}

	outMonsterPos = curMonsterPos();

	drawMonsters();

	return true;
}

void Environment4::drawMonsters()
{
	vector<vector<int>> tempMap = map;

	for (int i = 0; i < monsters.size(); ++i)
	{
		Pos monsterCurPos = monsters[i]->getPos();

		tempMap[monsterCurPos.x][monsterCurPos.y] = 3;
	}

	draw(tempMap, score);
}

vector<Pos> Environment4::curMonsterPos()
{
	vector<Pos> monsterPos(monsters.size());

	for (int i = 0; i < monsters.size(); ++i)
	{
		Pos monsterCurPos = monsters[i]->getPos();

		monsterPos[i] = monsterCurPos;
	}

	return monsterPos;
}

Environment4::~Environment4()
{
	for (int i = 0; i < monsters.size(); ++i)
		delete monsters[i];
}
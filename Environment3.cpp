#include "Environment3.h"
#include "Monster3.h"

Environment3::Environment3(vector<vector<int>> map)
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
				Monster3* curMonster = new Monster3(map, i, j, monsterId);
				monsterId += 1;

				monsters.push_back(curMonster);
			}
		}
	}
}

bool Environment3::interact(Pos curPos, vector<vector<int>> & outVision, vector<Pos> & outMonsterPos)
{
	if (curPos.x == -1)
		return false;

	if (map[curPos.x][curPos.y] == 2)
		foodCount -= 1;

	map[Px][Py] = 0;
	map[curPos.x][curPos.y] = 4;

	Px = curPos.x;
	Py = curPos.y;

	vector<Pos> monsterPos;
	for (int i = 0; i < monsters.size(); ++i)
		monsterPos.push_back(monsters[i]->getPos());

	for (int i = 0; i < monsters.size(); ++i)
	{
		Pos monsterCurPos = monsters[i]->getPos();
		Pos monsterNewPos = monsters[i]->interact(monsterPos);

		if (monsterNewPos.x == curPos.x && monsterNewPos.y == curPos.y)
			return false;

		map[monsterCurPos.x][monsterCurPos.y] = 0;
		map[monsterNewPos.x][monsterNewPos.y] = 3;

		monsterPos[i] = monsterNewPos;
	}

	outVision = curVision();
	outMonsterPos = curMonsterPos();

	// this->draw();
	this->drawVision(outVision);

	return true;
}

void Environment3::drawVision(vector<vector<int>> & vision)
{
	gotoXY(0, 0);

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (abs(i - Px) <= visionSize && abs(j - Py) <= visionSize)
				drawTile(map[i][j]);
			else
				cout << "  ";
		}

		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < visionSize * 2 + 1; ++i)
	{
		for (int j = 0; j < visionSize * 2 + 1; ++j)
			drawTile(vision[i][j]);

		cout << endl;
	}

	cout << endl;

	cout << setw(2) << foodCount << endl;

	cin.get();
}

vector<vector<int>> Environment3::curVision()
{
	vector<vector<int>> vision(visionSize * 2 + 1, vector<int>(visionSize * 2 + 1));

	for (int i = -visionSize; i <= visionSize; ++i)
	{
		for (int j = -visionSize; j <= visionSize; ++j)
		{
			int cur_x = Px + i;
			int cur_y = Py + j;

			int value = 5;

			if (cur_x >= 0 && cur_x < M && cur_y >= 0 && cur_y < N)
				value = map[cur_x][cur_y];

			vision[visionSize + i][visionSize + j] = value;
		}
	}

	return vision;
}

vector<Pos> Environment3::curMonsterPos()
{
	vector<Pos> monsterPos(monsters.size());

	for (int i = 0; i < monsters.size(); ++i)
	{
		Pos monsterCurPos = monsters[i]->getPos();

		if (abs(Px - monsterCurPos.x) > visionSize || abs(Py - monsterCurPos.y) > visionSize)
			continue;

		monsterPos[i] = monsterCurPos;
	}

	return monsterPos;
}

Environment3::~Environment3()
{
	for (int i = 0; i < monsters.size(); ++i)
		delete monsters[i];
}
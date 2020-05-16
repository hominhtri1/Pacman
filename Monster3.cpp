#include "Monster3.h"

Monster3::Monster3(vector<vector<int>> map, int Mx, int My, int id)
{
	this->map = map;

	M = map.size();
	N = map[0].size();

	start_x = Mx;
	start_y = My;

	cur_x = start_x;
	cur_y = start_y;

	this->id = id;
}

Pos Monster3::interact(vector<Pos> & monsterPos)
{
	vector<int> dx = { -1, 0, 1, 0 };
	vector<int> dy = { 0, 1, 0, -1 };

	vector<Pos> possiblePos;

	possiblePos.push_back(Pos(cur_x, cur_y));

	for (int i = 0; i < 4; ++i)
	{
		int new_x = cur_x + dx[i];
		int new_y = cur_y + dy[i];

		if (new_x < 0 || new_x >= M || new_y < 0 || new_y >= N)
			continue;

		if (abs(new_x - start_x) > monsterRange || abs(new_y - start_y) > monsterRange)
			continue;

		if (map[new_x][new_y] == 1 || map[new_x][new_y] == 2)
			continue;

		bool collideMonster = false;

		for (int j = 0; j < monsterPos.size(); ++j)
		{
			if (j == id)
				continue;
			
			if (new_x == monsterPos[j].x && new_y == monsterPos[j].y)
				collideMonster = true;
		}

		if (collideMonster)
			continue;

		possiblePos.push_back(Pos(new_x, new_y));
	}

	int numPossible = possiblePos.size();

	int choice = rand() % numPossible;
	Pos choicePos = possiblePos[choice];

	cur_x = choicePos.x;
	cur_y = choicePos.y;

	return choicePos;
}

Pos Monster3::getPos()
{
	return Pos(cur_x, cur_y);
}
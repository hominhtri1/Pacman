#include "Monster4.h"

Monster4::Monster4(vector<vector<int>> map, int Mx, int My)
{
	this->map = map;

	M = map.size();
	N = map[0].size();

	x = Mx;
	y = My;
}

int Monster4::distanceToAgent(int x, int y)
{
	return abs(x - Px) + abs(y - Py);
}

vector<int> Monster4::posWeightDist(vector<Pos> & possiblePos)
{
	int numPos = possiblePos.size();

	vector<int> posDistance(numPos);

	int minDistance = M + N;

	for (int i = 0; i < numPos; ++i)
	{
		Pos curPos = possiblePos[i];

		posDistance[i] = distanceToAgent(curPos.x, curPos.y);

		if (posDistance[i] < minDistance)
			minDistance = posDistance[i];
	}

	vector<int> posWeight(numPos);

	for (int i = 0; i < numPos; ++i)
	{
		int posDistanceType = posDistance[i] - minDistance;

		posWeight[i] = distanceTypeWeight[posDistanceType];
	}

	return posWeight;
}

int Monster4::weightedChoice(vector<int> & posWeight)
{
	int numPos = posWeight.size();
	
	int sum = 0;

	for (int i = 0; i < numPos; ++i)
		sum += posWeight[i];

	int rng = rand() % sum;

	int i = 0;

	while (rng >= posWeight[i])
	{
		rng -= posWeight[i];

		i += 1;
	}

	return i;
}

Pos Monster4::interact(int cur_Px, int cur_Py)
{
	map[Px][Py] = 0;
	map[cur_Px][cur_Py] = 4;
	
	Px = cur_Px;
	Py = cur_Py;

	vector<int> dx = { 0, -1, 0, 1, 0 };
	vector<int> dy = { 0, 0, 1, 0, -1 };

	vector<Pos> possiblePos;

	for (int i = 0; i < 5; ++i)
	{
		int new_x = x + dx[i];
		int new_y = y + dy[i];

		if (new_x < 0 || new_x >= M || new_y < 0 || new_y >= N)
			continue;

		if (map[new_x][new_y] == 1)
			continue;

		possiblePos.push_back(Pos(new_x, new_y));
	}

	vector<int> posWeight = posWeightDist(possiblePos);

	int choice = weightedChoice(posWeight);

	Pos choicePos = possiblePos[choice];

	x = choicePos.x;
	y = choicePos.y;

	return choicePos;
}

Pos Monster4::getPos()
{
	return Pos(x, y);
}
#include "Agent3.h"

Agent3::Agent3(int M, int N, int Px, int Py, int monsterCount)
{
	this->M = M;
	this->N = N;

	this->Px = Px;
	this->Py = Py;

	vector<vector<int>> tempMap(M, vector<int>(N, 5));
	tempMap[Px][Py] = 0;
	map = tempMap;

	path = vector<Pos>(0);
	path_i = path.size();

	monsterPos = vector<Pos>(monsterCount);
}

vector<Pos> Agent3::buildPath(vector<vector<Pos>> & prev, int end_x, int end_y)
{
	vector<Pos> curPath;

	int cur_x = end_x;
	int cur_y = end_y;

	while (true)
	{
		if (cur_x == Px && cur_y == Py)
			break;

		curPath.push_back(Pos(cur_x, cur_y));

		Pos prevPos = prev[cur_x][cur_y];
		cur_x = prevPos.x;
		cur_y = prevPos.y;
	}

	int size = curPath.size();

	vector<Pos> outPath(size);

	for (int i = 0; i < size; ++i)
	{
		outPath[i] = curPath[size - i - 1];
	}

	return outPath;
}

bool Agent3::BFSGoal(int x, int y)
{
	if (map[x][y] == 2)
		return true;

	bool atVisionEdge = false;

	for (int i = -visionSize; i <= visionSize; ++i)
	{
		for (int j = -visionSize; j <= visionSize; ++j)
		{
			int cur_x = x + i;
			int cur_y = y + j;

			if (cur_x >= 0 && cur_x < M && cur_y >= 0 && cur_y < N)
			{
				if (map[cur_x][cur_y] == 5)
					atVisionEdge = true;
			}
		}
	}

	return atVisionEdge;
}

bool Agent3::adjacentMonster(int x, int y, int relaxedLevel)
{
	if (relaxedLevel == 2)
		return false;
	
	if (relaxedLevel == 1)
	{
		if (abs(x - Px) > visionSize || abs(y - Py) > visionSize)
			return false;
	}
	
	vector<int> dx2 = { 0, -1, 0, 1, 0 };
	vector<int> dy2 = { 0, 0, 1, 0, -1 };

	for (int i = 0; i < 5; ++i)
	{
		int adjacent_x = x + dx2[i];
		int adjacent_y = y + dy2[i];

		if (adjacent_x < 0 || adjacent_x >= M || adjacent_y < 0 || adjacent_y >= N)
			continue;

		for (int i = 0; i < monsterPos.size(); ++i)
		{
			Pos monsterCurPos = monsterPos[i];

			if (monsterCurPos.x == -1 && monsterCurPos.y == -1)
				continue;

			if (adjacent_x == monsterCurPos.x && adjacent_y == monsterCurPos.y)
				return true;
		}
	}

	return false;
}

void Agent3::findPathWithBFS(int relaxedLevel)
{
	vector<Pos> tempPath;

	vector<int> dx = { -1, 0, 1, 0 };
	vector<int> dy = { 0, 1, 0, -1 };

	vector<vector<Pos>> prev(M, vector<Pos>(N));

	deque<Pos> D;

	D.push_back(Pos(Px, Py));
	prev[Px][Py] = Pos(-2, -2);

	while (D.size() > 0)
	{
		Pos curPos = D.front();
		D.pop_front();

		if (BFSGoal(curPos.x, curPos.y))
		{
			tempPath = buildPath(prev, curPos.x, curPos.y);
			break;
		}

		for (int i = 0; i < 4; ++i)
		{
			int new_x = curPos.x + dx[i];
			int new_y = curPos.y + dy[i];

			if (new_x < 0 || new_x >= M || new_y < 0 || new_y >= N)
				continue;

			if (map[new_x][new_y] == 1)
				continue;

			if (adjacentMonster(new_x, new_y, relaxedLevel))
				continue;

			if (prev[new_x][new_y].x != -1 && prev[new_x][new_y].y != -1)
				continue;

			D.push_back(Pos(new_x, new_y));
			prev[new_x][new_y] = Pos(curPos);
		}
	}

	path = tempPath;
}

Pos Agent3::interact(vector<vector<int>> vision, vector<Pos> visionMonsterPos, ofstream & fout)
{
	updateState(vision, visionMonsterPos);
	
	if (path_i == path.size() || adjacentMonster(path[path_i].x, path[path_i].y, false))
	{
		findPathWithBFS(0);

		printPath(fout);

		if (path.size() == 0)
		{
			findPathWithBFS(1);

			printPath(fout);

			if (path.size() == 0)
			{
				findPathWithBFS(2);

				if (path.size() == 0)
					return Pos(-1, -1);

				vector<Pos> tempPath;
				path = tempPath;

				path_i = 0;

				return Pos(Px, Py);
			}
		}

		path_i = 0;
	}

	Pos curPos = path[path_i];
	path_i += 1;

	Px = curPos.x;
	Py = curPos.y;

	map[Px][Py] = 0;

	return curPos;
}

void Agent3::updateState(vector<vector<int>> & vision, vector<Pos> & visionMonsterPos)
{
	for (int i = -visionSize; i <= visionSize; ++i)
	{
		for (int j = -visionSize; j <= visionSize; ++j)
		{
			if (vision[visionSize + i][visionSize + j] == 5)
				continue;

			int cur_x = Px + i;
			int cur_y = Py + j;

			if (vision[visionSize + i][visionSize + j] == 3 || vision[visionSize + i][visionSize + j] == 4)
				map[cur_x][cur_y] = 0;
			else
				map[cur_x][cur_y] = vision[visionSize + i][visionSize + j];
		}
	}

	
	for (int i = 0; i < visionMonsterPos.size(); ++i)
	{
		Pos monsterCurPos = visionMonsterPos[i];

		if (monsterCurPos.x == -1 && monsterCurPos.y == -1)
			continue;

		monsterPos[i] = visionMonsterPos[i];
	}
	
}

void Agent3::printPath(ofstream & fout)
{
	fout << path.size() << endl;

	for (int i = 0; i < path.size(); ++i)
		fout << path[i].x << " " << path[i].y << endl;

	fout << endl;
}
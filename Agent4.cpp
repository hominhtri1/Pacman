#include "Agent4.h"

Agent4::Agent4(vector<vector<int>> map, int monsterCount)
{
	this->map = map;

	M = map.size();
	N = map[0].size();

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (map[i][j] == 4)
			{
				Px = i;
				Py = j;
			}
		}
	}

	path = vector<Pos>(0);
	path_i = path.size();

	monsterPos = vector<Pos>(monsterCount);
}

vector<Pos> Agent4::buildPath(vector<vector<Pos>> & prev, int end_x, int end_y)
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

bool Agent4::adjacentMonster(int x, int y, int relaxedLevel)
{
	if (relaxedLevel == 1)
		return false;
	
	vector<int> dx2 = { 0, -1, 0, 1, 0 };
	vector<int> dy2 = { 0, 0, 1, 0, -1 };

	if (relaxedLevel == 2)
	{
		dx2 = { 0 };
		dy2 = { 0 };
	}

	for (int i = 0; i < dx2.size(); ++i)
	{
		int adjacent_x = x + dx2[i];
		int adjacent_y = y + dy2[i];

		if (adjacent_x < 0 || adjacent_x >= M || adjacent_y < 0 || adjacent_y >= N)
			continue;

		for (int i = 0; i < monsterPos.size(); ++i)
		{
			Pos monsterCurPos = monsterPos[i];

			if (adjacent_x == monsterCurPos.x && adjacent_y == monsterCurPos.y)
				return true;
		}
	}

	return false;
}

void Agent4::findPathWithBFS(int relaxedLevel)
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

		if (map[curPos.x][curPos.y] == 2)
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

void Agent4::findSafePath()
{
	vector<Pos> tempPath;

	vector<Pos> possiblePos;
	
	vector<int> dx2 = { 0, -1, 0, 1, 0 };
	vector<int> dy2 = { 0, 0, 1, 0, -1 };

	bool found = false;

	for (int i = 0; i < 5; ++i)
	{
		int adjacent_x = Px + dx2[i];
		int adjacent_y = Py + dy2[i];

		if (adjacent_x < 0 || adjacent_x >= M || adjacent_y < 0 || adjacent_y >= N)
			continue;

		if (map[adjacent_x][adjacent_y] == 1)
			continue;

		if (!adjacentMonster(adjacent_x, adjacent_y, 2))
			possiblePos.push_back(Pos(adjacent_x, adjacent_y));

		if (!adjacentMonster(adjacent_x, adjacent_y, 0))
		{
			tempPath.push_back(Pos(adjacent_x, adjacent_y));

			found = true;

			break;
		}
	}

	if (!found)
	{
		int numPossible = possiblePos.size();

		int choice = rand() % numPossible;
		Pos choicePos = possiblePos[choice];

		tempPath.push_back(choicePos);
	}

	path = tempPath;
}

Pos Agent4::interact(vector<Pos> inMonsterPos, ofstream & fout)
{
	monsterPos = inMonsterPos;

	if (path_i == path.size() || adjacentMonster(path[path_i].x, path[path_i].y, 0))
	{
		findPathWithBFS(0);

		printPath(fout);

		if (path.size() == 0)
		{
			findPathWithBFS(1);

			if (path.size() == 0)
				return Pos(-1, -1);

			vector<Pos> tempPath;
			path = tempPath;

			path_i = 0;

			findSafePath();

			printPath(fout);
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

void Agent4::printPath(ofstream & fout)
{
	fout << path.size() << endl;

	for (int i = 0; i < path.size(); ++i)
		fout << path[i].x << " " << path[i].y << endl;

	fout << endl;
}
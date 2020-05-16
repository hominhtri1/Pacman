#include "Agent1.h"

Agent1::Agent1(vector<vector<int>> map)
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

	findPathWithBFS();

	path_i = 0;
}

vector<Pos> Agent1::buildPath(vector<vector<Pos>> & prev, int end_x, int end_y)
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

void Agent1::findPathWithBFS()
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

			if (prev[new_x][new_y].x != -1 && prev[new_x][new_y].y != -1)
				continue;

			D.push_back(Pos(new_x, new_y));
			prev[new_x][new_y] = Pos(curPos);
		}
	}

	path = tempPath;
}

Pos Agent1::interact()
{
	if (path_i == path.size())
		return Pos(-1, -1);

	Pos curPos = path[path_i];
	path_i += 1;

	return curPos;
}
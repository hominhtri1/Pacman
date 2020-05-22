#include "Environment2.h"

Environment2::Environment2(vector<vector<int>> map)
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
}

bool Environment2::interact(Pos curPos)
{
	if (curPos.x == -1)
		return false;

	map[Px][Py] = 0;
	map[curPos.x][curPos.y] = 4;

	Px = curPos.x;
	Py = curPos.y;

	draw(map);

	return true;
}
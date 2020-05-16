#ifndef _AGENT3_H_
#define _AGENT3_H_

#include "Header.h"

class Agent3
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	vector<Pos> path;

	int path_i;

	vector<Pos> monsterPos;

	vector<Pos> buildPath(vector<vector<Pos>> & prev, int end_x, int end_y);

	bool BFSGoal(int x, int y);

	bool adjacentMonster(int x, int y, int relaxedLevel);

	void findPathWithBFS(int relaxedLevel);

	void updateState(vector<vector<int>> & vision, vector<Pos> & visionMonsterPos);

	void printPath(ofstream & fout);

public:
	Agent3(int M, int N, int Px, int Py, int monsterCount);

	Pos interact(vector<vector<int>> vision, vector<Pos> visionMonsterPos, ofstream & fout);

};

#endif
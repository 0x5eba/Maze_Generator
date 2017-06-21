#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <Windows.h>


class Maze {
public: 
	Maze() {};
	~Maze() {};
	void initialize();

private:
	struct Cell
	{
		int x, y;
		bool walls[4] = { true, true, true, true };
		bool visited;
		bool solve;
	};

private:
	Cell checkNeightbors(const int& a, const int& b);
	void drawLines(const int& a, const int& b, bool path);
	void setup();
	void draw(bool path);
	void removeWall(Cell& current, Cell& next);

private:
	std::vector<std::vector<Cell>> grid;
	std::vector<Cell> stack;
	Cell current;

	std::vector<int> distance;
	int cols;
	int rows;
	bool pop;
	bool reached;

private:
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
};

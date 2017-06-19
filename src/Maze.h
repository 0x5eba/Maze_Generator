#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>


class Maze {
public: 
	Maze() {};
	~Maze() {};
	void setup();

private:
	struct Cell
	{
		int x, y;
		bool walls[4] = { true, true, true, true };
		bool visited;
		int numb;
	};


	Cell checkNeightbors(const int& a, const int& b);
	void drawLines(const int& a, const int& b);
	void draw();
	void removeWall(Cell& current, Cell& next);
	


	Cell* grid[40][40]{};
	Cell current{};
	std::vector<Cell> stack{};

	const int w = 40;
	const int cols = 400 / w;
	const int rows = 400 / w;
	bool pop;

	int conta = 1;	
};
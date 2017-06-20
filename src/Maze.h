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
	};


	Cell checkNeightbors(const int& a, const int& b);
	void drawLines(const int& a, const int& b);
	void draw();
	void removeWall(Cell& current, Cell& next);
	
	std::vector<std::vector<Cell>> grid;
	std::vector<Cell> stack;
	Cell current;
	

	
	const int cols = 20;
	const int rows = 20;
	bool pop;	
};

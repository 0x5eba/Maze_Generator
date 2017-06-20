#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>


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
	void drawLines(const int& a, const int& b);
	void setup();
	void draw();
	void removeWall(Cell& current, Cell& next);

private:
	std::vector<std::vector<Cell>> grid;
	std::vector<Cell> stack;
	Cell current;

	int cols;
	int rows;
	bool pop;
	bool reached;
	int coordinateX, coordinateY;	
};

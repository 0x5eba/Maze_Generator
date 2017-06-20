#pragma once
#include "Maze.h"

void Maze::initialize()
{
	reached = false;
	do {
		do {
			std::cout << "\nInsert a number of total rows: ";
			std::cin >> Maze::rows;
			if (Maze::rows < 0 || Maze::rows > 45)
				std::cout << "\nInsert a number between 0 and 45\n";
		} while (Maze::rows < 0 || Maze::rows > 45);

		do
		{
			std::cout << "Insert a number of total columns: ";
			std::cin >> Maze::cols;
			if (Maze::cols < 0 || Maze::cols > 45)
				std::cout << "\nInsert a number between 0 and 45\n";
		} while (Maze::cols < 0 || Maze::cols > 45);

		if (Maze::rows != Maze::cols)
			std::cout << "\nInsert 2 equal numbers\n\n";
	} while (Maze::rows != Maze::cols);

	coordinateX = cols - 1;
	coordinateY = rows - 1;
	Maze::setup();
}

void Maze::setup()
{
	grid.resize(rows, std::vector<Maze::Cell>(cols));
	for (int a = 0; a < rows; a++)
	{
		for (int b = 0; b < cols; b++)
		{
			grid[a][b] = { a, b,{ true, true, true, true }, false, false };
		}
	}

	current = grid[0][0];
	grid[0][0].visited = true;
	grid[0][0].solve = true;

	int a = current.x, b = current.y;
	stack.push_back(current);

	do
	{
		//Step 1
		Cell next = checkNeightbors(a, b);
		a = next.x;
		b = next.y;
		grid[a][b].visited = true;
		
		if (!pop)
		{
			if (reached == false)
				grid[a][b].solve = true;	
			if (a == coordinateX && b == coordinateY)
				reached = true;

			//Step 2
			stack.push_back(current);

			//Step 3
			removeWall(current, next);

			//Step 4
			current = next;
			
		}
		else {
			if (reached == false)
				grid[a][b].solve = false;

			current = stack[stack.size() - 1];
			a = current.x;
			b = current.y;

			if (reached == false)
				grid[a][b].solve = false;

			stack.pop_back();
		}
	} while (stack.size() > 0);

	draw();
}

void Maze::drawLines(const int& a, const int& b)
{
	if (grid[a][b].visited)
	{
		if (grid[a][b].walls[1])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b].walls[0])
		{
			std::cout << "^";
		}
		else
		{
			std::cout << " ";
		}

		
		if (grid[a][b].solve)
		{
			std::cout << "*";
		}
		else {
			std::cout << " ";
		}


		if (grid[a][b].walls[2])
		{
			std::cout << "_";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b].walls[3])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
	}
	else
	{
		if (grid[a][b].walls[1])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b].walls[0])
		{
			std::cout << "^";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b].walls[2])
		{
			std::cout << "_";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b].walls[3])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
	}
}

void Maze::draw()
{
	for (int a = 0; a < rows; ++a)
	{
		for (int b = 0; b < cols; ++b)
		{
			drawLines(a, b);
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

Maze::Cell Maze::checkNeightbors(const int& a, const int& b)
{
	std::vector<int> arrToRandomNumber(4);

	if (b > 0 && !grid[a][b - 1].visited)
	{
		arrToRandomNumber[0] = 0;
	}
	else
	{
		arrToRandomNumber[0] = -1;
	}

	if (a + 1 < cols && !grid[a + 1][b].visited)
	{
		arrToRandomNumber[1] = 1;
	}
	else
	{
		arrToRandomNumber[1] = -1;
	}

	if (b + 1  < rows && !grid[a][b + 1].visited)
	{
		arrToRandomNumber[2] = 2;
	}
	else
	{
		arrToRandomNumber[2] = -1;
	}

	if (a > 0 && !grid[a - 1][b].visited)
	{
		arrToRandomNumber[3] = 3;
	}
	else
	{
		arrToRandomNumber[3] = -1;
	}


	int contameno1 = 0;
	for (int a = 0; a < arrToRandomNumber.size(); ++a)
	{
		if (arrToRandomNumber[a] == -1)
			contameno1++;
	}
	int random_element = -1;
	if (arrToRandomNumber.size() > 0 && contameno1 < 4)
	{
		do {
			std::random_device random_device;
			std::mt19937 engine{ random_device() };
			std::uniform_int_distribution<int> dist(0, 3);
			random_element = arrToRandomNumber[dist(engine)];
		} while (random_element == -1);

		pop = false;

		if (random_element == 0)
		{
			grid[a][b - 1].visited = true;
			return grid[a][b - 1];
		}
		else if (random_element == 1)
		{
			grid[a + 1][b].visited = true;
			return grid[a + 1][b];
		}
		else if (random_element == 2)
		{
			grid[a][b + 1].visited = true;
			return grid[a][b + 1];
		}
		else if (random_element == 3)
		{
			grid[a - 1][b].visited = true;
			return grid[a - 1][b];
		}
	}
	else {
		if (stack.size() > 0)
			pop = true;
	}
}

void Maze::removeWall(Maze::Cell& current, Maze::Cell& next)
{
	int asseY = current.x - next.x;
	if (asseY == 1)
	{
		grid[current.x][current.y].walls[0] = false;
		grid[next.x][next.y].walls[2] = false;
	}
	else if (asseY == -1)
	{
		grid[current.x][current.y].walls[2] = false;
		grid[next.x][next.y].walls[0] = false;
	}

	int asseX = current.y - next.y;
	if (asseX == 1)
	{
		grid[current.x][current.y].walls[1] = false;
		grid[next.x][next.y].walls[3] = false;
	}
	else if (asseX == -1)
	{
		grid[current.x][current.y].walls[3] = false;
		grid[next.x][next.y].walls[1] = false;
	}
}

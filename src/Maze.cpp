#pragma once
#include "Maze.h"

void Maze::setup()
{
	for (int a = 0; a < rows; a++)
	{
		for (int b = 0; b < cols; b++)
		{
			grid[a][b] = new Cell{ a, b,{ true, true, true, true }, false };
			if (a == 0 && b == 0)
			{
				current = *grid[a][b];
				continue;
			}
		}
	}

	int a = current.x, b = current.y;
	stack.push_back(current);
	do
	{
		//Step 1
		Cell next = checkNeightbors(a, b);
		a = next.x;
		b = next.y;
		grid[a][b]->visited = true;
		if (!pop)
		{
			//Step 2
			stack.push_back(current);

			//Step 3
			removeWall(current, next);

			//Step 4
			current = next;
		}
		else {
			current = stack[stack.size() - 1];
			a = current.x;
			b = current.y;
			stack.pop_back();
		}
		draw();
	} while (stack.size() > 0);
}

void Maze::drawLines(const int& a, const int& b)
{
	if (grid[a][b]->visited)
	{
		if (grid[a][b]->walls[1])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b]->walls[0])
		{
			std::cout << "^";
		}
		else
		{
			std::cout << " ";
		}

		/*if (grid[a][b]->numb > 9)
		{
		std::cout << grid[a][b]->numb;
		if (grid[a][b]->walls[2])
		{
		std::cout << "_";
		}
		else {
		std::cout << " ";
		}
		}
		else {
		std::cout << grid[a][b]->numb;
		if (grid[a][b]->walls[2])
		{
		std::cout << "_";
		}
		else {
		std::cout << " ";
		}
		}*/

		std::cout << "*";
		if (grid[a][b]->walls[2])
		{
			std::cout << "_";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b]->walls[3])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
	}
	else
	{
		if (grid[a][b]->walls[1])
		{
			std::cout << "|";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b]->walls[0])
		{
			std::cout << "^";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b]->walls[2])
		{
			std::cout << "_";
		}
		else {
			std::cout << " ";
		}
		if (grid[a][b]->walls[3])
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
	//system("pause");
}

Maze::Cell Maze::checkNeightbors(const int& a, const int& b)
{
	//neighbors
	std::vector<int> arrToRandomNumber(4);

	if (b - 1 > 0 && !grid[a][b - 1]->visited)
	{
		arrToRandomNumber[0] = 0;
	}
	else
	{
		arrToRandomNumber[0] = -1;
	}

	if (a + 1 < cols && !grid[a + 1][b]->visited)
	{
		arrToRandomNumber[1] = 1;
	}
	else
	{
		arrToRandomNumber[1] = -1;
	}

	if (b + 1 < rows && !grid[a][b + 1]->visited)
	{
		arrToRandomNumber[2] = 2;
	}
	else
	{
		arrToRandomNumber[2] = -1;
	}

	if (a - 1 > 0 && !grid[a - 1][b]->visited)
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

		conta++;
		pop = false;

		if (random_element == 0)
		{
			grid[a][b - 1]->visited = true;
			grid[a][b - 1]->numb = conta;
			return *grid[a][b - 1];
		}
		else if (random_element == 1)
		{
			grid[a + 1][b]->visited = true;
			grid[a + 1][b]->numb = conta;
			return *grid[a + 1][b];
		}
		else if (random_element == 2)
		{
			grid[a][b + 1]->visited = true;
			grid[a][b + 1]->numb = conta;
			return *grid[a][b + 1];
		}
		else if (random_element == 3)
		{
			grid[a - 1][b]->visited = true;
			grid[a - 1][b]->numb = conta;
			return *grid[a - 1][b];
		}
	}
	else {
		if (stack.size() > 0)
		{
			pop = true;
		}
		else {
			std::cout << "\n\nFINISH\n\n";
		}
	}

}

void Maze::removeWall(Maze::Cell& current, Maze::Cell& next)
{
	int asseY = current.x - next.x;
	if (asseY == 1)
	{
		grid[current.x][current.y]->walls[0] = false;
		grid[next.x][next.y]->walls[2] = false;
	}
	else if (asseY == -1)
	{
		grid[current.x][current.y]->walls[2] = false;
		grid[next.x][next.y]->walls[0] = false;
	}

	int asseX = current.y - next.y;
	if (asseX == 1)
	{
		grid[current.x][current.y]->walls[1] = false;
		grid[next.x][next.y]->walls[3] = false;
	}
	else if (asseX == -1)
	{
		grid[current.x][current.y]->walls[3] = false;
		grid[next.x][next.y]->walls[1] = false;
	}
}
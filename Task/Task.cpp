#include "stdafx.h"                       
#include <iostream>
#include <ctime>
#include <locale>
#include <fstream>
#include <vector>

const bool LEFT = true;
const bool RIGHT = false;

int sizeSet;
int sizePlacements;
int sizeCombinations;
int sizePermutations;
int sizeSubset;
int m;

const int maskaForBit = 0x1;

std::vector<bool> direction;
std::vector<int> set;
std::vector<std::vector<int>> combinations;
std::vector<std::vector<int>> permutations;

__int64 Factorial(int number)
{
	if ((number == 1) | (number == 0))
	{
		return 1;
	}
	return Factorial(number - 1) * number;
}

void ResetDirection()
{
	direction.clear();
	for (int i = 0; i < m; i++)
	{
		direction.push_back(LEFT);
	}
}

void GenerationCombinations()
{
	for (int i = 0; i < sizeSubset; i++)
	{
		int tempMask = i;
		std::vector<int> temp;
		for (int j = 0; j < sizeSet; j++)
		{
			if (tempMask & maskaForBit)
			{
				temp.push_back(j);
			}
			tempMask >>= 1;
		}

		if (temp.size() != m)
		{
			continue;
		}
		combinations.push_back(temp);
	}
}

void GenerationPlacements(std::vector<int> temp)
{
	permutations.push_back(temp);

	bool flag = false;
	do
	{
		// поиск максимального мобильного элемента
		std::pair<int, bool> pair(INT_MIN, false);
		int tempI = 0;
		flag = false;
		for (int i = 0; i < m; i++)
		{
			if ((i != 0) && (direction[i] == LEFT)
				&& (temp[i] > temp[i - 1]))
			{
				if (pair.first < temp[i])
				{
					pair.first = temp[i];
					pair.second = direction[i];
					tempI = i;
					flag = true;
				}
			}
			else if ((i != m - 1) && (direction[i] == RIGHT)
				&& (temp[i] > temp[i + 1]))
			{
				if (pair.first < temp[i])
				{
					pair.first = temp[i];
					pair.second = direction[i];
					tempI = i;
					flag = true;
				}
			}
		}

		// перемещение мобильного элемента и смена направлений
		if (flag == true)
		{
			if (direction[tempI] == LEFT)
			{
				std::swap(direction[tempI], direction[tempI - 1]);
				std::swap(temp[tempI], temp[tempI - 1]);
				tempI--;
			}
			else if (direction[tempI] == RIGHT)
			{
				std::swap(direction[tempI], direction[tempI + 1]);
				std::swap(temp[tempI], temp[tempI + 1]);
				tempI++;
			}
			permutations.push_back(temp);

			for (int i = 0; i < m; i++)
			{
				if (temp[tempI] < temp[i])
				{
					if (direction[i])
					{
						direction[i] = false;
					}
					else
					{
						direction[i] = true;
					}
				}
			}
		}
	} while (flag == true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	
	//Данные
	m = 3;
	sizeSet = 4;
	sizeCombinations = Factorial(sizeSet) / (Factorial(sizeSet - m) * Factorial(m));
	sizeSubset = (int)pow(2, sizeSet);
	sizePermutations = Factorial(sizeSet) / Factorial(sizeSet - m);
	sizePlacements = Factorial(m);

	for (int i = 0; i < sizeSet; i++)
	{
		set.push_back(i);
	}
	
	//Запуск генератора
	GenerationCombinations();
	for (int i = 0; i < sizeCombinations; i++)
	{
		ResetDirection();
		GenerationPlacements(combinations[i]);
	}

	std::cout << "Размещения:" << std::endl;
	for (int i = 0; i < sizePermutations; i++)
	{
		std::cout << "{ ";
		for (int j = 0; j < permutations[i].size(); j++)
		{
			std::cout << char(97 + permutations[i][j]) << " ";
		}
		std::cout << "}" << std::endl;
	}

	system("pause");
	return 0;
}


#include "GA.h"

GA::GA()
{
	evpop(popcurrent);
}

GA::~GA()
{
}

void GA::Update()
{
	for (int i = 0; i < 4; i++)
	{
		popnext[i] = popcurrent[i];
	}

	PickChroms(popnext);
	Crossover(popnext);
	Mutation(popnext);

	for (int i = 0; i < 4; i++)
	{
		popcurrent[i] = popnext[i];
	}
}

void GA::evpop(chrom popcurrent[4])
{
	int random;
	int value;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			random = rand() % 2;
			popcurrent[i].bit[j] = random;
		}
		value = x(popcurrent[i]);
		popcurrent[i].fit = y(x(popcurrent[i]));
		printf("\n popcurrent[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i,
			popcurrent[i].bit[5], popcurrent[i].bit[4], popcurrent[i].bit[3], popcurrent[i].bit[2],
			popcurrent[i].bit[1], popcurrent[i].bit[0], value, popcurrent[i].fit);
	}
}

int GA::x(chrom popcurrent)
{
	int z = (popcurrent.bit[0] * 1) + (popcurrent.bit[1] * 2) + (popcurrent.bit[2] * 4) + (popcurrent.bit[3] * 8) + (popcurrent.bit[4] * 16);
	if (popcurrent.bit[5] == 1)
	{
		z = z * (-1);
	}
	return 0;
}

int GA::y(int x)
{
	int y = -(x * x) + 5;
	return(y);
}

void GA::PickChroms(chrom popcurrent[4])
{
	chrom temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (popcurrent[j + 1].fit > popcurrent[j].fit)
			{
				temp = popcurrent[j + 1];
				popcurrent[j + 1] = popcurrent[j];
				popcurrent[j] = temp;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		std::cout << "\nSorting: popnext[" << i << "] fitness=" << popcurrent[i].fit;
		//printf("\nSorting:popnext[%d] fitness=%d", i, popcurrent[i].fit); // print the result
	}
	std::cout << std::endl;
}

void GA::Crossover(chrom popnext[4])
{
	int random = (rand() % 5) + 1;
	for (int i = 0; i < random; i++)
	{
		popnext[2].bit[i] = popnext[0].bit[i];
		popnext[3].bit[i] = popnext[1].bit[i];
	}

	for (int i = random; i < 6; i++)
	{
		popnext[2].bit[i] = popnext[1].bit[i];
		popnext[3].bit[i] = popnext[0].bit[i];
	}

	for (int i = 0; i < 4; i++)
	{
		popnext[i].fit = y(x(popnext[i]));
	}

	for (int i = 0; i < 4; i++)
	{
		printf("\nCrossOver popnext[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i,
			popnext[i].bit[5], popnext[i].bit[4], popnext[i].bit[3], popnext[i].bit[2],
			popnext[i].bit[1], popnext[i].bit[0], x(popnext[i]), popnext[i].fit);
	}
}

void GA::Mutation(chrom popnext[4])
{
	int random = rand() % 50;

	if (random == 25)
	{
		int col = rand() % 6;
		int row = rand() % 4;

		if (popnext[row].bit[col] == 0) // invert the bit
		{
			popnext[row].bit[col] = 1;
		}
		else if (popnext[row].bit[col] == 1)
		{
			popnext[row].bit[col] = 0;
		}

		popnext[row].fit = y(x(popnext[row]));
		int value = x(popnext[row]);
		printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   fitness = % d", row, col, popnext[row].bit[5], popnext[row].bit[4], popnext[row].bit[3],
			popnext[row].bit[2], popnext[row].bit[1], popnext[row].bit[0], value, popnext[row].fit);
	}
}
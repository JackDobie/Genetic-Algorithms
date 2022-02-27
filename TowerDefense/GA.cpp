#include "GA.h"

GA::GA()
{
	evpop();
}

GA::~GA()
{
}

void GA::Update()
{
	// setting currentindex to -1 shows that it is ready to do GA again, otherwise it is checking fitness of each chrom
	if (currentIndex != -1)
	{
		std::cout << "Index: " << currentIndex << ": ";
		for (int j = 0; j < CHROM_BITS; j++)
		{
			std::cout << popnext[currentIndex].bit[j] << " ";
		}
		std::cout << std::endl;
		std::cout << "Score: " << popnext[currentIndex].fit << std::endl;

		if (mutating) // if mutating, only want to check fitness of that one chrom, so can change back to -1 after fitness was found
		{
			mutating = false;
			currentIndex = -1;
		}
		else if (++currentIndex >= POP_SIZE) // update index. if index greater than max, check for mutation which will change currentindex once finished
		{
			if (rand() % 2 == 1)
			{
				Mutation();
			}
			else
			{
				if (!pickedNewChroms) // has to check if not previously picked new chroms because picknewchroms will cause it to go back to here 
				{
					PickNewChroms();
				}
				else
				{
					pickedNewChroms = false; // reset pickednewchroms to allow it to be used next time
					currentIndex = -1;
				}
			}
		}
	}
	
	if (currentIndex == -1)
	{
		PickChroms(); // sort popcurrent to have the highest scoring at the front to be used as parents

		Crossover();
	}
}

void GA::SetCurrentScore(int score)
{
	if (currentIndex != -1)
	{
		popnext[currentIndex].fit = score;
	}
}

void GA::evpop()
{
	// generate chroms for population size
	for (int i = 0; i < POP_SIZE; i++)
	{
		for (int j = 0; j < CHROM_BITS; j++)
		{
			int newPosX, newPosY;
			newPosX = rand() % BOARD_WIDTH;
			newPosY = rand() % BOARD_HEIGHT;
			// check if the generated chrom is not the same as the others
			for (int k = 0; k < POP_SIZE; k++)
			{
				if (k != i)
				{
					while (newPosX == popcurrent[k].bitPosX[j])
					{
						newPosX = rand() % BOARD_WIDTH;
					}
					popcurrent[i].bitPosX[j] = newPosX;

					while (newPosY == popcurrent[k].bitPosY[j])
					{
						newPosY = rand() % BOARD_HEIGHT;
					}
					popcurrent[i].bitPosY[j] = newPosY;
				}
			}

			int newBit = (rand() % towerBit::thrower) + 1;
			popcurrent[i].bit[j] = newBit;
			//random = rand() % BOARD_WIDTH;
			//popcurrent[i].bitPosX[j] = random;
			//random = rand() % BOARD_HEIGHT;
			//popcurrent[i].bitPosY[j] = random;
			//popcurrent[i].fit = 0;
		}

		popnext[i] = popcurrent[i];
	}
}

void GA::PickChroms()
{
	for (int i = 0; i < POP_SIZE; i++)
	{
		popcurrent[i] = popnext[i];
	}

	chrom temp;
	for (int i = 0; i < POP_SIZE; i++)
	{
		for (int j = i + 1; j <= POP_SIZE; j++)
		{
			if (popcurrent[j].fit > popcurrent[i].fit)
			{
				//std::cout << "new chroms picked: " << popcurrent[j].fit << std::endl;
				temp = popcurrent[j];
				popcurrent[j] = popcurrent[i];
				popcurrent[i] = temp;
			}
		}
	}

	std::cout << "\n========================\n";
	for (int i = 0; i < POP_SIZE; i++)
	{
		std::cout << "Chrom " << i << ": ";
		for (int j = 0; j < CHROM_BITS; j++)
		{
			std::cout << popcurrent[i].bit[j] << " ";
		}
		std::cout << std::endl;
		std::cout << "Score: " << popcurrent[i].fit << std::endl;
	}
	std::cout << "========================\n\n";

	for (int i = 0; i < POP_SIZE; i++)
	{
		popnext[i] = popcurrent[i]; // update popnext with the sorted chroms
	}
}

void GA::Crossover()
{
	if (POP_SIZE > 1)
	{
		std::cout << "Crossover:" << std::endl;

		int crossPoint = CROSSOVER_POINT;
		if (CROSSOVER_POINT == -1)
		{
			crossPoint = (rand() % CHROM_BITS) + 1;
		}

		// start on parent size to start on children
		for (int i = CROSSOVER_PARENTS; i < POP_SIZE; i++)
		{
			for (int j = 1; j < crossPoint; j++) // crossing bits below the cross point
			{
				// if crossover index greater than 1, take 1. this makes the index different to the index after the cross point
				int index = j % (CROSSOVER_PARENTS > 1 ? CROSSOVER_PARENTS - 1 : CROSSOVER_PARENTS);
				chrom crossChrom = popnext[index];
				popnext[i].bit[j] = crossChrom.bit[j];
				popnext[i].bitPosX[j] = crossChrom.bitPosX[j];
				popnext[i].bitPosY[j] = crossChrom.bitPosY[j];
			}
			for (int j = crossPoint; j < CHROM_BITS; j++) // crossing bits above the cross point
			{
				int index = j % CROSSOVER_PARENTS;
				chrom crossChrom = popnext[index];
				popnext[i].bit[j] = crossChrom.bit[j];
				popnext[i].bitPosX[j] = crossChrom.bitPosX[j];
				popnext[i].bitPosY[j] = crossChrom.bitPosY[j];
			}
			popnext[i].fit = 0;
		}

		// set to parents size because do not need to re check chroms that did not change (parents)
		currentIndex = CROSSOVER_PARENTS;

		/*for (int i = currentIndex; i < POP_SIZE; i++)
		{
			popnext[i].fit = 0;
		}*/
	}
}

bool GA::Mutation()
{
	if ((rand() % 2) == 1)
	{
		int bitIndex = rand() % CHROM_BITS;
		int chromIndex = rand() % POP_SIZE;
		// randomise bit
		std::cout << "\n------------------------\nMutation! Index: " << chromIndex << std::endl;
		for (int i = 0; i < CHROM_BITS; i++)
		{
			std::cout << popnext[chromIndex].bit[i];
		}
		std::cout << " -> ";

		chrom newChrom = popnext[chromIndex];

		// make new random bit that is not the same
		short newBit = (rand() % towerBit::thrower) + 1;
		while (newBit == popnext[chromIndex].bit[bitIndex])
		{
			newBit = (rand() % towerBit::thrower) + 1;
		}
		newChrom.bit[bitIndex] = newBit;

		// make new random X position
		short int newPosX = rand() % BOARD_WIDTH;
		while (newPosX == popnext[chromIndex].bitPosX[bitIndex])
		{
			newPosX = rand() % BOARD_WIDTH;
		}
		newChrom.bitPosX[bitIndex] = newPosX;

		// make new random Y position
		short int newPosY = rand() % BOARD_HEIGHT;
		while (newPosY == popnext[chromIndex].bitPosY[bitIndex])
		{
			newPosY = rand() % BOARD_HEIGHT;
		}
		newChrom.bitPosY[bitIndex] = newPosY;

		popnext[chromIndex] = newChrom;

		for (int i = 0; i < CHROM_BITS; i++)
		{
			std::cout << popnext[chromIndex].bit[i];
		}
		std::cout << "\n------------------------\n\n";
		//std::cout << "mutation!" << std::endl;
		currentIndex = chromIndex;
		mutating = true;
		popnext[currentIndex].fit = 0;
		return true;
	}
	else
	{
		currentIndex = -1;
		return false;
	}
}

void GA::PickNewChroms()
{
	if (rand() % 2 == 1)
	{
		PickChroms(); // sort chroms

		std::cout << "\n------------------------\nPicked new chroms!\nIndex: ";
		int index = POP_SIZE - NEW_CHROMS;
		// generate new random chroms that score the lowest
		for (int i = index; i < POP_SIZE; i++)
		{
			std::cout << i << (i == POP_SIZE - 1 ? "\n" : ", ");
			for (int j = 0; j < CHROM_BITS; j++)
			{
				int newBit = (rand() % towerBit::thrower) + 1;
				popnext[i].bit[j] = newBit;
				int newPosX = rand() % BOARD_WIDTH;
				popnext[i].bitPosX[j] = newPosX;
				int newPosY = rand() % BOARD_HEIGHT;
				popnext[i].bitPosY[j] = newPosY;
				popnext[i].fit = 0;
			}
		}
		std::cout << "\n------------------------\n\n";
		currentIndex = index;
		pickedNewChroms = true;
	}
	else
	{
		currentIndex = -1;
	}
}

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

		//std::cout << "Index: " << currentIndex << ", Score: " << popnext[currentIndex].fit << std::endl;
		if (mutating) // if mutating, only want to check fitness of that one chrom, so can change back to -1 after fitness was found
		{
			mutating = false;
			//popcurrent[currentIndex] = popnext[currentIndex]; // update popcurrent. only need to update currentindex chrom because only that was changed
			currentIndex = -1;
			for (int i = 0; i < POP_SIZE; i++)
			{
				popcurrent[i] = popnext[i]; // update popcurrent before it sorts again in pickchroms
			}
		}
		else if (++currentIndex >= POP_SIZE) // update index. if index greater than max, check for mutation which will change currentindex once finished
		{
			Mutation();

			for (int i = 0; i < POP_SIZE; i++)
			{
				popcurrent[i] = popnext[i]; // update popcurrent before it sorts again in pickchroms
			}
		}
		/*else
		{
			popcurrent[currentIndex] = popnext[currentIndex];
		}*/
	}
	
	if (currentIndex == -1)
	{
		PickChroms(); // sort popcurrent to have the highest scoring at the front to be used as parents

		for (int i = 0; i < POP_SIZE; i++)
		{
			popnext[i] = popcurrent[i]; // update popnext with the sorted chroms
		}

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
	srand(time(NULL));
	// generate chroms for population size
	for (int i = 0; i < POP_SIZE; i++)
	{
		for (int j = 0; j < CHROM_BITS; j++)
		{
			bool canContinue = true;
			int newPosX, newPosY;
			// check if the generated chrom is not the same as the others
			for (int k = 0; k < POP_SIZE; k++)
			{
				if (k != i)
				{
					/*newBit = (rand() % towerBit::thrower) + 1;
					while (newBit == popcurrent[k].bit[j])
					{
						newBit = (rand() % towerBit::thrower) + 1;
					}
					popcurrent[i].bit[j] = newBit;*/

					newPosX = rand() % BOARD_WIDTH;
					while (newPosX == popcurrent[k].bitPosX[j])
					{
						newPosX = rand() % BOARD_WIDTH;
					}
					popcurrent[i].bitPosX[j] = newPosX;

					newPosY = rand() % BOARD_HEIGHT;
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
}

void GA::Crossover()
{
	if (POP_SIZE > 1)
	{
		std::cout << "Crossover:" << std::endl;
		int random = (rand() % CHROM_BITS - 1) + 2;

		// start on half pop size to start on children
		int halfPopSize = POP_SIZE / 2;
		for (int i = halfPopSize; i < POP_SIZE; i++)
		{
			for (int j = 1; j < random; j++) // crossing bits below the cross point
			{
				chrom crossChrom = popnext[i - halfPopSize];
				popnext[i].bit[j] = crossChrom.bit[j];
				popnext[i].bitPosX[j] = crossChrom.bitPosX[j];
				popnext[i].bitPosY[j] = crossChrom.bitPosY[j];
			}
			for (int j = random; j < CHROM_BITS; j++) // crossing bits above the cross point
			{
				int distance = i - halfPopSize - 1;
				chrom crossChrom = popnext[halfPopSize - distance];
				popnext[i].bit[j] = crossChrom.bit[j];
				popnext[i].bitPosX[j] = crossChrom.bitPosX[j];
				popnext[i].bitPosY[j] = crossChrom.bitPosY[j];
			}
		}

		// set to halfpopsize because do not need to re check chroms that did not change
		currentIndex = halfPopSize;
		//currentIndex = 0;

		for (int i = halfPopSize; i < POP_SIZE; i++)
		{
			popnext[i].fit = 0;
		}
	}
}

void GA::Mutation()
{
	int random = rand() % 3;

	if (random == 1)
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
		std::cout << std::endl;
		//std::cout << "mutation!" << std::endl;
		currentIndex = chromIndex;
		mutating = true;
		popnext[currentIndex].fit = 0;
	}
	else
	{
		currentIndex = -1;
	}
}
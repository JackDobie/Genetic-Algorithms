#include "AIController.h"
#include "Timer.h"
#include "GameState.h"
#include <iostream>
#include <Windows.h>
#include "GA.h"

#include "GameController.h"

using namespace std;

AIController::AIController()
{
	m_gameController = nullptr;
	m_gameBoard = nullptr;
	m_Timer = nullptr;
	m_gameState = nullptr;

	m_GA = new GA();
	GA_iteration = 0;
}

AIController::~AIController()
{

}

void AIController::gameOver()
{
	if (GA_iteration < GA_maxIteration)
	{
		m_GA->SetCurrentScore(m_gameState->getScore());
		cout << m_gameState->getScore() << endl;
	}
	/*else
	{
		chrom* GAPopulation = m_GA->GetPop();
	}*/
}

void AIController::update()
{
	if (m_Timer == nullptr)
		return;

	// HINT
	// a second has elapsed - your GA manager (GA Code) may decide to do something at this time...
	static double elapsedSeconds = 0;
	double seconds = floor(m_Timer->elapsedSeconds());
	if (seconds > elapsedSeconds)
	{
		elapsedSeconds = seconds;

	}

	//GAManager::Instance()->Update(m_Timer->elapsedSeconds());

	if (!TowersToAdd.empty()) // if haven't placed all GA towers
	{
		for (int i = 0; i < TowersToAdd.size(); i++)
		{
			if (addTower(TowersToAdd[i])) // if the tower was successfully added, remove from vector
			{
				cout << "Add tower: " << (int)TowersToAdd[i].type << ", X: " << TowersToAdd[i].xPos << ", Y: " << TowersToAdd[i].yPos << endl;
				swap(TowersToAdd[i], TowersToAdd.back());
				TowersToAdd.pop_back();
			}
		}
	}

	// this might be useful? Monsters killed
	static int monstersKilled = 0;

	if (m_gameState->getMonsterEliminated() > monstersKilled)
	{
		monstersKilled = m_gameState->getMonsterEliminated();
	}

	recordScore();
}

bool AIController::addTower(TowerInfo tower)
{
	return m_gameBoard->addTower(tower.type, tower.xPos, tower.yPos);
}

bool AIController::addTower(TowerType type, int gridx, int gridy)
{
	// grid position can be from 0,0 to 25,17
	/*
	enum class TowerType {
	empty, slammer, swinger, thrower };
	*/

	bool towerAdded = m_gameBoard->addTower(type, gridx, gridy);
	return towerAdded;
	// NOTE towerAdded might be false if the tower can't be placed in that position, is there isn't enough funds
}

void AIController::setupBoard()
{
	m_Timer->start();

	m_GA->Update();
	GA_iteration++;
	chrom* GAPopulation = m_GA->GetPop();
	for (int i = 0; i < POP_SIZE; i++)
	{
		for (int j = 0; j < CHROM_BITS; j++)
		{
			/*TowerType t = (TowerType)GAPopulation[i].bit[j];
			int xPos = GAPopulation[i].bitPosX[j];
			int yPos = GAPopulation[i].bitPosY[j];*/
			TowerInfo t;
			t.type = (TowerType)GAPopulation[i].bit[j];
			t.xPos = GAPopulation[i].bitPosX[j];
			t.yPos = GAPopulation[i].bitPosY[j];

			if (addTower(t))
			{
				cout << "Add tower: " << (int)t.type << ", X: " << t.xPos << ", Y: " << t.yPos << endl;
			}
			else
			{
				cout << "Unable to add tower: " << (int)t.type << ", X: " << t.xPos << ", Y: " << t.yPos << endl;
				TowersToAdd.push_back(t);
			}
		}
	}
}

int AIController::recordScore()
{
	int currentWave = m_gameState->getCurrentWave();
	int killCount = m_gameState->getMonsterEliminated();
	currentWave *= 10; // living longer is good
	int score = currentWave + killCount;

	static int iteration = 0;

	/*if (iteration == 0)
		cout << "iteration" << "," << "wave" << "," << "kills" << "," << "score" << endl;

	cout << iteration << "," << m_gameState->getCurrentWave() << "," << m_gameState->getMonsterEliminated() << "," << score << endl;*/
	iteration++;

	m_gameState->setScore(score);

	return score;
}
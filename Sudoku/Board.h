#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

class Board {

	vector <Tile> board;
	int width, height, numMines, numFlags, minesLeft;


public:
	bool endGame = false, gameWon = false, debug = false;

	/*Construction/Initialization*/
	Board(int width, int height, int numMines);
	void LoadBoard(string fileName);
	void LoadBoard(int width, int height, int numMines);

	/*Getters*/
	int MineNeighb(int index);
	bool GetTileFlag(int index);
	bool IsPressed(int index);

	/*Helper Functions*/
	void Display(RenderWindow& window);
	void FlipTile(int index);
	void FlagTile(float x, float y);
	void DebugMode();
	void EndGame(bool result);
	void EndGameCheck();

};

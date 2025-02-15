#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>


using namespace sf;

class Tile {

	bool mineStat, flagStat, pressedStat;
	Sprite background, foreground, hidden;

public:
	int vecIndex = NULL;
	int numNeighbors = 0;
	Tile* neighbors[8] = { nullptr };
	Tile();//implement
	Tile(int index, bool isMine);

	/*Mutators*/
	void ChangeFlag();
	void SetPressed();
	void SetForeground();

	/*Getters*/
	Sprite& GetBackground();
	Sprite& GetForeground();
	Sprite& GetHidden();
	bool IsMine();
	bool IsFlagged();
	bool IsPressed();

};


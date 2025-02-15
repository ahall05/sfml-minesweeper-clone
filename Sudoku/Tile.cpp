#include "Tile.h"

Tile::Tile()
{
	this->pressedStat = false;
	this->flagStat = false;
	this->mineStat = false;
	this->background.setTexture(TextureManager::GetTexture("tile_revealed"));
}
Tile::Tile(int index, bool isMine)
{
	this->pressedStat = false;
	this->flagStat = false;
	this->mineStat = isMine;
	this->vecIndex = index;
	this->background.setTexture(TextureManager::GetTexture("tile_revealed"));
	if (isMine) {
		this->foreground.setTexture(TextureManager::GetTexture("mine"));
	}
	this->hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
}

void Tile::ChangeFlag()
{
	if (this->flagStat)
		this->flagStat = false;
	else
		this->flagStat = true;
}

void Tile::SetPressed()
{
	if (this->pressedStat)
		this->pressedStat = false;
	else
		this->pressedStat = true;
}

void Tile::SetForeground()
{
	//assign appropriate foreground, except zero which wont have one
	if (this->numNeighbors != 0) {
		string path = "number_" + std::to_string(this->numNeighbors);
		this->foreground.setTexture(TextureManager::GetTexture(path));
	}
	
}

Sprite& Tile::GetBackground()
{
	return this->background;
}

Sprite& Tile::GetForeground()
{
	return this->foreground;
}

Sprite& Tile::GetHidden()
{
	return this->hidden;
}

bool Tile::IsMine()
{
	return this->mineStat;
}

bool Tile::IsFlagged()
{
	return this->flagStat;
}

bool Tile::IsPressed()
{
	return pressedStat;
}


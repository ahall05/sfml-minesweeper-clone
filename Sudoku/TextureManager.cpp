#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/" + fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return textures[textureName];
}

void TextureManager::Clear()
{
	textures.clear();
}

/*textures["debug"].loadFromFile("debug.png");
	textures["digits"].loadFromFile("digits.png");
	textures["face_happy"].loadFromFile("face_happy.png");
	textures["face_lose"].loadFromFile("face_lose.png");
	textures["face_win"].loadFromFile("face_win.png");
	textures["flag"].loadFromFile("flag.png");
	textures["mine"].loadFromFile("mine.png");
	textures["number_1"].loadFromFile("number_1.png");
	textures["number_2"].loadFromFile("number_2.png");
	textures["number_3"].loadFromFile("number_3.png");
	textures["number_4"].loadFromFile("number_4.png");
	textures["number_5"].loadFromFile("number_5.png");
	textures["number_6"].loadFromFile("number_6.png");
	textures["number_7"].loadFromFile("number_.7png");
	textures["number_8"].loadFromFile("number_8.png");
	textures["test_1"].loadFromFile("test_1.png");
	textures["test_2"].loadFromFile("test_2.png");
	textures["test_3"].loadFromFile("test_3.png");
	textures["tile_hidden"].loadFromFile("tile_hidden.png");
	textures["tile_revealed"].loadFromFile("tile_revealed.png");*/
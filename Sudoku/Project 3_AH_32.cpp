#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "TextureManager.h"
#include "Board.h"
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string data;
    int width, height, numMines;
    int center, boardWidth, boardHeight;
    ifstream inFile("boards/config.cfg");

    getline(inFile, data);
    width = stoi(data);
    boardWidth = width * 32;

    getline(inFile, data);
    height = stoi(data);
    boardHeight = height * 32;

    getline(inFile, data);
    numMines = stoi(data);

    center = (width * 32) / 2;

    sf::RenderWindow window(sf::VideoMode((width * 32), (height * 32 + 100)), "Minesweeper");

    //loads random board from config
    Board testGame(width, height, numMines);
 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (!testGame.endGame) {
                    if ((event.mouseButton.x >= 0 && event.mouseButton.x <= boardWidth)
                    && (event.mouseButton.y >= 0 && event.mouseButton.y <= boardHeight)) {
                        //converts index from pixels to a number from 0 to (height - 1)
                        int xTemp = event.mouseButton.x / 32.0f;
                        int yTemp = event.mouseButton.y / 32.0f;

                        //since its stored in a 1D vector, 
                        //the index is gained by the following formula
                        int index = (yTemp * width) + xTemp;

                        //check for left or right click
                        if (event.mouseButton.button == sf::Mouse::Left) {

                            //if not flagged, flip tile
                            if (!testGame.GetTileFlag(index) && !testGame.IsPressed(index)) {
                                //flip tile
                                testGame.FlipTile(index);
                            } 
                        }
                        else if (event.mouseButton.button == sf::Mouse::Right) {
                            //flag tile
                            testGame.FlagTile(event.mouseButton.x, event.mouseButton.y);
                        }
                    }
                }
                //checks if the click was in the tile area
                
				//check if smiley was clicked
                if ((event.mouseButton.y >= boardHeight && event.mouseButton.y <= (boardHeight + 64))) {

                    if ((event.mouseButton.x >= (center - 32) && event.mouseButton.x <= (center + 32))) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            testGame.LoadBoard(width, height, numMines);
                        }
                    }//checks if debug was pressed
                    else if ((event.mouseButton.x >= ((center + 32) + (1 * 64))) && (event.mouseButton.x <= ((center + 32) + (2 * 64)))) {
                        testGame.DebugMode();
                    }//checks if test 1 was pressed
                    else if ((event.mouseButton.x > ((center + 32) + (2 * 64))) && (event.mouseButton.x <= ((center + 32) + (3 * 64)))) {
                        testGame.LoadBoard("testboard1.brd");
                    }//checks if test 2 was pressed
                    else if ((event.mouseButton.x > ((center + 32) + (3 * 64))) && (event.mouseButton.x <= ((center + 32) + (4 * 64)))) {
                        testGame.LoadBoard("testboard2.brd");
                    }//checks if test 3 was pressed
                    else if ((event.mouseButton.x > ((center + 32) + (4 * 64))) && (event.mouseButton.x <= ((center + 32) + (5 * 64)))) {
                        testGame.LoadBoard("testboard3.brd");
                    }
                    
                }
            }
        }


        testGame.EndGameCheck();
        window.clear();


        testGame.Display(window);

        /*sf::Texture tile_hidden, tile_revealed;
        if (!tile_hidden.loadFromFile("images/tile_hidden.png"))
            cout << "Nope";
        else {

            //draw board
            for (int i = 0; i < 5; i++) {
                tile_hidden.loadFromFile("images/tile_hidden.png");
                tile_revealed.loadFromFile("images/tile_revealed");
                sf::Sprite testSprite;
                testSprite.setTexture(tile_hidden);
                testSprite.setPosition(i * 32, 0);
                window.draw(testSprite);
            }
        }    //change texture
        if (event.type == sf::Event::MouseButtonPressed) {
            tile_revealed.loadFromFile("images/tile_revealed.png");
            sf::Sprite testHidden;
            testHidden.setTexture(tile_revealed);
            sf::Vector2i position = sf::Mouse::getPosition();
            position.x -= position.x % 32;
            position.y -= position.y % 32;
            testHidden.setPosition(position.x, position.y);
            window.draw(testHidden);
        }*/
        
        window.display();
    }

    return 0;
}
/********END OF MAIN********/

/*




*/
#include "Board.h"
#include "TextureManager.h"

Board::Board(int width, int height, int numMines) {
    this->width = width;
    this->height = height;
    this->numMines = numMines;
    this->minesLeft = numMines;
    LoadBoard(width, height, numMines);
}

void Board::Display(RenderWindow& window)
{
    //display board
    int tileCount = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            //draw background
            this->board[tileCount].GetBackground().setPosition(x * 32.0f, y * 32.0f);
            window.draw(this->board[tileCount].GetBackground());

            //draw foreground
            this->board[tileCount].GetForeground().setPosition(x * 32, y * 32);
            window.draw(this->board[tileCount].GetForeground());

            
            if (this->board[tileCount].IsPressed()) {
                
            }
            else {
                //display hidden tile
                this->board[tileCount].GetHidden().setPosition(x * 32, y * 32);
                window.draw(this->board[tileCount].GetHidden());
            }
            //if flagged, draw flag on top 
            if (this->board[tileCount].IsFlagged() || (this->gameWon && this->endGame && this->board[tileCount].IsMine())) {
                Sprite flag(TextureManager::GetTexture("flag"));
                flag.setPosition(x * 32, y * 32);
                window.draw(flag);
            }
            //if debug mode, or if the game is over and the game is lost, draw mine on top
            if ((this->debug || (!this->gameWon && this->endGame)) && this->board[tileCount].IsMine()) {
                this->board[tileCount].GetForeground().setPosition(x * 32, y * 32);
                window.draw(this->board[tileCount].GetForeground());
            }
            
            tileCount++;
        }
    }

    //set each digit
        Sprite hunDig(TextureManager::GetTexture("digits"));
        Sprite tenDig(TextureManager::GetTexture("digits"));
        Sprite oneDig(TextureManager::GetTexture("digits"));

    if (this->minesLeft >= 0) {
        hunDig.setTextureRect(sf::IntRect((this->minesLeft / 100) * 21, 0, 21, 32));
        hunDig.setPosition(0, this->height * 32);

        tenDig.setTextureRect(sf::IntRect(((this->minesLeft / 10) % 10) * 21, 0, 21, 32));
        tenDig.setPosition(21, this->height * 32);
    
        oneDig.setTextureRect(sf::IntRect((this->minesLeft % 10) * 21, 0, 21, 32));
        oneDig.setPosition(42, this->height * 32);
    }
    else {
        hunDig.setTextureRect(sf::IntRect((10 * 21), 0, 21, 32));
        hunDig.setPosition(0, this->height * 32);

        tenDig.setTextureRect(sf::IntRect((abs((this->minesLeft / 10)) % 10) * 21, 0, 21, 32));
        tenDig.setPosition(21, this->height * 32);

        oneDig.setTextureRect(sf::IntRect((abs(this->minesLeft) % 10) * 21, 0, 21, 32));
        oneDig.setPosition(42, this->height * 32);
    }

    //display buttons
    Sprite test1(TextureManager::GetTexture("test_1")),
           test2(TextureManager::GetTexture("test_2")),
           test3(TextureManager::GetTexture("test_3")),
           debug(TextureManager::GetTexture("debug")),
           smiley, minesLeft;
    
    int center = ((this->width * 32) / 2) - 32;

    if (this->endGame && this->gameWon) {
        smiley.setTexture(TextureManager::GetTexture("face_win"));
    }
    else if(this->endGame && !this->gameWon) {
        smiley.setTexture(TextureManager::GetTexture("face_lose"));
    }
    else {
        smiley.setTexture(TextureManager::GetTexture("face_happy"));
    }
    smiley.setPosition(center, this->height * 32);
    debug.setPosition(center + (2 * 64), this->height * 32);
    test1.setPosition(center + (3 * 64), this->height * 32);
    test2.setPosition(center + (4 * 64), this->height * 32);
    test3.setPosition(center + (5 * 64), this->height * 32);
    
    window.draw(hunDig);
    window.draw(tenDig);
    window.draw(oneDig);
    window.draw(smiley);
    window.draw(debug);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);
}

void Board::LoadBoard(string fileName)
{
    this->endGame = false;
    this->gameWon = false;
    this->numMines = 0;
    this->board.clear();
    string path = "boards/" + fileName;
    ifstream inFile(path);

    string data;
    int rowCount = 0;
    while (!inFile.eof()) {
        getline(inFile, data);
        for (unsigned int i = 0; i < data.size(); i++) {
            if (data[i] == '1') {        //pass null as index until it's changed later
                this->board.push_back(Tile(NULL, true));
                this->numMines++;
            }
            else {
                this->board.push_back(Tile(NULL, false));
            }
        }
    }

    this->minesLeft = this->numMines;

    //after all mines are initialized, set forground for non-mines and set index
    for (unsigned int i = 0; i < this->board.size(); i++) {
        this->board[i].vecIndex = i;
        if (!this->board[i].IsMine()) {
            //set number of neighbors
            this->board[i].numNeighbors = this->MineNeighb(i);
            //set foreground
            this->board[i].SetForeground();
        }
    }
}

void Board::LoadBoard(int width, int height, int numMines)
{
    this->endGame = false;
    this->gameWon = false;
    this->numMines = 0;
    this->board.clear();
    vector <int> mineList;
    srand(time(NULL));
    int rIndex;

    //generates a list of numMines amount of indexes to be set as mines
    for (int i = 0; mineList.size() < 50; i++) {

        //generate random index
        rIndex = rand() % (width * height);

        //if the index is not already in the list, add it to list
        if (find(mineList.begin(), mineList.end(), rIndex) == mineList.end()) 
            mineList.push_back(rIndex);
        
    }

    //create board, checking if the index is a mine
    for (int i = 0; i < width * height; i++) {

        //if the index is in the mineList, add a mine Tile
        if (!(find(mineList.begin(), mineList.end(), i) == mineList.end())) {
            this->board.push_back(Tile(i, true));
            this->numMines++;
        }
        else {
            this->board.push_back(Tile(i, false));
        }
    }
    this->minesLeft = this->numMines;
    //after all mines are initialized, set forground for non-mines
    for (unsigned int i = 0; i < this->board.size(); i++) {
        if (!this->board[i].IsMine()) {
            //set number of neighbors
            this->board[i].numNeighbors = this->MineNeighb(i);
            //set foreground
            this->board[i].SetForeground();
        }
    }
}

void Board::FlipTile(int index)
{
    //press clicked tile
    this->board[index].SetPressed();

    //if its a mine, trigger endgame
    if (this->board[index].IsMine()) {
        EndGame(false);
    }//else if it has neighbors, set the foreground
    else if (this->MineNeighb(index) != 0){
        this->board[index].SetForeground();
    }//else, it has no neighbors, call recursively
    else {
        //loop through neighbors of pressed tile
        for (int i = 0; i < 8; i++) {
            //if neighbors[i] is not null, not pressed, and not a mine, call FlipTile
            if (this->board[index].neighbors[i] != nullptr && !this->board[index].neighbors[i]->IsPressed() 
                && !this->board[index].neighbors[i]->IsMine() && !this->board[index].neighbors[i]->IsFlagged())
                FlipTile(this->board[index].neighbors[i]->vecIndex);
        }
        
    }

}

void Board::FlagTile(float x, float y)
{
    int xTemp = x / 32.0f;
    int yTemp = y / 32.0f;
    //the index is gained by the following formula
    int index = (yTemp * width) + xTemp;

    this->board[index].ChangeFlag();
   
    if (this->board[index].IsFlagged())
        this->minesLeft--;
    else
        this->minesLeft++;
}

int Board::MineNeighb(int index)
{
    
    int mineNeighbors = 0;
    int xOriginal = index % this->width;
    int yOriginal = index / this->width;

    for (int i = 0; i < 8; i++) {
        int xTemp, yTemp;
        switch (i) {
        //top left
        case 0:
            xTemp = xOriginal - 1;
            yTemp = yOriginal - 1;
            break;
         //top middle
        case 1:
            xTemp = xOriginal;
            yTemp = yOriginal - 1;
            break;
        //top right
        case 2:
            xTemp = xOriginal + 1;
            yTemp = yOriginal - 1;
            break;
        //middle left
        case 3:
            xTemp = xOriginal - 1;
            yTemp = yOriginal;
            break;
        //middle right
        case 4:
            xTemp = xOriginal + 1;
            yTemp = yOriginal;
            break;
        //bottom left
        case 5:
            xTemp = xOriginal - 1;
            yTemp = yOriginal + 1;
            break;
        //bottom middle
        case 6:
            xTemp = xOriginal;
            yTemp = yOriginal + 1;
            break;
        //bottom right
        case 7:
            xTemp = xOriginal + 1;
            yTemp = yOriginal + 1;
            break;
        }

        //check if the temp coordinates are valid
        if ((0 <= xTemp && xTemp < this->width) && (0 <= yTemp && yTemp < this->height)) {
            int tempIndex = (yTemp * this->width) + xTemp;
            //if coordinates are valid, add to passed Tile's neighbors list
            this->board[index].neighbors[i] = &this->board[tempIndex];

            if (this->board[tempIndex].IsMine()) {
                mineNeighbors++;
            }
        }
        //if its invalid, assign nullptr
        else
            this->board[index].neighbors[i] = nullptr;
        
    }
    return mineNeighbors;
}

void Board::DebugMode()
{
    if(this->debug)
        this->debug = false;
    else
        this->debug = true;
}

void Board::EndGame(bool result)
{
    this->endGame = true;
    this->gameWon = result;
}

void Board::EndGameCheck()
{
    int count = 0;
    for (unsigned int i = 0; i < this->board.size(); i++) {
        if (this->board[i].IsPressed())
            count++;
    };

    if (count == this->board.size() - this->numMines) {
        EndGame(true);
        this->minesLeft = 0;
    }
        
}

bool Board::GetTileFlag(int index)
{
    return this->board[index].IsFlagged();
}

bool Board::IsPressed(int index)
{
    return this->board[index].IsPressed();
}


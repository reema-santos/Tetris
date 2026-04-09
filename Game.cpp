#include "Game.h"
#include "IO.h"

int Game::GetRand(int pA, int pB) {
    return rand() % (pB - pA + 1) + pA;
}

void Game::InitGame() {
    // seeds (initialises) the psuedo-rendom number generator
    // i.e. ensures that the program generates a different sequence of random numbers every execution
    // time(NULL) returns current time. as time is constantly changing, 
    // a unique seed is produced each time
    // using the same seed makes things look random, but is the same each time
    srand(time(NULL));

    mPiece = GetRand(0,6);
    mRotation = GetRand(0,3);
    mPosX = (BOARD_WIDTH/2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    mNextPiece = GetRand(0,6);
    mNextRotation = GetRand(0,3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation) {
    colour mColour;

    for (int i = 0; i < PIECE_BLOCKS; ++i) {
        for (int j = 0; j < PIECE_BLOCKS; ++j) {
            switch (mPieces->GetBlockType(pPiece, pRotation, j, i)) {
                case 1:
                    mColour = GREEN;
                    break;
                case 2:
                    mColour = BLUE;
                    break;
            }
            
            if (mPieces->GetBlockType(pPiece, pRotation, j, i) != 0) {
                // mIO->DrawRectangle();
            }
        }
    }
}


void DrawBoard();
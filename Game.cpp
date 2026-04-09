#include "Game.hpp"
#include "IO.hpp"
#include <cassert>

int Game::GetRand(int pA, int pB) {
    return rand() % (pB - pA + 1) + pA;
}

// Initialisation
void Game::InitGame() {
    // seeds (initialises) the psuedo-rendom number generator
    // i.e. ensures that the program generates a different sequence of random numbers every execution
    // time(NULL) returns current time. as time is constantly changing, 
    // a unique seed is produced each time
    // using the same seed makes things look random, but is the same each time
    srand((unsigned int) time(NULL));

    mPiece = GetRand(0,6);
    mRotation = GetRand(0,3);
    mPosX = (BOARD_WIDTH/2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    mNextPiece = GetRand(0,6);
    mNextRotation = GetRand(0,3);
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
}

// Sets the nect piece as the current one and resets position. Then selects a new next piece.
void Game::CreateNewPiece() {
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH/2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    mNextPiece = GetRand(0,6);
    mNextRotation = GetRand(0,3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation) {
    colour mColour;

    int mPixelsX = mBoard->GetXPosInPixels(pX);
    int mPixelsY = mBoard->GetYPosInPixels(pY);

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
                mIO->DrawRectangle(
                    mPixelsX + (i * BLOCK_SIZE),
                    mPixelsY + (j * BLOCK_SIZE),
                    (mPixelsX + (i * BLOCK_SIZE)) + BLOCK_SIZE - 1,
                    (mPixelsY + (j * BLOCK_SIZE)) + BLOCK_SIZE - 1,
                    mColour
                );
                // Parameters:
                // (int pX1, int pY1, int pX2, int pY2, enum colour pC)
            }
        }
    }
}

// Draws two blue columns to delimit the board
// Draws blocks that are already stored in the board
void Game::DrawBoard() {
    // Limits of the board in pixels
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH/2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH/2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    // Verifies assumptions. If condition is false, program terminates.
    assert(mY > MIN_VERTICAL_MARGIN);

    mX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; i < BOARD_HEIGHT; ++j) {
            if (!mBoard->IsFreeBlock(i, j)) {
                mIO->DrawRectangle(
                    mX1 + (i * BLOCK_SIZE),
                    mY + (j * BLOCK_SIZE),
                    (mX2 + (i * BLOCK_SIZE)) + BLOCK_SIZE - 1,
                    (mY + (j * BLOCK_SIZE)) + BLOCK_SIZE - 1,
                    RED
                );
            }
        }
    }
}

// Draws everything
void Game::DrawScene() {
    DrawBoard(); // Delimiters and blocks
    DrawPiece(mPosX, mPosY, mPiece, mRotation); // Playing piece
    DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation); // Next piece
}

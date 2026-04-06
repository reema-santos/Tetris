#include "Board.h"

Board::Board(Pieces* pPieces, int pScreenHeight) {
    mPieces = pPieces;
    mScreenHeight = pScreenHeight;
    InitBoard();
}

void Board::InitBoard() {
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; j < BOARD_HEIGHT; ++j) {
            mBoard[i][j] = POS_FREE;
        }
    }
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation) {
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; ++i1, ++i2) {
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; ++j1, ++j2) {
            if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) {
                // Block is not empty
                // So Board is filled
                mBoard[i1][j1] = POS_FILLED;
            }
        }
    }
}
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

bool Board::IsGameOver() {
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        return (mBoard[i][0] == POS_FILLED);
    }
}

void Board::DeleteLine(int pY) {
    for (int j = pY; j > 0; --j) {
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
}

void Board::DeletePossibleLines() {
    for (int j = 0; j < BOARD_HEIGHT; ++j) {
        int i = 0;
        while (i < BOARD_WIDTH) {
            if (mBoard[i][j] != POS_FILLED) break;
            i++;
        }
        if (i == BOARD_WIDTH) DeleteLine(j);
    }
}

bool Board::IsFreeBlock(int pX, int pY) {
    return mBoard[pX][pY] == POS_FREE;
}
#ifndef _BOARD_
#define _BOARD_

#include "Pieces.hpp"

#define BOARD_LINE_WIDTH 6 // Width of delimiters to board
#define BLOCK_SIZE 16 // Width and height of a block
#define BOARD_POSITION 320 // Centre position of board from the left of the screen
#define BOARD_WIDTH 10 // Board width (blocks)
#define BOARD_HEIGHT 20 // Board height (blocks)
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical board limit
#define MIN_HORIZONTAL_MARGIN 20 // Minimum horizontal board limit
#define PIECE_BLOCKS 5 // Number of horizonal and vertical blocks of a matrix piece

class Board {
    public:
        Board(Pieces* pPieces, int pScreenHeight);

        int GetXPosInPixels(int pPos);
        int GetYPosInPixels(int pPos);
        bool IsFreeBlock(int pX, int pY);
        bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
        void StorePiece(int pX, int pY, int pPiece, int pRotation);
        void DeletePossibleLines();
        bool IsGameOver();

    private:
        enum {
            POS_FREE,
            POS_FILLED
        };
        
        int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
        Pieces* mPieces;
        int mScreenHeight;
        
        void InitBoard();
        void DeleteLine(int pY);
};

#endif
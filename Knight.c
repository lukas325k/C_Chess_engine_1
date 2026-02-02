#include "pieces.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>

static int8_t ValidMovesAtIndex[64][8];

void KnightGenerateValidMoves(void)
{
    for (int i = 0; i < 64; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            ValidMovesAtIndex[i][j] = -1;
        }
    }
    int8_t directions[] = { -17, -10, 6, 15, 17, 10, -6, -15 };
    for (int i = 0; i < 64; i++)
    {
        for (int a = 0; a < 8; a++)
        {
            int dir = directions[a];
            if (0 <= i + dir && i + dir < 64 && (i + dir) / 8 != i / 8)
            {
                if (abs(dir) < 11 && (i + dir) / 8 != i / 8 && ((i + dir) / 8 != (i / 8) +2) && ((i + dir) / 8 != (i / 8) -2))
                    ValidMovesAtIndex[i][a] = i + dir;
                else if (abs(dir) > 11 && (((i + dir) / 8) == (((i) / 8) + 2) || ((i + dir) / 8) == (((i) / 8) - 2)))
                    ValidMovesAtIndex[i][a] = i + dir;
            }
        }
    }
}

int8_t* KnightGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece)
{
    static int8_t ValidMoves[9];
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int i = 0; i < 8; i++)
    {
        if (ValidMovesAtIndex[Index][i] != -1 && (Board[ValidMovesAtIndex[Index][i]] & PieceColor) == 0)
        {
            ValidMoves[WriteIndex] = ValidMovesAtIndex[Index][i];
            WriteIndex ++;
        }
    }

    for (int i = WriteIndex; i < 9; i++)
    {
        ValidMoves[i] = -1;
    }

    return ValidMoves;
}

void MKnightGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *ValidMovesBuffer)
{
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int i = 0; i < 8; i++)
    {
        if (ValidMovesAtIndex[Index][i] != -1 && (Board[ValidMovesAtIndex[Index][i]] & PieceColor) == 0)
        {
            ValidMovesBuffer[WriteIndex] = ValidMovesAtIndex[Index][i];
            WriteIndex ++;
        }
    }

    for (int i = WriteIndex; i < 28; i++)
    {
        ValidMovesBuffer[i] = -1;
    }

}

void KnightGetCaptures(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *CapturesBuffer)
{
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int i = 0; i < 8; i++)
    {
        if (ValidMovesAtIndex[Index][i] != -1 && (Board[ValidMovesAtIndex[Index][i]] & PieceColor) == 0 && Board[ValidMovesAtIndex[Index][i]] != 0)
        {
            CapturesBuffer[WriteIndex] = ValidMovesAtIndex[Index][i];
            WriteIndex ++;
        }
    }

    for (int i = WriteIndex; i < 28; i++)
    {
        CapturesBuffer[i] = -1;
    }

}



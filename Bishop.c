#include "pieces.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>


int8_t* BishopGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece)
{
    static int8_t ValidMoves[15];
    static int8_t directions[] = {7, 9, -7, -9};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 4; d++)
    {
        int dir = directions[d];
        if (dir == -7 || dir == 9)
        {
            for (int i = 1; i < SpaceRight; i++)
            {
                if(0 <= Index+dir*i && Index+dir*i < 64)
                {
                        if (Board[Index+dir*i] == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                    }
                    else if ((Board[Index+dir*i] & ColorMask & PieceColor) == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
        }
        else
        {
            for (int i = 1; i < SpaceLeft; i++)
            {
                if(0 <= Index+dir*i && Index+dir*i < 64)
                {
                        if (Board[Index+dir*i] == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                    }
                    else if ((Board[Index+dir*i] & ColorMask & PieceColor) == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
        }
    }

    


    for (int i = WriteIndex; i < 15; i++)
    {
        ValidMoves[i] = -1;
    }

    return ValidMoves;
}

void MBishopGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t* ValidMovesBuffer)
{
    static int8_t directions[] = {7, 9, -7, -9};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 4; d++)
    {
        int dir = directions[d];
        if (dir == -7 || dir == 9)
        {
            for (int i = 1; i < SpaceRight; i++)
            {
                if(0 <= Index+dir*i && Index+dir*i < 64)
                {
                    if (Board[Index+dir*i] == 0)
                    {
                        ValidMovesBuffer[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                    }
                    else if ((Board[Index+dir*i] & ColorMask & PieceColor) == 0)
                    {
                        ValidMovesBuffer[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
        }
        else
        {
            for (int i = 1; i < SpaceLeft; i++)
            {
                if(0 <= Index+dir*i && Index+dir*i < 64)
                {
                        if (Board[Index+dir*i] == 0)
                    {
                        ValidMovesBuffer[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                    }
                    else if ((Board[Index+dir*i] & ColorMask & PieceColor) == 0)
                    {
                        ValidMovesBuffer[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
        }
    }

    for (int i = WriteIndex; i < 28; i++)
    {
        ValidMovesBuffer[i] = -1;
    }

}

void BishopGetCaptures(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t* CapturesBuffer)
{
    static int8_t directions[] = {7, 9, -7, -9};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 4; d++)
    {
        int dir = directions[d];
        if (dir == -7 || dir == 9)
        {
            for (int i = 1; i < SpaceRight; i++)
            {
                if(0 <= Index+dir*i && Index+dir*i < 64)
                {
                    
                    if ((Board[Index+dir*i] & ColorMask & PieceColor) == 0)
                    {
                        CapturesBuffer[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
        }
        else
        {
            for (int i = 1; i < SpaceLeft; i++)
            {
                if(0 <= Index+dir*i && Index+dir*i < 64)
                {
                    if ((Board[Index+dir*i] & ColorMask & PieceColor) == 0)
                    {
                        CapturesBuffer[WriteIndex] = Index+dir*i;
                        WriteIndex ++;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
        }
    }

    for (int i = WriteIndex; i < 28; i++)
    {
        CapturesBuffer[i] = -1;
    }

}

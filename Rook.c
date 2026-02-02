#include "pieces.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>


int8_t* RookGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece)
{
    static int8_t ValidMoves[15];
    static int8_t directions[] = {1, 8, -1, -8};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 4; d++)
    {
        int dir = directions[d];
        if (dir == 1)
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
        else if (dir == -1)
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
        else
        {
            for (int i = 1; i < 8; i++)
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

void MRookGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *ValidMovesBuffer) {
    static const int directions[4] = {1, -1, 8, -8};
    int8_t WriteIndex = 0;
    int8_t myColor = SelectedPiece & ColorMask;

    int startFile = Index % 8;
    int startRank = Index / 8;

    for (int d = 0; d < 4; d++) {
        int dir = directions[d];
        int step = 1;
        while (1) {
            int target = Index + dir * step;
            int file = target % 8;
            int rank = target / 8;

            if (target < 0 || target >= 64) break;
            if ((dir == 1 || dir == -1) && (file < 0 || file > 7 || abs(file - startFile) != step)) break;

            int8_t piece = Board[target];
            if (piece == 0) {
                ValidMovesBuffer[WriteIndex++] = target;
            } else {
                if ((piece & ColorMask) != myColor) {
                    ValidMovesBuffer[WriteIndex++] = target;
                }
                break; 
            }
            step++;
        }
    }


    while (WriteIndex < 28) ValidMovesBuffer[WriteIndex++] = -1;
}

void RookGetCaptures(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *CapturesBuffer)
{
    static int8_t directions[] = {1, 8, -1, -8};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 4; d++)
    {
        int dir = directions[d];
        if (dir == 1)
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
        else if (dir == -1)
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
        else
        {
            for (int i = 1; i < 8; i++)
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

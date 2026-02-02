#include "pieces.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>


int8_t* KingGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece)
{
    static int8_t ValidMoves[12];
    static int8_t directions[] = {7, 9, -7, -9, -1, 1, 8, -8};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 8; d++)
    {
        int dir = directions[d];
        if (dir == -7 || dir == 9 || dir == 1)
        {
            if (SpaceRight > 1)
            {
                if(0 <= Index+dir && Index+dir < 64)
                {
                    if (Board[Index+dir] == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        if (dir == 1)
                        {
                            if ((SelectedPiece &CastleRightMask) == CastleRight && Board[Index + 2] == 0)
                            {
                                ValidMoves[WriteIndex] = Index + 2;
                                WriteIndex ++;
                            }
                        }
                    }
                    else if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        continue;
                    }
                }
                
            }
        }
        else if (dir == 7 || dir == -9 || dir == -1)
        {
            if (SpaceLeft > 1)
            {
                if(0 <= Index+dir && Index+dir < 64)
                {
                    if (Board[Index+dir] == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        if (dir == -1)
                        {
                            if ((SelectedPiece & CastleLeftMask) == CastleLeft && Board[Index - 2] == 0 && Board[Index - 3] == 0)
                            {
                                ValidMoves[WriteIndex] = Index - 2;
                                WriteIndex ++;
                            }
                        }
                    }
                    else if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                    {
                        ValidMoves[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        continue;
                    }
                }
                
            }
            
        }
        else
        {
            if(0 <= Index+dir && Index+dir < 64)
            {
                if (Board[Index+dir] == 0)
                {
                    ValidMoves[WriteIndex] = Index+dir;
                    WriteIndex ++;
                    continue;
                }
                else if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                {
                    ValidMoves[WriteIndex] = Index+dir;
                    WriteIndex ++;
                    continue;
                }
            }

        }
    }

    


    for (int i = WriteIndex; i < 12; i++)
    {
        ValidMoves[i] = -1;
    }

    return ValidMoves;
}


void MKingGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *VAlidMovesBuffer)
{
    static int8_t directions[] = {7, 9, -7, -9, -1, 1, 8, -8};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 8; d++)
    {
        int dir = directions[d];
        if (dir == -7 || dir == 9 || dir == 1)
        {
            if (SpaceRight > 1)
            {
                if(0 <= Index+dir && Index+dir < 64)
                {
                    if (Board[Index+dir] == 0)
                    {
                        VAlidMovesBuffer[WriteIndex] = Index+dir;
                        WriteIndex ++;
                    
                    }
                    else if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                    {
                        VAlidMovesBuffer[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        continue;
                    }
                }
                
            }
        }
        else if (dir == 7 || dir == -9 || dir == -1)
        {
            if (SpaceLeft > 1)
            {
                if(0 <= Index+dir && Index+dir < 64)
                {
                    if (Board[Index+dir] == 0)
                    {
                        VAlidMovesBuffer[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        
                    }
                    else if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                    {
                        VAlidMovesBuffer[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        continue;
                    }
                }
                
            }
            
        }
        else
        {
            if(0 <= Index+dir && Index+dir < 64)
            {
                if (Board[Index+dir] == 0)
                {
                    VAlidMovesBuffer[WriteIndex] = Index+dir;
                    WriteIndex ++;
                    continue;
                }
                else if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                {
                    VAlidMovesBuffer[WriteIndex] = Index+dir;
                    WriteIndex ++;
                    continue;
                }
            }

        }
    }

    


    for (int i = WriteIndex; i < 28; i++)
    {
        VAlidMovesBuffer[i] = -1;
    }

}

void KingGetCaptures(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *CapturesBuffer)
{
    static int8_t directions[] = {7, 9, -7, -9, -1, 1, 8, -8};
    int SpaceLeft = Index%8 + 1;
    int SpaceRight = 8 - Index%8;
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;

    for (int d = 0; d < 8; d++)
    {
        int dir = directions[d];
        if (dir == -7 || dir == 9 || dir == 1)
        {
            if (SpaceRight > 1)
            {
                if(0 <= Index+dir && Index+dir < 64)
                {
                    
                    if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                    {
                        CapturesBuffer[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        continue;
                    }
                }
                
            }
        }
        else if (dir == 7 || dir == -9 || dir == -1)
        {
            if (SpaceLeft > 1)
            {
                if(0 <= Index+dir && Index+dir < 64)
                {
                    if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                    {
                        CapturesBuffer[WriteIndex] = Index+dir;
                        WriteIndex ++;
                        continue;
                    }
                }
                
            }
            
        }
        else
        {
            if(0 <= Index+dir && Index+dir < 64)
            {
                if ((Board[Index+dir] & ColorMask & PieceColor) == 0)
                {
                    CapturesBuffer[WriteIndex] = Index+dir;
                    WriteIndex ++;
                    continue;
                }
            }

        }
    }



    for (int i = WriteIndex; i < 28; i++)
    {
        CapturesBuffer[i] = -1;
    }

}

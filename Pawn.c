#include "pieces.h"
#include "config.h"
#include <stdbool.h>


int8_t* PawnGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece)
{
    static int8_t ValidMoves[5];
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;
    int direction = (PieceColor == Black) ? 1 : -1;
    bool TwoUpFlag = (SelectedPiece & Pawn2UpMask) != 0;

    int OneStep = Index + 8 * direction;
    if (0 <= OneStep && OneStep < 64 && Board[OneStep] == 0)
    {
        ValidMoves[WriteIndex] = OneStep;
        WriteIndex ++;

        if (TwoUpFlag == true)
        {   
            int TwoStep = Index + (2 * 8 * direction);
            if (0 <= TwoStep && TwoStep < 64 && Board[TwoStep] == 0)
            {
                ValidMoves[WriteIndex] = TwoStep;
                WriteIndex ++;
            }

        }
    }
    for (int Sidestep = -1; Sidestep < 2; Sidestep += 2)
    {
        if (0 <= (OneStep + Sidestep) && (OneStep+Sidestep) < 64 && ((Board[OneStep+Sidestep] & ColorMask) & PieceColor) == 0 && Board[OneStep+Sidestep] != 0)
        {
            if (((Index/ 8) + direction) == ((OneStep + Sidestep) / 8))
            {
                ValidMoves[WriteIndex] = OneStep + Sidestep;
                WriteIndex++;
            }
        }
    }

    for (int i = WriteIndex; i < 5; i++)
    {
        ValidMoves[i] = -1;
    }

    return ValidMoves;
}

void MPawnGetValidMoves(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *ValidMovesBuffer)
{
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;
    int direction = (PieceColor == Black) ? 1 : -1;
    bool TwoUpFlag = (SelectedPiece & Pawn2UpMask) != 0;

    int OneStep = Index + 8 * direction;
    if (0 <= OneStep && OneStep < 64 && Board[OneStep] == 0)
    {
        ValidMovesBuffer[WriteIndex] = OneStep;
        WriteIndex ++;

        if (TwoUpFlag == true)
        {   
            int TwoStep = Index + (2 * 8 * direction);
            if (0 <= TwoStep && TwoStep < 64 && Board[TwoStep] == 0)
            {
                ValidMovesBuffer[WriteIndex] = TwoStep;
                WriteIndex ++;
            }

        }
    }
    for (int Sidestep = -1; Sidestep < 2; Sidestep += 2)
    {
        if (0 <= (OneStep + Sidestep) && (OneStep+Sidestep) < 64 && ((Board[OneStep+Sidestep] & ColorMask) & PieceColor) == 0 && Board[OneStep+Sidestep] != 0)
        {
            if (((Index/ 8) + direction) == ((OneStep + Sidestep) / 8))
            {
                ValidMovesBuffer[WriteIndex] = OneStep + Sidestep;
                WriteIndex++;
            }
        }
    }

    for (int i = WriteIndex; i < 28; i++)
    {
        ValidMovesBuffer[i] = -1;
    }
}

void PawnGetCaptures(int8_t *Board, int8_t Index, int8_t SelectedPiece, int8_t *CapturesBuffer)
{
    int8_t WriteIndex = 0;
    int8_t PieceColor = SelectedPiece & ColorMask;
    int direction = (PieceColor == Black) ? 1 : -1;

    int OneStep = Index + 8 * direction;
    for (int Sidestep = -1; Sidestep < 2; Sidestep += 2)
    {
        if (0 <= (OneStep + Sidestep) && (OneStep+Sidestep) < 64 && ((Board[OneStep+Sidestep] & ColorMask) & PieceColor) == 0 && Board[OneStep+Sidestep] != 0)
        {
            if (((Index/ 8) + direction) == ((OneStep + Sidestep) / 8))
            {
                CapturesBuffer[WriteIndex] = OneStep + Sidestep;
                WriteIndex++;
            }
        }
    }

    for (int i = WriteIndex; i < 28; i++)
    {
        CapturesBuffer[i] = -1;
    }

}

// #include "config.h"
// #include "pieces.h"
// #include <stdint.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>
// #include <string.h>

// typedef struct
// {
//     int Score;
//     int8_t PieceToMove;
//     int8_t FromIndex;
//     int8_t ToIndex;
// } MoveInfo;

// typedef struct
// {
//     int8_t LeftFrom;
//     int8_t RightFrom;
//     bool CastledLeft;
//     bool CastledRight;

// } RookPos;

// typedef struct
// {
//    int Score;
//    int8_t BoardIndex;
// } IterativeInfo;

// typedef struct
// {
//     int piece;
//     int from;
//     int to;
// }LastMovedPieces;

// typedef struct
// {
//     uint64_t Hash;
//     int16_t Depth;
// }KMInfo;

// typedef struct
// {
//     uint64_t BoardHash;
//     int32_t Score;
//     int8_t BestMove;
//     int8_t BestMoveFrom;
//     int8_t Depth;
//     int8_t MaxDepth;
// }TTData;

// static int8_t PiecePositionsBuffer[30][17];
// static int8_t ValidMovesBuffer[30][28];
// static int ValidMovesScoreBuffer[30][28];
// static int8_t BestMoveBuffer[30];
// static int8_t BestMoveFromBuffer[30];
// static IterativeInfo IterativeInfoBuffer[17];
// static LastMovedPieces LastMovedPiecesArray[30];
// static int HistoryTable[64 * 64];
// static int8_t NumPieces[8][2];

// void V11CalculateInitialMaterial(int8_t *Board, int *WhiteValue, int
// *BlackValue, int* PieceValues, int MaximizingColour)
// {
//     *WhiteValue = 0;
//     *BlackValue = 0;

//     for (int i = 0; i < 64; i++)
//     {
//         int8_t piece = Board[i];
//         int8_t pieceName = piece & NameMask;
//         int8_t color = piece & ColorMask;
//         if (piece == 0)
//             continue;

//         if (color == MaximizingColour)
//         {
//             NumPieces[pieceName][BlackPieceIndex] ++;
//             *BlackValue += PieceValues[piece & NameMask];
//         }
//         else
//         {
//             NumPieces[pieceName][WhitePieceIndex] ++;
//             *WhiteValue += PieceValues[piece & NameMask];
//         }
//     }

//     int numPawns = NumPieces[Pawn][BlackPieceIndex] +
//     NumPieces[Pawn][WhitePieceIndex];
//     NumPieces[NumOrigPawnsIndex][BlackPieceIndex] = numPawns;
//     if (numPawns == 16)
//     {
//         return;
//     }

//     *BlackValue -= NumPieces[Knight][BlackPieceIndex] *
//     KnightsToPawnsSubtraction * (16 - numPawns); *WhiteValue -=
//     NumPieces[Knight][WhitePieceIndex] * KnightsToPawnsSubtraction * (16 -
//     numPawns);

//     *BlackValue += NumPieces[Rook][BlackPieceIndex] * RooksToPawnsAdition *
//     (16 - numPawns); *WhiteValue += NumPieces[Rook][WhitePieceIndex] *
//     RooksToPawnsAdition * (16 - numPawns);

// }

// void V11CalculateInitialHash(int8_t *Board, uint64_t *BoardHash, uint64_t
// *ZobristTable)
// {
//     *BoardHash = 0;
//     for (int i = 0; i < 64; i++)
//     {
//         *BoardHash ^= ZobristTable[(Board[i] & PieceMask) * 64 + i];
//     }
// }

// bool V11Contains(uint64_t BoardHash, TTData *TranspositionTable, int Depth,
// int TTindex, int8_t MaxDepth)
// {

//     return (TranspositionTable[TTindex].BoardHash == BoardHash &&
//        TranspositionTable[TTindex].Depth >= Depth &&
//         TranspositionTable[TTindex].MaxDepth == MaxDepth);

// }

// bool V11TTCanOrderMoves(uint64_t BoardHash, TTData *TranspositionTable, int
// Depth, int TTindex, int To)
// {
//     return (TranspositionTable[TTindex].BoardHash == BoardHash &&
//        TranspositionTable[TTindex].Depth < Depth &&
//         TranspositionTable[TTindex].BestMove == To);
// }

// void V11AddKeyValuePair(TTData *TranspositionTable, int Depth, int Score, int
// TTindex, uint64_t BoardHash, int8_t MaxDepth)
// {
//     TranspositionTable[TTindex].BoardHash = BoardHash;
//     TranspositionTable[TTindex].Score = Score;
//     TranspositionTable[TTindex].Depth = Depth;
//     TranspositionTable[TTindex].MaxDepth = MaxDepth;
//     TranspositionTable[TTindex].BestMove = BestMoveBuffer[Depth + 1];
// }

// void V11WriteArrayToFile(const char* filename, int* array, int length)
// {
//     FILE* file = fopen(filename, "a");
//     if (file == NULL) {
//         perror("Failed to open file");
//         return;
//     }

//     for (int i = 0; i < length; i++) {
//         fprintf(file, "%d\n", array[i]);  // write each value on a new line
//     }
//     fprintf(file, "\n");

//     fclose(file);
// }

// void V11PrintBoardToFile(int8_t *board, const char *filename, int
// boardNumber, double time, int Score, int cutoffs) {
//     FILE *file = fopen(filename, "a"); // Open in append mode
//     if (file == NULL) {
//         printf("Error: Could not open file %s\n", filename);
//         return;
//     }

//     // Optional header for each board
//     fprintf(file, "eals #%d\n", boardNumber);
//     fprintf(file, "time #%f\n", time);
//     fprintf(file, "evals per second #%f\n", (double)boardNumber / time);
//     fprintf(file, "score #%d\n", Score);
//     fprintf(file, "cutoffs #%d\n", cutoffs);

//     for (int row = 0; row < 8; row++) {
//         for (int col = 0; col < 8; col++) {
//             int index = row * 8 + col;

//             // Print piece or empty square
//             if (board[index] == 0) {
//                 fprintf(file, ". "); // Empty square
//             } else {
//                 fprintf(file, "%d ", board[index]); // Piece value
//             }
//         }
//         fprintf(file, "\n"); // Newline after each row
//     }

//     fprintf(file, "------------------------\n\n"); // Separator between
//     boards

//     fclose(file);
// }

// void V11UpdateValues(int8_t CapturedPiece, int *WhiteValue, int *BlackValue,
// int *PieceValues, int reverse, int MaximizingColour, bool Promoted)
// {
//     int numPawns = NumPieces[Pawn][BlackPieceIndex] +
//     NumPieces[Pawn][WhitePieceIndex]; int8_t CapturedPieceName =
//     CapturedPiece & NameMask; if ((CapturedPiece & ColorMask) ==
//     MaximizingColour)
//     {
//         *BlackValue -= PieceValues[CapturedPiece&NameMask] * reverse;

//         NumPieces[CapturedPieceName][BlackPieceIndex] += (-1 * reverse);
//         if (CapturedPieceName == Knight)
//         {
//             *BlackValue += KnightsToPawnsSubtraction * (16 - numPawns) *
//             reverse;
//         }
//         else if (CapturedPieceName == Rook)
//         {
//             *BlackValue -= RooksToPawnsAdition * (16 - numPawns) * reverse;
//         }
//     }
//     else
//     {
//         *WhiteValue -= PieceValues[CapturedPiece&NameMask] * reverse;

//         NumPieces[CapturedPieceName][WhitePieceIndex] += (-1 * reverse);
//         if (CapturedPieceName == Knight)
//         {
//             *WhiteValue += KnightsToPawnsSubtraction * (16 - numPawns) *
//             reverse;
//         }
//         else if (CapturedPieceName == Rook)
//         {
//             *WhiteValue -= RooksToPawnsAdition * (16 - numPawns) * reverse;
//         }
//     }

//     if (CapturedPieceName == Pawn)
//     {
//         *BlackValue += NumPieces[Rook][BlackPieceIndex] * RooksToPawnsAdition
//         * reverse; *BlackValue -= NumPieces[Knight][BlackPieceIndex] *
//         KnightsToPawnsSubtraction * reverse;

//         *WhiteValue += NumPieces[Rook][WhitePieceIndex] * RooksToPawnsAdition
//         * reverse; *WhiteValue -= NumPieces[Knight][WhitePieceIndex] *
//         KnightsToPawnsSubtraction * reverse;
//     }
// }

// void V11MiniMaxCheckCastleRights(int8_t SelectedPiece, int8_t StopIndex,
// int8_t *board, int8_t StartIndex, bool *Castled, RookPos *myRooks)
// {
//     int8_t Color = SelectedPiece & ColorMask;
//     if (Color == Black)
//     {
//         if ((SelectedPiece & NameMask) == King)
//         {
//             if (BlackCanCastleLeft && StopIndex == (BlackKingStartPos - 2) &&
//             StartIndex == BlackKingStartPos)
//             {
//                 board[BlackRookLeftStartPos] = 0;
//                 board[BlackKingStartPos-1] = Rook | Black;
//                 *Castled = true;
//                 myRooks->CastledLeft = true;
//             }
//             else if (BlackCanCastleRight && StopIndex == (BlackKingStartPos +
//             2) && StartIndex == BlackKingStartPos)
//             {
//                 board[BlackRookRightStartPos] = 0;
//                 board[BlackKingStartPos+1] = Rook | Black;
//                 *Castled = true;
//                 myRooks->CastledRight = true;
//             }
//             BlackCanCastleLeft = false;
//             BlackCanCastleRight = false;
//             board[StopIndex] &= PieceMask;
//         }
//         else if ((SelectedPiece & NameMask) == Rook)
//         {
//             if (StartIndex == BlackRookRightStartPos)
//             {
//                 BlackCanCastleRight = false;

//                 if ((board[BlackKingStartPos] & NameMask) == King)
//                 {
//                     board[BlackKingStartPos] &= (PieceMask | CastleLeftMask);
//                 }
//             }
//             else if (StartIndex == BlackRookLeftStartPos)
//             {
//                 BlackCanCastleLeft = false;
//                 if ((board[BlackKingStartPos] & NameMask) == King)
//                 {
//                     board[BlackKingStartPos] &= (PieceMask |
//                     CastleRightMask);
//                 }
//             }
//         }

//     }
//     else if (Color == White)
//     {
//         if ((SelectedPiece & NameMask) == King)
//         {
//             if (WhiteCanCastleLeft && StopIndex == (WhiteKingStartPos - 2) &&
//             StartIndex == WhiteKingStartPos)
//             {
//                 board[WhiteRookLeftStartPos] = 0;
//                 board[WhiteKingStartPos-1] = Rook | White;
//                 *Castled = true;
//                 myRooks->CastledLeft = true;
//             }
//             else if (WhiteCanCastleRight && StopIndex == (WhiteKingStartPos +
//             2) && StartIndex == WhiteKingStartPos)
//             {
//                 board[WhiteRookRightStartPos] = 0;
//                 board[WhiteKingStartPos+1] = Rook | White;
//                 *Castled = true;
//                 myRooks->CastledRight = true;
//             }
//             WhiteCanCastleLeft = false;
//             WhiteCanCastleRight = false;

//             board[StopIndex] &= PieceMask;
//         }
//         else if ((SelectedPiece & NameMask) == Rook)
//         {
//             if (StartIndex == WhiteRookRightStartPos)
//             {
//                 WhiteCanCastleRight = false;
//                 if ((board[WhiteKingStartPos] & NameMask) == King)
//                 {
//                     board[WhiteKingStartPos] &= (PieceMask | CastleLeftMask);
//                 }
//             }
//             else if (StartIndex == WhiteRookLeftStartPos)
//             {
//                 WhiteCanCastleLeft = false;
//                 if ((board[WhiteKingStartPos] & NameMask) == King)
//                 {
//                     board[WhiteKingStartPos] &= (PieceMask |
//                     CastleRightMask);
//                 }
//             }
//         }

//     }
// }

// bool V11CheckRepetition(int Depth)
// {
//     if (LastMovedPiecesArray[Depth].piece ==
//     LastMovedPiecesArray[Depth-2].piece &&
//         LastMovedPiecesArray[Depth].to == LastMovedPiecesArray[Depth-2].from)
//     {
//         return true;
//     }
//     return false;
// }

// void V11swapInt8(int8_t* a, int8_t* b)
// {
//     int8_t t = *a;
//     *a = *b;
//     *b = t;
// }

// void V11swapInt(int* a, int* b)
// {
//     int t = *a;
//     *a = *b;
//     *b = t;
// }

// int V11GetMoveScore(int8_t Piece, int8_t From, int8_t To, int8_t *Board, int
// *PieceValues, uint64_t *ZobristTable, int Depth, KMInfo *KillerMovesBuffer,
// int8_t ColorAtPlay, uint64_t BoardHash, TTData *TranspositionTable, int
// TTsize)
// {
//     int8_t TargetPiece = Board[To];
//     int Score = 0;
//     int PieceName = Piece & NameMask;

//     // scoring captures
//     if (TargetPiece != 0)
//     {
//         Score += (PieceValues[TargetPiece & NameMask] * 10) -
//         PieceValues[PieceName];
//     }
//     else
//     {
//         // killer moves
//         uint64_t KMHash = ZobristTable[(Piece & PieceMask) * 64 + To];
//         int KMIndex = KMHash & 8191;
//         if (KillerMovesBuffer[KMIndex].Depth == Depth &&
//         KillerMovesBuffer[KMIndex].Hash == KMHash)
//         {
//             Score += 10;
//         }
//         else
//         {
//             Score += HistoryTable[From * 64 + To] / 10000;
//         }
//         // pawn promotionm
//         if (PieceName == Pawn)
//         {
//             if (ColorAtPlay == Black && To / 8 == 7)
//             {
//                 Score += 10000;
//             }
//             else if (ColorAtPlay == White && To / 8 == 0)
//             {
//                 Score += 10000;
//             }
//         }
//     }

//     int TTindex = BoardHash & TTsize;
//     if (V11TTCanOrderMoves(BoardHash, TranspositionTable, Depth, TTindex,
//     To))
//     {
//         Score += 10000;
//     }

//     return Score;
// }

// void V11MovesQuickSort(int Low, int High, int Depth)
// {
//     int i = Low -1;
//     int Pivot = ValidMovesScoreBuffer[Depth][High];
//     if (Low >= High || High <= 0)
//     {
//         return;
//     }

//     for (int j = Low; j < High; j++)
//     {
//         if (ValidMovesScoreBuffer[Depth][j] > Pivot)
//         {
//             i++;
//             V11swapInt8(&ValidMovesBuffer[Depth][i],
//             &ValidMovesBuffer[Depth][j]);
//             V11swapInt(&ValidMovesScoreBuffer[Depth][i],
//             &ValidMovesScoreBuffer[Depth][j]);
//         }
//     }
//     V11swapInt8(&ValidMovesBuffer[Depth][i+1],
//     &ValidMovesBuffer[Depth][High]);
//     V11swapInt(&ValidMovesScoreBuffer[Depth][i+1],
//     &ValidMovesScoreBuffer[Depth][High]); if (Low < High)
//     {
//         V11MovesQuickSort(Low, i,Depth);
//         V11MovesQuickSort(i+2, High, Depth);
//     }

// }

// void V11PositionQuickSort(int Low, int High, int Depth)
// {
//     int i = Low -1;
//     int Pivot = IterativeInfoBuffer[High].Score;
//     if (Low >= High || High <= 0)
//     {
//         return;
//     }

//     for (int j = Low; j < High; j++)
//     {
//         if (IterativeInfoBuffer[j].Score > Pivot)
//         {
//             i++;
//             int LoopfirstPosIndex = 0;
//             int LoopsecondPosIndex = 0;
//             for (int index = 0; index < 17; index ++)
//             {
//                 if (PiecePositionsBuffer[Depth][index] ==
//                 IterativeInfoBuffer[i].BoardIndex)
//                 {
//                     LoopfirstPosIndex = index;
//                 }
//                 if (PiecePositionsBuffer[Depth][index] ==
//                 IterativeInfoBuffer[j].BoardIndex)
//                 {
//                     LoopsecondPosIndex = index;
//                 }
//             }

//             V11swapInt(&IterativeInfoBuffer[i].Score,
//             &IterativeInfoBuffer[j].Score);
//             V11swapInt8(&IterativeInfoBuffer[i].BoardIndex,
//             &IterativeInfoBuffer[j].BoardIndex);
//             V11swapInt8(&PiecePositionsBuffer[Depth][LoopfirstPosIndex],
//             &PiecePositionsBuffer[Depth][LoopsecondPosIndex]);
//         }
//     }
//     int firstPosIndex;
//     int secondPosIndex;
//     for (int index = 0; index < 17; index ++)
//     {
//         if (PiecePositionsBuffer[Depth][index] ==
//         IterativeInfoBuffer[i+1].BoardIndex)
//         {
//             firstPosIndex = index;
//         }
//         if (PiecePositionsBuffer[Depth][index] ==
//         IterativeInfoBuffer[High].BoardIndex)
//         {
//             secondPosIndex = index;
//         }
//     }

//     V11swapInt(&IterativeInfoBuffer[i+1].Score,
//     &IterativeInfoBuffer[High].Score);
//     V11swapInt8(&IterativeInfoBuffer[i+1].BoardIndex,
//     &IterativeInfoBuffer[High].BoardIndex);
//     V11swapInt8(&PiecePositionsBuffer[Depth][firstPosIndex],
//     &PiecePositionsBuffer[Depth][secondPosIndex]);

//     if (Low < High)
//     {
//         V11PositionQuickSort(Low, i, Depth);
//         V11PositionQuickSort(i+2, High, Depth);
//     }

// }

// void V11SortValidMoves(int Depth, int8_t Piece, int8_t *Board, int
// *PieceValues, uint64_t *ZobristTable, KMInfo *KillerMovesBuffer, int8_t From,
// int8_t ColorAtPlay, uint64_t BoardHash, TTData *TranspositionTable, int
// TTsize)
// {
//     int Low = 0;
//     int High = -1;

//     for (int i = 0; i < 28; i++)
//     {
//         if (ValidMovesBuffer[Depth][i] == -1)
//         {
//             High = i-1;
//             break;
//         }
//         ValidMovesScoreBuffer[Depth][i] = V11GetMoveScore(Piece, From,
//         ValidMovesBuffer[Depth][i], Board, PieceValues, ZobristTable, Depth,
//         KillerMovesBuffer, ColorAtPlay, BoardHash, TranspositionTable,
//         TTsize);
//     }

//     V11MovesQuickSort(Low, High, Depth);

// }

// void V11SortPiecePositions(int Depth)
// {
//     int Low = 0;
//     int High = -1;

//     for (int i = 0; i < 17; i++)
//     {
//         if (IterativeInfoBuffer[i].BoardIndex == -1)
//         {
//             High = i-1;
//             break;
//         }
//         continue;
//     }

//     V11PositionQuickSort(Low, High, Depth);

// }

// void V11FindAllPiecesOfColor(int8_t Color, int8_t Board[], int Depth, RookPos
// *myRooks)
// {
//     int FreeIndex = 0;
//     for (int i = 0; i < 64; i++)
//     {
//         if ((Board[i] & ColorMask) == Color)
//         {
//             PiecePositionsBuffer[Depth][FreeIndex] =  i;
//             FreeIndex ++;
//             if ((Board[i] & NameMask) == Rook)
//             {
//                 if (i == WhiteRookLeftStartPos || i == BlackRookLeftStartPos)
//                 {
//                     myRooks->LeftFrom = i;
//                 }
//                 else if (i == WhiteRookRightStartPos || i ==
//                 BlackRookRightStartPos)
//                 {
//                     myRooks->RightFrom = i;
//                 }
//             }
//         }
//     }
//     for (int i = FreeIndex; i < 17; i++)
//     {
//         PiecePositionsBuffer[Depth][i] = -1;
//     }
// }

// void V11GetCaptures(int8_t SelectedPiece, int8_t *Board, int8_t From, int
// Depth)
// {
//     switch (SelectedPiece&NameMask)
//     {
//         case (Pawn):
//         {
//             PawnGetCaptures(Board, From, SelectedPiece,
//             ValidMovesBuffer[Depth]); break;
//         }
//         case (Knight):
//         {
//             KnightGetCaptures(Board, From, SelectedPiece,
//             ValidMovesBuffer[Depth]); break;
//         }
//         case (Bishop):
//         {
//             BishopGetCaptures(Board, From, SelectedPiece,
//             ValidMovesBuffer[Depth]); break;
//         }
//         case (Rook):
//         {
//             RookGetCaptures(Board, From, SelectedPiece,
//             ValidMovesBuffer[Depth]); break;
//         }
//         case (Queen):
//         {
//             QueenGetCaptures(Board, From, SelectedPiece,
//             ValidMovesBuffer[Depth]); break;
//         }
//         case (King):
//         {
//             KingGetCaptures(Board, From, SelectedPiece,
//             ValidMovesBuffer[Depth]); break;
//         }

//     }
// }

// void V11MiniMaxGetValidMoves(int8_t SelectedPiece, int8_t board[], int8_t
// StartIndex, int depth)
// {
//     switch (SelectedPiece&NameMask)
//     {
//         case (Pawn):
//         {
//             MPawnGetValidMoves(board, StartIndex, SelectedPiece,
//             ValidMovesBuffer[depth]); break;
//         }
//         case (Knight):
//         {
//             MKnightGetValidMoves(board, StartIndex, SelectedPiece,
//             ValidMovesBuffer[depth]); break;
//         }
//         case (Bishop):
//         {
//             MBishopGetValidMoves(board, StartIndex, SelectedPiece,
//             ValidMovesBuffer[depth]); break;
//         }
//         case (Rook):
//         {
//             MRookGetValidMoves(board, StartIndex, SelectedPiece,
//             ValidMovesBuffer[depth]); break;
//         }
//         case (Queen):
//         {
//             MQueenGetValidMoves(board, StartIndex, SelectedPiece,
//             ValidMovesBuffer[depth]); break;
//         }
//         case (King):
//         {
//             MKingGetValidMoves(board, StartIndex, SelectedPiece,
//             ValidMovesBuffer[depth]); break;
//         }

//     }

// }

// void V11MakeMove(int8_t *Board, int8_t Piece, int8_t *CapturedPiece, int8_t
// From, int8_t To, bool *Promoted, int *WhiteValue, int *BlackValue, int*
// PieceValues, RookPos *myRooks, int Depth, int Maximizingcolour)
// {
//     *CapturedPiece = Board[To];
//     Board[To] = Piece;
//     Board[From] = 0;

//     LastMovedPiecesArray[Depth].piece = Piece;
//     LastMovedPiecesArray[Depth].to = To;
//     LastMovedPiecesArray[Depth].from = From;

//     if ((Piece & NameMask) == Pawn)
//     {
//         Board[To] &= PieceMask;

//         if ((Piece & ColorMask) == White && To / 8 == 0)
//         {
//             *Promoted = true;
//             Board[To] = White | Queen;
//             *WhiteValue += PieceValues[Queen];
//         }
//         else if ((Piece & ColorMask) == Black && To / 8 == 7)
//         {
//             *Promoted = true;
//             Board[To] = Black | Queen;
//             *BlackValue += PieceValues[Queen];

//         }

//     }

//     if (*CapturedPiece != 0)
//         V11UpdateValues(*CapturedPiece, WhiteValue, BlackValue, PieceValues,
//         1, Maximizingcolour, Promoted);

// }

// void V11UnMakeMove(int8_t *Board, int8_t Piece, int8_t From, int8_t To,
// int8_t CapturedPiece, bool Promoted, RookPos *myRooks, int *WhiteValue, int
// *BlackValue, int* PieceValues, int MaximizingColour, int8_t ColorAtPlay)
// {

//     Board[To] = CapturedPiece;
//     Board[From] = Piece;

//     if (Promoted == true)
//     {
//         if (ColorAtPlay == Black)
//         {
//             *BlackValue -= PieceValues[Queen];
//         }
//         else
//         {
//             *WhiteValue -= PieceValues[Queen];
//         }
//     }

//     V11UpdateValues(CapturedPiece, WhiteValue, BlackValue, PieceValues, -1,
//     MaximizingColour, Promoted);

// }

// int V11Evaluate(int *BlackValue, int *WhiteValue, int *Evals)
// {
//     int Score = *BlackValue - *WhiteValue;
//     (*Evals) ++;
//     return Score;
// }

// int V11Minimax(int MaxDepth, int Depth, int8_t ColorAtPlay, int8_t *Board,
// int *WhiteValue, int *BlackValue, int* PieceValues, int alpha, int beta,
// MoveInfo *myMoveInfo, int *Evals, int *cutoffs, int MaximizingColour,
// uint64_t *ZobristTable, KMInfo *KillerMovesBuffer, TTData
// *TranspositionTable, int TTsize, uint64_t BoardHash)
// {

//     int Score = (ColorAtPlay == MaximizingColour) ? -1000000 : 1000000;
//     RookPos myRooks = {0,0, false, false};
//     bool IsMaximizing = (ColorAtPlay == MaximizingColour) ? true : false;

//     const int WhiteKing = King | White;
//     const int BlackKing = King | Black;
//     const int OpponentKing = (ColorAtPlay == White) ? BlackKing : WhiteKing;

//     // null move pruning
//     if (MaxDepth - Depth >= 3 && (*WhiteValue + *BlackValue)>= 21500)
//     {
//         int R = 2;
//         int Nalpha = IsMaximizing ? beta - 1: alpha;
//         int Nbeta = IsMaximizing ? beta: alpha +1;

//         BoardHash ^= (ColorAtPlay * 64);

//         int NullMoveScore = V11Minimax(MaxDepth, Depth+1 + R,
//         ColorAtPlay^ColorMask, Board, WhiteValue, BlackValue, PieceValues,
//         Nalpha, Nbeta, myMoveInfo, Evals, cutoffs, MaximizingColour,
//         ZobristTable, KillerMovesBuffer, TranspositionTable, TTsize,
//         BoardHash);

//         BoardHash ^= (ColorAtPlay * 64);

//         if (IsMaximizing)
//         {
//             if (NullMoveScore >= beta)
//             {
//                 return beta;
//             }
//         }
//         else
//         {
//             if (NullMoveScore <= alpha)
//             {
//                 return alpha;
//             }
//         }
//     }

//     V11FindAllPiecesOfColor(ColorAtPlay, Board, Depth, &myRooks);

//     int FreeIterIndex = 0;

//     if (Depth == 1 && MaxDepth != 2)
//     {

//         V11SortPiecePositions(Depth);

//         for (int IterIndex = 0; IterIndex < 17; IterIndex++)
//         {
//             IterativeInfoBuffer[IterIndex].BoardIndex = -1;
//         }
//         FreeIterIndex = 0;
//     }

//     for (int PieceIndex = 0; PieceIndex < 17; PieceIndex++)
//     {
//         int8_t PiecePosition = PiecePositionsBuffer[Depth][PieceIndex];
//         int8_t Piece = Board[PiecePosition];
//         int8_t PieceOnly = Piece & PieceMask;

//         if (PiecePosition == -1)
//             break;

//         V11MiniMaxGetValidMoves(Piece, Board, PiecePosition, Depth);

//         if (Depth != MaxDepth)
//             V11SortValidMoves(Depth, Piece, Board, PieceValues, ZobristTable,
//             KillerMovesBuffer, PiecePosition, ColorAtPlay, BoardHash,
//             TranspositionTable, TTsize);

//         if (Depth == 1)
//         {
//             IterativeInfoBuffer[FreeIterIndex].BoardIndex = PiecePosition;
//             IterativeInfoBuffer[FreeIterIndex].Score = INT32_MIN;
//             FreeIterIndex ++;
//         }

//         for (int MoveIndex = 0; MoveIndex < 28; MoveIndex++)
//         {
//             int8_t CapturedPiece = 0;
//             int8_t Move = ValidMovesBuffer[Depth][MoveIndex];
//             if (Move == -1)
//                 break;

//             bool Promoted = false;

//             V11MakeMove(Board, Piece, &CapturedPiece, PiecePosition, Move,
//             &Promoted, WhiteValue, BlackValue, PieceValues, &myRooks, Depth,
//             MaximizingColour);

//             BoardHash ^= ZobristTable[PieceOnly * 64 + PiecePosition];
//             BoardHash ^= ZobristTable[(CapturedPiece & PieceMask) * 64 +
//             Move]; BoardHash ^= ZobristTable[PieceOnly * 64 + Move];

//             int MiniMaxScore;

//             if (Depth == MaxDepth)
//             {

//                 int EvalScore = V11Evaluate(BlackValue, WhiteValue, Evals);
//                 if (ColorAtPlay == MaximizingColour)
//                 {
//                     if (EvalScore > Score)
//                     {
//                         Score = EvalScore;
//                         BestMoveBuffer[Depth] = Move;
//                         BestMoveFromBuffer[Depth] = PiecePosition;
//                     }
//                 }
//                 else
//                 {
//                     if (EvalScore < Score)
//                     {
//                         Score = EvalScore;
//                         BestMoveBuffer[Depth] = Move;
//                         BestMoveFromBuffer[Depth] = PiecePosition;
//                     }

//                 }

//             }
//             else
//             {
//                 if ((CapturedPiece & PieceMask) == OpponentKing)
//                 {
//                     MiniMaxScore = (ColorAtPlay == MaximizingColour) ?
//                     10000000 - (1 << Depth): -10000000 + (1 << Depth);
//                 }
//                 else
//                 {
//                     int TTindex = BoardHash & TTsize;

//                     if (V11Contains(BoardHash, TranspositionTable, Depth,
//                     TTindex, MaxDepth))
//                     {

//                         MiniMaxScore = TranspositionTable[TTindex].Score;

//                     }
//                     else
//                     {

//                         MiniMaxScore = V11Minimax(MaxDepth, Depth+1,
//                         ColorAtPlay^ColorMask, Board, WhiteValue, BlackValue,
//                         PieceValues, alpha, beta, myMoveInfo, Evals, cutoffs,
//                         MaximizingColour, ZobristTable, KillerMovesBuffer,
//                         TranspositionTable, TTsize, BoardHash);
//                         V11AddKeyValuePair(TranspositionTable, Depth,
//                         MiniMaxScore, TTindex, BoardHash, MaxDepth);
//                     }
//                 }

//                 if (V11CheckRepetition(Depth))
//                 {
//                     if (IsMaximizing)
//                     {
//                         MiniMaxScore -= 50;
//                     }
//                     else
//                     {
//                         MiniMaxScore += 50;

//                     }
//                 }

//                 if (ColorAtPlay == MaximizingColour)
//                 {
//                     if (MiniMaxScore > Score)
//                     {
//                         Score = MiniMaxScore;
//                         BestMoveBuffer[Depth] = Move;
//                         BestMoveFromBuffer[Depth] = PiecePosition;
//                     }
//                 }
//                 else
//                 {
//                     if (MiniMaxScore < Score)
//                     {
//                         Score = MiniMaxScore;
//                         BestMoveBuffer[Depth] = Move;
//                         BestMoveFromBuffer[Depth] = PiecePosition;
//                     }

//                 }

//                 if (Depth == 1)
//                 {
//                     // info for iterative deepening
//                     for (int IterIndex = 0; IterIndex < FreeIterIndex;
//                     IterIndex++)
//                     {
//                         if(IterativeInfoBuffer[IterIndex].BoardIndex ==
//                         PiecePosition)
//                         {
//                             if (IterativeInfoBuffer[IterIndex].Score <
//                             MiniMaxScore)
//                             {
//                                 IterativeInfoBuffer[IterIndex].Score =
//                                 MiniMaxScore; break;
//                             }
//                         }
//                     }

//                     if (Score > myMoveInfo->Score)
//                     {
//                         myMoveInfo->FromIndex = PiecePosition;
//                         myMoveInfo->PieceToMove = Promoted ? ColorAtPlay |
//                         Queen : Piece; myMoveInfo->Score = Score;
//                         myMoveInfo->ToIndex = Move;
//                     }

//                 }

//             }

//             BoardHash ^= ZobristTable[PieceOnly * 64 + Move];
//             BoardHash ^= ZobristTable[(CapturedPiece & PieceMask) * 64 +
//             Move]; BoardHash ^= ZobristTable[PieceOnly * 64 + PiecePosition];

//             V11UnMakeMove(Board, Piece, PiecePosition, Move, CapturedPiece,
//             Promoted, &myRooks, WhiteValue, BlackValue, PieceValues,
//             MaximizingColour, ColorAtPlay);

//             if (IsMaximizing)
//             {
//                 if (Score > alpha)
//                 {
//                     alpha = Score;
//                 }
//             }
//             else
//             {
//                 if (Score < beta)
//                 {
//                     beta = Score;
//                 }
//             }
//             if (beta <= alpha)
//             {
//                 //  quiet move pruning
//                 if (CapturedPiece == 0)
//                 {
//                     //  killer moves
//                     uint64_t KMHash = ZobristTable[(Piece & PieceMask) * 64 +
//                     Move]; int KMIndex = KMHash & 8191;

//                     KillerMovesBuffer[KMIndex].Depth = Depth;
//                     KillerMovesBuffer[KMIndex].Hash = KMHash;

//                     HistoryTable[PiecePosition * 64 + Move] += Depth;

//                 }

//                 (*cutoffs) ++;
//                 return Score;
//             }

//         }

//     }

//     return Score;
// }

// int V11StartIterativeDepening(int StartDepth, int Depth, int8_t ColorAtPlay,
// int8_t *Board, int *WhiteValue, int *BlackValue, int* PieceValues, int alpha,
// int beta, int *Evals, int *cutoffs, uint64_t *ZobristTable)
// {

//     int Score = 0;
//     float MaxTime = 1;
//     MoveInfo myMoveInfo;

//     static KMInfo KillerMovesBuffer[8191] = {0};

//     struct timespec start, end;

//     clock_gettime(CLOCK_MONOTONIC, &start);

//     for (int IterIndex = 0; IterIndex < 17; IterIndex++)
//     {
//         IterativeInfoBuffer[IterIndex].BoardIndex = -1;
//     }

//     const int TTsize = 1048575;
//     static TTData TranspositionTable[TTsize] = {0};
//     uint64_t BoardHash = 0;
//     V11CalculateInitialHash(Board, &BoardHash, ZobristTable);

//     for (int MaxDepth = 2; MaxDepth < 77; MaxDepth ++)
//     {
//         clock_gettime(CLOCK_MONOTONIC, &end);
//         double elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//         if (elapsed > MaxTime)
//         {
//             FILE *file = fopen("output.txt", "a");
//             fprintf(file, "max depth %d", MaxDepth-1);
//             fprintf(file, "\n");
//             fclose(file);
//             break;

//         }

//         memset(KillerMovesBuffer, 0, sizeof(KMInfo) * 8191);

//         myMoveInfo.FromIndex = 0;
//         myMoveInfo.PieceToMove = 0;
//         myMoveInfo.ToIndex = 0;
//         myMoveInfo.Score = -1000000;

//         Score = V11Minimax(MaxDepth,StartDepth, ColorAtPlay, Board,
//         WhiteValue, BlackValue, PieceValues, alpha, beta, &myMoveInfo, Evals,
//         cutoffs, ColorAtPlay, ZobristTable, KillerMovesBuffer,
//         TranspositionTable, TTsize, BoardHash);

//         // aspiration windows
//         if (Score <= alpha) {
//             // Fail-low widen window downward and re-search
//             memset(KillerMovesBuffer, 0, sizeof(KMInfo) * 8191);
//             memset(TranspositionTable, 0, sizeof(TTData) * TTsize);
//             alpha = -1000000000;
//             beta = 1000000000;
//             myMoveInfo.FromIndex = 0;
//             myMoveInfo.PieceToMove = 0;
//             myMoveInfo.ToIndex = 0;
//             myMoveInfo.Score = -1000000;
//             Score = V11Minimax(MaxDepth,StartDepth, ColorAtPlay, Board,
//             WhiteValue, BlackValue, PieceValues, alpha, beta, &myMoveInfo,
//             Evals, cutoffs, ColorAtPlay, ZobristTable, KillerMovesBuffer,
//             TranspositionTable, TTsize, BoardHash);
//         }
//         else if (Score >= beta) {
//             // Fail-high widen window upward and re-search
//             memset(KillerMovesBuffer, 0, sizeof(KMInfo) * 8191);
//             memset(TranspositionTable, 0, sizeof(TTData) * TTsize);
//             alpha = -1000000000;
//             beta =  1000000000;
//             myMoveInfo.FromIndex = 0;
//             myMoveInfo.PieceToMove = 0;
//             myMoveInfo.ToIndex = 0;
//             myMoveInfo.Score = -1000000;
//             Score = V11Minimax(MaxDepth,StartDepth, ColorAtPlay, Board,
//             WhiteValue, BlackValue, PieceValues, alpha, beta, &myMoveInfo,
//             Evals, cutoffs, ColorAtPlay, ZobristTable, KillerMovesBuffer,
//             TranspositionTable, TTsize, BoardHash);
//         }

//         if (MaxDepth % 2 == 1)
//         {
//             alpha = Score - 310;
//             beta = Score + 210;
//         }
//         else
//         {
//             alpha = Score - 210;
//             beta = Score + 310;
//         }

//         if ((ColorAtPlay == Black && Score > 100000) ||
//             (ColorAtPlay == White && Score < -100000))
//             break;
//     }

//     // move on main board

//     Board[myMoveInfo.FromIndex] = 0;
//     Board[myMoveInfo.ToIndex] = myMoveInfo.PieceToMove;

//     if ((myMoveInfo.PieceToMove & NameMask) == Pawn)
//     {
//         Board[myMoveInfo.ToIndex] &= PieceMask;
//     }

//     return Score;
// }

// void MinimaxStarterV11(int8_t *Board, int8_t MaximizingColor, uint64_t
// *ZobristTable)
// {
//     struct timespec start, end;

//     int Evals = 0;
//     int cutoffs = 0;
//     int8_t MaximizingColour = 0;

//     BlackCanCastleRight = true;
//     BlackCanCastleLeft = true;
//     WhiteCanCastleRight = true;
//     WhiteCanCastleLeft = true;
//     int StartDepth = 1;

//     int alpha = -1000000000;
//     int beta = 1000000000;

//     int WhiteValue = 0;
//     int BlackValue = 0;
//     int Score = 0;
//     Evals = 0;
//     cutoffs =0;

//     MaximizingColour = MaximizingColor;

//     static int PieceValues[] = {0,100,320,330,500,900,10000};

//     V11CalculateInitialMaterial(Board, &WhiteValue, &BlackValue, PieceValues,
//     MaximizingColour);

//     clock_gettime(CLOCK_MONOTONIC, &start);

//     Score = V11StartIterativeDepening(StartDepth, StartDepth,
//     MaximizingColour, Board, &WhiteValue, &BlackValue, PieceValues, alpha,
//     beta, &Evals, &cutoffs, ZobristTable);

//     clock_gettime(CLOCK_MONOTONIC, &end);

//     double elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//     V11PrintBoardToFile(Board, "output.txt", Evals, elapsed, Score, cutoffs);
// }

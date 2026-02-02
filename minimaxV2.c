// #include "config.h"
// #include "pieces.h"
// #include <stdint.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>

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

// static int8_t PiecePositionsBuffer[30][17];
// static int8_t ValidMovesBuffer[30][28];
// static int8_t ValidMovesScoreBuffer[30][28];
// static IterativeInfo IterativeInfoBuffer[17];
// static LastMovedPieces LastMovedPiecesArray[30];

// void V2CalculateInitialMaterial(int8_t *Board, int *WhiteValue, int
// *BlackValue, int* PieceValues, int MaximizingColour)
// {
//     *WhiteValue = 0;
//     *BlackValue = 0;

//     for (int i = 0; i < 64; i++)
//     {
//         int8_t piece = Board[i];
//         if (piece == 0)
//             continue;

//         if ((piece & ColorMask) == MaximizingColour)
//             *BlackValue += PieceValues[piece & NameMask];
//         else
//             *WhiteValue += PieceValues[piece & NameMask];
//     }
// }

// void V2WriteArrayToFile(const char* filename, int* array, int length)
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

// void V2PrintBoardToFile(int8_t *board, const char *filename, int boardNumber,
// double time, int Score, int cutoffs) {
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

// void V2UpdateValues(int8_t CapturedPiece, int *WhiteValue, int *BlackValue,
// int *PieceValues, int reverse, int MaximizingColour)
// {
//     if ((CapturedPiece & ColorMask) == MaximizingColour)
//     {
//         *BlackValue -= PieceValues[CapturedPiece&NameMask] * reverse;
//     }
//     else
//     {
//         *WhiteValue -= PieceValues[CapturedPiece&NameMask] * reverse;
//     }
// }

// void V2MiniMaxCheckCastleRights(int8_t SelectedPiece, int8_t StopIndex,
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

// bool V2CheckRepetition(int Depth)
// {
//     if (LastMovedPiecesArray[Depth].piece ==
//     LastMovedPiecesArray[Depth-2].piece &&
//         LastMovedPiecesArray[Depth].to == LastMovedPiecesArray[Depth-2].from)
//     {
//         return true;
//     }
//     return false;
// }

// void V2swapInt8(int8_t* a, int8_t* b)
// {
//     int8_t t = *a;
//     *a = *b;
//     *b = t;
// }

// void V2swapInt(int* a, int* b)
// {
//     int t = *a;
//     *a = *b;
//     *b = t;
// }

// void V2MovesQuickSort(int Low, int High, int Depth)
// {
//     int i = Low -1;
//     int Pivot = ValidMovesScoreBuffer[Depth][High];
//     if (High <= 0)
//     {
//         return;
//     }

//     for (int j = Low; j < High; j++)
//     {
//         if (ValidMovesScoreBuffer[Depth][j] > Pivot)
//         {
//             i++;
//             V2swapInt8(&ValidMovesBuffer[Depth][i],
//             &ValidMovesBuffer[Depth][j]);
//             V2swapInt8(&ValidMovesScoreBuffer[Depth][i],
//             &ValidMovesScoreBuffer[Depth][j]);
//         }
//     }
//     V2swapInt8(&ValidMovesBuffer[Depth][i+1],
//     &ValidMovesBuffer[Depth][High]);
//     V2swapInt8(&ValidMovesScoreBuffer[Depth][i+1],
//     &ValidMovesScoreBuffer[Depth][High]); if (Low < High)
//     {
//         V2MovesQuickSort(Low, i,Depth);
//         V2MovesQuickSort(i+2, High, Depth);
//     }

// }

// void V2PositionQuickSort(int Low, int High, int Depth)
// {
//     int i = Low -1;
//     int Pivot = IterativeInfoBuffer[High].Score;
//     if (High <= 0)
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

//             V2swapInt(&IterativeInfoBuffer[i].Score,
//             &IterativeInfoBuffer[j].Score);
//             V2swapInt8(&IterativeInfoBuffer[i].BoardIndex,
//             &IterativeInfoBuffer[j].BoardIndex);
//             V2swapInt8(&PiecePositionsBuffer[Depth][LoopfirstPosIndex],
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

//     V2swapInt(&IterativeInfoBuffer[i+1].Score,
//     &IterativeInfoBuffer[High].Score);
//     V2swapInt8(&IterativeInfoBuffer[i+1].BoardIndex,
//     &IterativeInfoBuffer[High].BoardIndex);
//     V2swapInt8(&PiecePositionsBuffer[Depth][firstPosIndex],
//     &PiecePositionsBuffer[Depth][secondPosIndex]);

//     if (Low < High)
//     {
//         V2PositionQuickSort(Low, i, Depth);
//         V2PositionQuickSort(i+2, High, Depth);
//     }

// }

// int V2GetMoveScore(int8_t Piece, int8_t To, int8_t *Board, int *PieceValues,
// uint64_t *ZobristTable, int Depth, KMInfo *KillerMovesBuffer)
// {
//     int8_t TargetPiece = Board[To];
//     int Score = 0;

//     if (TargetPiece != 0)
//     {
//         Score += (PieceValues[TargetPiece & NameMask] * 100) -
//         PieceValues[Piece & NameMask];
//     }

//     uint64_t KMHash = ZobristTable[(Piece & PieceMask) * 64 + To];
//     int KMIndex = KMHash & 8191;
//     if (KillerMovesBuffer[KMIndex].Depth == Depth &&
//     KillerMovesBuffer[KMIndex].Hash == KMHash)
//     {
//         Score += 10;
//     }

//     return Score;
// }

// void V2SortValidMoves(int Depth, int8_t Piece, int8_t *Board, int
// *PieceValues, uint64_t *ZobristTable, KMInfo *KillerMovesBuffer)
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
//         ValidMovesScoreBuffer[Depth][i] = V2GetMoveScore(Piece,
//         ValidMovesBuffer[Depth][i], Board, PieceValues, ZobristTable, Depth,
//         KillerMovesBuffer);
//     }

//     V2MovesQuickSort(Low, High, Depth);

// }

// void V2SortPiecePositions(int Depth)
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

//     V2PositionQuickSort(Low, High, Depth);

// }

// void V2FindAllPiecesOfColor(int8_t Color, int8_t Board[], int Depth, RookPos
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

// void V2MiniMaxGetValidMoves(int8_t SelectedPiece, int8_t board[], int8_t
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

// void V2MakeMove(int8_t *Board, int8_t Piece, int8_t *CapturedPiece, int8_t
// From, int8_t To, bool *Castled, int *WhiteValue, int *BlackValue, int*
// PieceValues, RookPos *myRooks, int Depth, int Maximizingcolour)
// {
//     *CapturedPiece = Board[To];
//     Board[To] = Piece;
//     Board[From] = 0;

//     LastMovedPiecesArray[Depth].piece = Piece;
//     LastMovedPiecesArray[Depth].to = To;
//     LastMovedPiecesArray[Depth].from = From;

//     // MiniMaxCheckCastleRights(Piece, To, Board, From, Castled, myRooks);

//     if ((Piece & NameMask) == Pawn)
//     {
//         Board[To] &= PieceMask;
//     }

//     if (*CapturedPiece != 0)
//         V2UpdateValues(*CapturedPiece, WhiteValue, BlackValue, PieceValues,
//         1, Maximizingcolour);

// }

// void V2UnMakeMove(int8_t *Board, int8_t Piece, int8_t From, int8_t To, int8_t
// CapturedPiece, bool Castled, RookPos *myRooks, int *WhiteValue, int
// *BlackValue, int* PieceValues, int MaximizingColour)
// {

//     // if (Castled == true)
//     // {
//     //     if(myRooks->CastledLeft == true)
//     //     {
//     //         Board[myRooks->LeftFrom] = Board[myRooks->LeftFrom + 3];
//     //         Board[myRooks->LeftFrom + 3] = 0;
//     //         Piece |= CastleLeft;
//     //         if ((Piece & ColorMask) == Black)
//     //             BlackCanCastleLeft = true;
//     //         else
//     //             WhiteCanCastleLeft = true;
//     //     }
//     //     if(myRooks->CastledRight == true)
//     //     {
//     //         Board[myRooks->RightFrom] = Board[myRooks->RightFrom - 2];
//     //         Board[myRooks->LeftFrom - 2] = 0;
//     //         Piece |= CastleRight;
//     //         if ((Piece & ColorMask) == Black)
//     //             BlackCanCastleRight = true;
//     //         else
//     //             WhiteCanCastleRight = true;
//     //     }
//     // }
//     Board[To] = CapturedPiece;
//     Board[From] = Piece;

//     V2UpdateValues(CapturedPiece, WhiteValue, BlackValue, PieceValues, -1,
//     MaximizingColour);

// }

// int V2Evaluate(int *BlackValue, int *WhiteValue, int *Evals)
// {
//     int Score = *BlackValue - *WhiteValue;
//     (*Evals) ++;
//     return Score;
// }

// int V2Minimax(int MaxDepth, int Depth, int8_t ColorAtPlay, int8_t *Board, int
// *WhiteValue, int *BlackValue, int* PieceValues, int alpha, int beta, MoveInfo
// *myMoveInfo, int *Evals, int *cutoffs, int MaximizingColour, uint64_t
// *ZobristTable, KMInfo *KillerMovesBuffer)
// {
//     int Score = (ColorAtPlay == MaximizingColour) ? -1000000 : 1000000;
//     RookPos myRooks = {0,0, false, false};

//     V2FindAllPiecesOfColor(ColorAtPlay, Board, Depth, &myRooks);

//     int FreeIterIndex = 0;

//     if (Depth == 1 && MaxDepth != 2)
//     {

//         V2SortPiecePositions(Depth);

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

//         if (PiecePosition == -1)
//             break;

//         V2MiniMaxGetValidMoves(Piece, Board, PiecePosition, Depth);

//         V2SortValidMoves(Depth, Piece, Board, PieceValues, ZobristTable,
//         KillerMovesBuffer);

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
//                 continue;

//             bool Castled = false;
//             V2MakeMove(Board, Piece, &CapturedPiece, PiecePosition, Move,
//             &Castled, WhiteValue, BlackValue, PieceValues, &myRooks, Depth,
//             MaximizingColour);

//             int MiniMaxScore;

//             bool IsMaximizing = (ColorAtPlay == MaximizingColour) ? true :
//             false;

//             if (Depth == MaxDepth)
//             {
//                 int EvalScore = V2Evaluate(BlackValue, WhiteValue, Evals);
//                 if (ColorAtPlay == MaximizingColour)
//                 {
//                     if (EvalScore > Score)
//                     {
//                         Score = EvalScore;
//                     }
//                 }
//                 else
//                 {
//                     if (EvalScore < Score)
//                     {
//                         Score = EvalScore;
//                     }

//                 }

//             }
//             else
//             {
//                 MiniMaxScore = V2Minimax(MaxDepth, Depth+1,
//                 ColorAtPlay^ColorMask, Board, WhiteValue, BlackValue,
//                 PieceValues, alpha, beta, myMoveInfo, Evals, cutoffs,
//                 MaximizingColour, ZobristTable, KillerMovesBuffer);

//                 if (V2CheckRepetition(Depth))
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

//                 if (IsMaximizing)
//                 {
//                     if (MiniMaxScore > Score)
//                     {
//                         Score = MiniMaxScore;
//                     }
//                 }
//                 else
//                 {
//                     if (MiniMaxScore < Score)
//                     {
//                         Score = MiniMaxScore;
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
//                         myMoveInfo->PieceToMove = Piece;
//                         myMoveInfo->Score = Score;
//                         myMoveInfo->ToIndex = Move;
//                     }

//                 }

//             }

//             V2UnMakeMove(Board, Piece, PiecePosition, Move, CapturedPiece,
//             Castled, &myRooks, WhiteValue, BlackValue, PieceValues,
//             MaximizingColour);

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
//                     uint64_t KMHash = ZobristTable[(Piece & PieceMask) * 64 +
//                     Move]; int KMIndex = KMHash & 8191;

//                     KillerMovesBuffer[KMIndex].Depth = Depth;
//                     KillerMovesBuffer[KMIndex].Hash = KMHash;
//                 }

//                 (*cutoffs) ++;
//                 return Score;
//             }

//         }

//     }

//     return Score;
// }

// int V2StartIterativeDepening(int StartDepth, int Depth, int8_t ColorAtPlay,
// int8_t *Board, int *WhiteValue, int *BlackValue, int* PieceValues, int alpha,
// int beta, int *Evals, int *cutoffs, uint64_t *ZobristTable)
// {
//     int Score;
//     float MaxTime = 1000;
//     MoveInfo myMoveInfo;

//     static KMInfo KillerMovesBuffer[8191];

//     struct timespec start, end;

//     clock_gettime(CLOCK_MONOTONIC, &start);

//     for (int IterIndex = 0; IterIndex < 17; IterIndex++)
//     {
//         IterativeInfoBuffer[IterIndex].BoardIndex = -1;
//     }

//     for (int MaxDepth = 2; MaxDepth < 7; MaxDepth ++)
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

//         myMoveInfo.FromIndex = 0;
//         myMoveInfo.PieceToMove = 0;
//         myMoveInfo.ToIndex = 0;
//         myMoveInfo.Score = -1000000;

//         Score = V2Minimax(MaxDepth,StartDepth, ColorAtPlay, Board,
//         WhiteValue, BlackValue, PieceValues, alpha, beta, &myMoveInfo, Evals,
//         cutoffs, ColorAtPlay, ZobristTable, KillerMovesBuffer);

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

// void MinimaxStarterV2(int8_t *Board, int8_t MaximizingColor, uint64_t
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

//     int alpha = -100000;
//     int beta = 100000;

//     int WhiteValue = 0;
//     int BlackValue = 0;
//     int Score = 0;
//     Evals = 0;
//     cutoffs =0;

//     MaximizingColour = MaximizingColor;

//     static int PieceValues[] = {0,100,320,330,500,900,10000};

//     V2CalculateInitialMaterial(Board, &WhiteValue, &BlackValue, PieceValues,
//     MaximizingColour);

//     clock_gettime(CLOCK_MONOTONIC, &start);

//     Score = V2StartIterativeDepening(StartDepth, StartDepth,
//     MaximizingColour, Board, &WhiteValue, &BlackValue, PieceValues, alpha,
//     beta, &Evals, &cutoffs, ZobristTable);

//     clock_gettime(CLOCK_MONOTONIC, &end);

//     double elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//     V2PrintBoardToFile(Board, "output.txt", Evals, elapsed, Score, cutoffs);
// }

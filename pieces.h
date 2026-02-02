#ifndef PIECES
#define PIECES
#include <stdint.h>

int8_t* PawnGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece);
void MPawnGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece, int8_t *ValidMovesBuffer);
void PawnGetCaptures(int8_t* board, int8_t startIndex, int8_t piece, int8_t *CapturesBuffer);
int8_t* KnightGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece);
void MKnightGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece, int8_t *ValidMovesBuffer);
void KnightGetCaptures(int8_t* board, int8_t startIndex, int8_t piece, int8_t *CapturesBuffer);
int8_t* BishopGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece);
void MBishopGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece, int8_t *ValidMovesBuffer);
void BishopGetCaptures(int8_t* board, int8_t startIndex, int8_t piece, int8_t *CapturesBuffer);
int8_t* RookGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece);
void MRookGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece, int8_t *ValidMovesBuffer);
void RookGetCaptures(int8_t* board, int8_t startIndex, int8_t piece, int8_t *CapturesBuffer);
int8_t* QueenGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece);
void MQueenGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece, int8_t *ValidMovesBuffer);
void QueenGetCaptures(int8_t* board, int8_t startIndex, int8_t piece, int8_t *CapturesBuffer);
int8_t* KingGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece);
void MKingGetValidMoves(int8_t* board, int8_t startIndex, int8_t piece, int8_t *ValidMovesBuffer);
void KingGetCaptures(int8_t* board, int8_t startIndex, int8_t piece, int8_t *CapturesBuffer);
void KnightGenerateValidMoves(void);

#endif

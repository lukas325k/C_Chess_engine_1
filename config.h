#include <stdbool.h>
#include <stdint.h>
#define ScreenWidth 1000
#define ScreenHeight 1000
#define TILE_SIZE (ScreenWidth / 8)
#define tilesInRow 8
#define LIGHT_TILE (Color){240, 217, 181, 255}
#define DARK_TILE (Color){181, 136, 99, 255}
#define ATTACKED_TILE (Color){255, 0, 0, 50}

#define WhiteKingStartPos 60
#define WhiteRookLeftStartPos 56
#define WhiteRookRightStartPos 63
#define BlackKingStartPos 4
#define BlackRookLeftStartPos 0
#define BlackRookRightStartPos 7

#define BlackPieceIndex 0
#define WhitePieceIndex 1

#define Pawn 0x01   // 0000 0001
#define Knight 0x02 // 0000 0010
#define Bishop 0x03 // 0000 0011
#define Rook 0x04   // 0000 0100
#define Queen 0x05  // 0000 0101
#define King 0x06   // 0000 0110

#define White 0x08 // 0000 1000
#define Black 0x10 // 0001 0000

#define Pawn2Up 0x20 // 0010 0000

#define CastleLeft 0x20  // 0010 0000
#define CastleRight 0x40 // 0100 0000

#define NameMask 0x07        // 0000 0111
#define ColorMask 0x18       // 0001 1000
#define Pawn2UpMask 0x20     // 0010 0000
#define PieceMask 0x1F       // 0001 1111
#define CastleLeftMask 0x20  // 0010 0000
#define CastleRightMask 0x40 // 0100 0000

#define KnightsToPawnsSubtraction 3
#define RooksToPawnsAdition 4
#define NumOrigPawnsIndex 7

extern bool BlackCanCastleRight;
extern bool BlackCanCastleLeft;
extern bool WhiteCanCastleRight;
extern bool WhiteCanCastleLeft;

void MinimaxStarterV1(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV2(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV3(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV4(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV5(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV6(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV7(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV8(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV9(int8_t *board, int8_t MaximizinColor,
                      uint64_t *ZobristTable);
void MinimaxStarterV10(int8_t *board, int8_t MaximizinColor,
                       uint64_t *ZobristTable);
void MinimaxStarterV11(int8_t *board, int8_t MaximizinColor,
                       uint64_t *ZobristTable);

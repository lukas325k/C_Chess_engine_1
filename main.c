
#include <raylib.h>

#include "config.h"
#include "pieces.h"

#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

Texture2D whitePawn;
Texture2D blackPawn;
Texture2D whiteKnight;
Texture2D blackKnight;
Texture2D whiteBishop;
Texture2D blackBishop;
Texture2D whiteRook;
Texture2D blackRook;
Texture2D whiteQueen;
Texture2D blackQueen;
Texture2D whiteKing;
Texture2D blackKing;

int8_t board[64];
const char *StartFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int8_t SelectedPiece;
int8_t StartIndex;
int8_t StopIndex;

bool BlackCanCastleRight = true;
bool BlackCanCastleLeft = true;
bool WhiteCanCastleRight = true;
bool WhiteCanCastleLeft = true;

uint64_t *ZobristTable;

int eval = 0;

uint64_t rand64() {
  uint64_t r;
  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, &r, sizeof(r));
  close(fd);
  return r;
}

uint64_t *InitializeZobristHashing() {

  static uint64_t ZobristTable[23 * 64];
  srand(time(NULL));

  for (int Piece = 0; Piece < 23; Piece++) {
    for (int from = 0; from < 64; from++) {
      ZobristTable[(Piece * 64) + from] = rand64();
    }
  }

  return ZobristTable;
}

bool IsInArray(int8_t value, int8_t array[], int size) {
  for (int i = 0; i < size; i++) {
    if (array[i] == value) {
      return true;
    }
  }
  return false;
}

int GetArrayLength(int8_t *Array) {
  int lenght = 0;
  for (int i = 0; Array[i] != -1; i++) {
    lenght++;
  }
  return lenght;
}

void DrawValidMoves(int8_t *ValidMoves) {
  int x;
  int y;
  for (int i = 0; i < GetArrayLength(ValidMoves); i++) {
    int8_t Pos = ValidMoves[i];
    x = Pos % 8;
    y = Pos / 8;
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                  ATTACKED_TILE);
  }
}

void LoadTextures(void) {
  whitePawn = LoadTexture("C/chess/pieces-basic-png/white-pawn.png");
  blackPawn = LoadTexture("C/chess/pieces-basic-png/black-pawn.png");
  whiteKnight = LoadTexture("C/chess/pieces-basic-png/white-knight.png");
  blackKnight = LoadTexture("C/chess/pieces-basic-png/black-knight.png");
  whiteBishop = LoadTexture("C/chess/pieces-basic-png/white-bishop.png");
  blackBishop = LoadTexture("C/chess/pieces-basic-png/black-bishop.png");
  whiteRook = LoadTexture("C/chess/pieces-basic-png/white-rook.png");
  blackRook = LoadTexture("C/chess/pieces-basic-png/black-rook.png");
  whiteQueen = LoadTexture("C/chess/pieces-basic-png/white-queen.png");
  blackQueen = LoadTexture("C/chess/pieces-basic-png/black-queen.png");
  whiteKing = LoadTexture("C/chess/pieces-basic-png/white-king.png");
  blackKing = LoadTexture("C/chess/pieces-basic-png/black-king.png");
}

void DrawBoard(void) {
  ClearBackground(RAYWHITE);
  for (int y = 0; y < tilesInRow; y++) {
    for (int x = 0; x < tilesInRow; x++) {

      DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                    (x + y) % 2 == 0 ? LIGHT_TILE : DARK_TILE);
    }
  }
}

void DrawPieces(void) {
  for (int i = 0; i < 64; i++) {
    switch (board[i] & PieceMask) {
    case 0:
      break;
    case Pawn | Black: {
      DrawTexture(blackPawn, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Pawn | White: {
      DrawTexture(whitePawn, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Knight | Black: {
      DrawTexture(blackKnight, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Knight | White: {
      DrawTexture(whiteKnight, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Bishop | Black: {
      DrawTexture(blackBishop, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Bishop | White: {
      DrawTexture(whiteBishop, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Rook | Black: {
      DrawTexture(blackRook, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Rook | White: {
      DrawTexture(whiteRook, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Queen | Black: {
      DrawTexture(blackQueen, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case Queen | White: {
      DrawTexture(whiteQueen, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case King | Black: {
      DrawTexture(blackKing, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    case King | White: {
      DrawTexture(whiteKing, (i % 8) * TILE_SIZE, (i / 8) * TILE_SIZE, WHITE);
      break;
    }
    }
  }
}

void FenToBoard(const char *Fen) {
  int BoardIndex = 0;
  for (int i = 0; i < (int)strlen(Fen); i++) {
    switch (Fen[i]) {
    case 'p': {
      if (BoardIndex / 8 == 1)
        board[BoardIndex] = Pawn | Black | Pawn2Up;
      else
        board[BoardIndex] = Pawn | Black;

      BoardIndex++;
      break;
    }
    case 'P': {
      if (BoardIndex / 8 == 6)
        board[BoardIndex] = Pawn | White | Pawn2Up;
      else
        board[BoardIndex] = Pawn | White;
      BoardIndex++;
      break;
    }
    case 'n': {
      board[BoardIndex] = Knight | Black;
      BoardIndex++;
      break;
    }
    case 'N': {
      board[BoardIndex] = Knight | White;
      BoardIndex++;
      break;
    }
    case 'b': {
      board[BoardIndex] = Bishop | Black;
      BoardIndex++;
      break;
    }
    case 'B': {
      board[BoardIndex] = Bishop | White;
      BoardIndex++;
      break;
    }
    case 'r': {
      board[BoardIndex] = Rook | Black;
      BoardIndex++;
      break;
    }
    case 'R': {
      board[BoardIndex] = Rook | White;
      BoardIndex++;
      break;
    }
    case 'q': {
      board[BoardIndex] = Queen | Black;
      BoardIndex++;
      break;
    }
    case 'Q': {
      board[BoardIndex] = Queen | White;
      BoardIndex++;
      break;
    }
    case 'k': {
      board[BoardIndex] = King | Black;
      if (BoardIndex == BlackKingStartPos) {
        if (BlackCanCastleRight)
          board[BoardIndex] |= CastleRight;
        if (BlackCanCastleLeft)
          board[BoardIndex] |= CastleLeft;
      }
      BoardIndex++;
      break;
    }
    case 'K': {
      board[BoardIndex] = King | White;
      if (BoardIndex == WhiteKingStartPos) {
        if (WhiteCanCastleRight)
          board[BoardIndex] |= CastleRight;
        if (WhiteCanCastleLeft)
          board[BoardIndex] |= CastleLeft;
      }
      BoardIndex++;
      break;
    }
    case '/':
      break;
    default: {
      BoardIndex += Fen[i] - '0';
    }
    }
  }
}

int8_t MousePosToBoardIndex(Vector2 MousePos) {
  int index = 0;
  index += (int)MousePos.x / TILE_SIZE;
  index += (int)(MousePos.y / TILE_SIZE) * tilesInRow;
  return index;
}

int8_t *GetValidMoves(void) {
  switch (SelectedPiece & NameMask) {
  case (Pawn): {
    return PawnGetValidMoves(board, StartIndex, SelectedPiece);
  }
  case (Knight): {
    return KnightGetValidMoves(board, StartIndex, SelectedPiece);
  }
  case (Bishop): {
    return BishopGetValidMoves(board, StartIndex, SelectedPiece);
  }
  case (Rook): {
    return RookGetValidMoves(board, StartIndex, SelectedPiece);
  }
  case (Queen): {
    return QueenGetValidMoves(board, StartIndex, SelectedPiece);
  }
  case (King): {
    return KingGetValidMoves(board, StartIndex, SelectedPiece);
  }
  }
  return NULL;
}

void CheckCastleRights(void) {
  int8_t Color = SelectedPiece & ColorMask;
  if (Color == Black) {
    if ((SelectedPiece & NameMask) == King) {
      if (BlackCanCastleLeft && StopIndex == (BlackKingStartPos - 2)) {
        board[BlackRookLeftStartPos] = 0;
        board[BlackKingStartPos - 1] = Rook | Black;
      } else if (BlackCanCastleRight && StopIndex == (BlackKingStartPos + 2)) {
        board[BlackRookRightStartPos] = 0;
        board[BlackKingStartPos + 1] = Rook | Black;
      }
      BlackCanCastleLeft = false;
      BlackCanCastleRight = false;
      board[StopIndex] &= PieceMask;
    } else if ((SelectedPiece & NameMask) == Rook) {
      if (StartIndex == BlackRookRightStartPos) {
        BlackCanCastleRight = false;
        if ((board[BlackKingStartPos] & NameMask) == King) {
          board[BlackKingStartPos] &= (PieceMask | CastleLeftMask);
        }
      } else if (StartIndex == BlackRookLeftStartPos) {
        BlackCanCastleLeft = false;
        if ((board[BlackKingStartPos] & NameMask) == King) {
          board[BlackKingStartPos] &= (PieceMask | CastleRightMask);
        }
      }
    }

  } else if (Color == White) {
    if ((SelectedPiece & NameMask) == King) {
      if (WhiteCanCastleLeft && StopIndex == (WhiteKingStartPos - 2)) {
        board[WhiteRookLeftStartPos] = 0;
        board[WhiteKingStartPos - 1] = Rook | White;
      } else if (WhiteCanCastleRight && StopIndex == (WhiteKingStartPos + 2)) {
        board[WhiteRookRightStartPos] = 0;
        board[WhiteKingStartPos + 1] = Rook | White;
      }
      WhiteCanCastleLeft = false;
      WhiteCanCastleRight = false;
      board[StopIndex] &= PieceMask;
    } else if ((SelectedPiece & NameMask) == Rook) {
      if (StartIndex == WhiteRookRightStartPos) {
        WhiteCanCastleRight = false;
        if ((board[WhiteKingStartPos] & NameMask) == King) {
          board[WhiteKingStartPos] &= (PieceMask | CastleLeftMask);
        }
      } else if (StartIndex == WhiteRookLeftStartPos) {
        WhiteCanCastleLeft = false;
        if ((board[WhiteKingStartPos] & NameMask) == King) {
          board[WhiteKingStartPos] &= (PieceMask | CastleRightMask);
        }
      }
    }
  }
}

void MouseInput(void) {
  Vector2 MousePos = GetMousePosition();

  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    if (SelectedPiece == 0) {
      StartIndex = MousePosToBoardIndex(MousePos);
      SelectedPiece = board[StartIndex];
      // if ((SelectedPiece & ColorMask) == Black)
      // {
      //     MinimaxStarterV11(board, Black, ZobristTable);

      // }
      board[StartIndex] = 0;
    } else if ((SelectedPiece & ColorMask) != Black) {
      int8_t *ValidMoves = GetValidMoves();
      DrawValidMoves(ValidMoves);
    }

    switch (SelectedPiece & PieceMask) {
    case 0:
      break;
    case Pawn | Black: {
      DrawTexture(blackPawn, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Pawn | White: {
      DrawTexture(whitePawn, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Knight | Black: {
      DrawTexture(blackKnight, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Knight | White: {
      DrawTexture(whiteKnight, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Bishop | Black: {
      DrawTexture(blackBishop, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Bishop | White: {
      DrawTexture(whiteBishop, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Rook | Black: {
      DrawTexture(blackRook, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Rook | White: {
      DrawTexture(whiteRook, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Queen | Black: {
      DrawTexture(blackQueen, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case Queen | White: {
      DrawTexture(whiteQueen, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case King | Black: {
      DrawTexture(blackKing, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    case King | White: {
      DrawTexture(whiteKing, MousePos.x - TILE_SIZE / 2,
                  MousePos.y - TILE_SIZE / 2, WHITE);
      break;
    }
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && SelectedPiece != 0) {
    StopIndex = MousePosToBoardIndex(MousePos);
    int8_t *ValidMoves = GetValidMoves();

    if (IsInArray(StopIndex, ValidMoves, GetArrayLength(ValidMoves))) {
      board[StopIndex] = SelectedPiece;

      CheckCastleRights();
      if ((SelectedPiece & NameMask) == Pawn) {
        board[StopIndex] &= PieceMask;
        if ((SelectedPiece & ColorMask) == White && StopIndex / 8 == 0) {
          board[StopIndex] = White | Queen;
        } else if ((SelectedPiece & ColorMask) == Black && StopIndex / 8 == 7) {
          board[StopIndex] = Black | Queen;
        }
      }

      MinimaxStarterV10(board, Black, ZobristTable);

    } else {
      board[StartIndex] = SelectedPiece;
    }

    SelectedPiece = 0;
  }
}

int main(void) {

  FenToBoard(StartFen);
  KnightGenerateValidMoves();
  InitWindow(ScreenWidth, ScreenHeight, "chess");
  LoadTextures();
  ZobristTable = InitializeZobristHashing();
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();

    DrawBoard();
    MouseInput();
    DrawPieces();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

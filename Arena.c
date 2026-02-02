// #include "config.h"
// #include "pieces.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <string.h>
// #include <time.h>
// #include <fcntl.h>
// #include <unistd.h>

// #define MAX_LINE_LENGTH 1024
// #define MAX_FEN_LENGTH 256

// int8_t board[64];

// int FirstWins = 0;
// int SecondWins = 0;
// int Draws = 0;

// double FirstTime = 0;
// double SecondTime = 0;

// int MaxMoves = 100;

// bool BlackCanCastleRight = true;
// bool BlackCanCastleLeft = true;
// bool WhiteCanCastleRight = true;
// bool WhiteCanCastleLeft = true;

// uint64_t *ZobristTable;

// uint64_t rand64() {
//     uint64_t r;
//     int fd = open("/dev/urandom", O_RDONLY);
//     read(fd, &r, sizeof(r));
//     close(fd);
//     return r;
// }

// uint64_t* InitializeZobristHashing()
// {

//     static uint64_t ZobristTable[23 * 64];
//     srand(time(NULL));

//     for (int Piece = 0; Piece < 23; Piece ++)
//     {
//         for (int from = 0; from < 64; from ++)
//         {
//             ZobristTable[(Piece * 64) + from] = rand64();

//         }
//     }

//     return ZobristTable;
// }

// void ArenaPrintBoardToFile(int8_t *board, const char *filename) {
//     FILE *file = fopen(filename, "a"); // Open in append mode
//     if (file == NULL) {
//         printf("Error: Could not open file %s\n", filename);
//         return;
//     }

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

// void FenToBoard(const char *Fen)
// {
//     int BoardIndex = 0;
//     for (int i = 0; i < 64; i++)
//     {
//         board[i] = 0;
//     }
//     for (int i = 0; i < (int)strlen(Fen); i++)
//     {
//         switch (Fen[i])
//         {
//             case 'p':
//             {
//                 if (BoardIndex/8 == 1)
//                     board[BoardIndex] = Pawn | Black | Pawn2Up;
//                 else
//                     board[BoardIndex] = Pawn | Black;

//                 BoardIndex ++;
//                 break;
//             }
//             case 'P':
//             {
//                 if (BoardIndex/8 == 6)
//                     board[BoardIndex] = Pawn | White | Pawn2Up;
//                 else
//                     board[BoardIndex] = Pawn | White;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'n':
//             {
//                 board[BoardIndex] = Knight | Black;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'N':
//             {
//                 board[BoardIndex] = Knight | White;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'b':
//             {
//                 board[BoardIndex] = Bishop | Black;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'B':
//             {
//                 board[BoardIndex] = Bishop | White;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'r':
//             {
//                 board[BoardIndex] = Rook | Black;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'R':
//             {
//                 board[BoardIndex] = Rook | White;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'q':
//             {
//                 board[BoardIndex] = Queen | Black;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'Q':
//             {
//                 board[BoardIndex] = Queen | White;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'k':
//             {
//                 board[BoardIndex] = King | Black;
//                 BoardIndex ++;
//                 break;
//             }
//             case 'K':
//             {
//                 board[BoardIndex] = King | White;
//                 BoardIndex ++;
//                 break;
//             }
//             case '/':
//                 break;
//             default:
//             {
//                 BoardIndex += Fen[i] - '0';
//             }
//         }
//     }
// }

// bool Won(int8_t Color)
// {
//     bool won = true;
//     for (int i = 0; i < 64; i++)
//     {
//         if (board[i] == (King | (Color ^ ColorMask)))
//         {
//             won = false;
//         }
//     }
//     return won;
// }

// void BattleStarter1(int8_t StartColor, int8_t *board)
// {
//     struct timespec start, end;
//     double elapsed;
//     int moves = 0;
//     while (true)
//     {
//         clock_gettime(CLOCK_MONOTONIC, &start);
//         MinimaxStarterV11(board, StartColor, ZobristTable);
//         clock_gettime(CLOCK_MONOTONIC, &end);
//         elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//         FirstTime += elapsed;

//         if (Won(StartColor))
//         {
//             FirstWins ++;
//             break;
//         }

//         clock_gettime(CLOCK_MONOTONIC, &start);
//         MinimaxStarterV11(board, StartColor ^ ColorMask, ZobristTable);
//         clock_gettime(CLOCK_MONOTONIC, &end);
//         elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//         SecondTime += elapsed;

//         if (Won(StartColor ^ ColorMask))
//         {
//             SecondWins ++;
//             break;
//         }

//         moves ++;
//         if (moves > MaxMoves)
//         {
//             Draws ++;
//             break;
//         }

//     }

// }

// void BattleStarter2(int8_t StartColor, int8_t *board)
// {
//     struct timespec start, end;
//     double elapsed;
//     int moves = 0;
//     while (true)
//     {
//         clock_gettime(CLOCK_MONOTONIC, &start);
//         MinimaxStarterV11(board, StartColor, ZobristTable);
//         clock_gettime(CLOCK_MONOTONIC, &end);
//         elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//         SecondTime += elapsed;

//         if (Won(StartColor))
//         {
//             SecondWins ++;
//             break;
//         }

//         clock_gettime(CLOCK_MONOTONIC, &start);
//         MinimaxStarterV11(board, StartColor ^ ColorMask, ZobristTable);
//         clock_gettime(CLOCK_MONOTONIC, &end);
//         elapsed = (end.tv_sec - start.tv_sec) +
//                      (end.tv_nsec - start.tv_nsec) / 1e9;
//         FirstTime += elapsed;

//         if (Won(StartColor ^ ColorMask))
//         {
//             FirstWins ++;
//             break;
//         }

//         moves ++;
//         if (moves > MaxMoves)
//         {
//             Draws ++;
//             break;
//         }

//     }

// }

// int main() {
//     FILE *file;
//     char line[MAX_LINE_LENGTH];
//     int8_t MaximizingColor;

//     ZobristTable = InitializeZobristHashing();

//     file = fopen("C/chess/fenExualPos.txt", "r");  // Open file for reading
//     if (file == NULL) {
//         perror("Error opening file");
//         return 1;
//     }

//     while (fgets(line, sizeof(line), file)) {
//         // Clean newline at end
//         line[strcspn(line, "\n")] = 0;

//         char Fen[MAX_FEN_LENGTH] = {0};
//         char colorChar = 0;

//         // Tokenize the line by space
//         char *token = strtok(line, " ");
//         if (token != NULL) {
//             strncpy(Fen, token, MAX_FEN_LENGTH - 1);  // Copy FEN
//         }

//         token = strtok(NULL, " ");
//         if (token != NULL) {
//             colorChar = token[0];  // Should be 'w' or 'b'
//         }

//         MaximizingColor = (colorChar == 'b') ? Black : White;

//         FenToBoard(Fen);
//         ZobristTable = InitializeZobristHashing();
//         // first starts
//         BattleStarter1(MaximizingColor, board);
//         // second starts
//         FenToBoard(Fen);
//         ZobristTable = InitializeZobristHashing();
//         BattleStarter2(MaximizingColor, board);

//     }

//     fclose(file);
//     FILE *file2 = fopen("output.txt", "a");
//     fprintf(file2, "First #%d\n", FirstWins);
//     fprintf(file2, "Secodn #%d\n", SecondWins);
//     fprintf(file2, "Draws #%d\n", Draws);
//     fprintf(file2, "Time1 #%f\n", FirstTime);
//     fprintf(file2, "Time2 #%f\n", SecondTime);
//     fclose(file2);
//     return 0;
// }

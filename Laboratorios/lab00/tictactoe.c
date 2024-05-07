#include <stdbool.h> /* Tipo bool             */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdlib.h>  /* exit() y EXIT_FAILURE */

#include <assert.h> /* assert() */

#define BOARD_LENGTH 5

#define CELL_MAX (BOARD_LENGTH * BOARD_LENGTH - 1)

void print_sep(int length) {
  printf("\t ");
  for (int i = 0; i < length; i++)
    printf("................");
  printf("\n");
}

void print_board(char board[BOARD_LENGTH][BOARD_LENGTH]) {
  int cell = 0;

  print_sep(BOARD_LENGTH);
  for (int row = 0; row < BOARD_LENGTH; ++row) {
    for (int column = 0; column < BOARD_LENGTH; ++column) {
      printf("\t | %d: %c ", cell, board[row][column]);
      ++cell;
    }
    printf("\t | \n");
    print_sep(BOARD_LENGTH);
  }
}
// ------------------------------
bool has_free_cell(char board[BOARD_LENGTH][BOARD_LENGTH]) {
  int row = 0;
  bool free_cell = false;

  while (row < BOARD_LENGTH && !free_cell) {
    int column = 0;
    while (column < BOARD_LENGTH && !free_cell) {
      if (board[row][column] == '-') {
        free_cell = true;
      }
      column++;
    }
    row++;
  }

  return free_cell;
}

char get_winner(char board[BOARD_LENGTH][BOARD_LENGTH]) {
  char winner = '-';

  // Buscar en filas
  int fila = 0;
  while (fila < BOARD_LENGTH && winner == '-') {
    char first_char_in_fila = board[fila][0];
    int columna = 0;
    bool fila_win = true;
    while (columna < BOARD_LENGTH && fila_win) {
      if (board[fila][columna] != first_char_in_fila ||
          board[fila][columna] == '-') {
        fila_win = false;
      }
      columna++;
    }
    if (fila_win) {
      winner = first_char_in_fila;
    }
    fila++;
  }

  // Buscar en columnas
  int columna = 0;
  while (columna < BOARD_LENGTH && winner == '-') {
    char first_char_in_columna = board[0][columna];
    int fila = 0;
    bool columna_win = true;
    while (fila < BOARD_LENGTH && columna_win) {
      if (board[fila][columna] != first_char_in_columna ||
          board[fila][columna] == '-') {
        columna_win = false;
      }
      fila++;
    }
    if (columna_win) {
      winner = first_char_in_columna;
    }
    columna++;
  }

  // Buscar en diagonal principal
  int main_diagonal_fila = 0;
  int main_diagonal_columna = 0;
  char first_char_in_main_diagonal =
      board[main_diagonal_fila][main_diagonal_columna];
  bool main_diagonal_win = true;
  while (main_diagonal_fila < BOARD_LENGTH &&
         main_diagonal_columna < BOARD_LENGTH && main_diagonal_win) {
    if (board[main_diagonal_fila][main_diagonal_columna] !=
            first_char_in_main_diagonal ||
        board[main_diagonal_fila][main_diagonal_columna] == '-') {
      main_diagonal_win = false;
    }
    main_diagonal_fila++;
    main_diagonal_columna++;
  }
  if (main_diagonal_win) {
    winner = first_char_in_main_diagonal;
  }

  // Buscar en diagonal secundaria
  int secondary_diagonal_fila = BOARD_LENGTH - 1;
  int secondary_diagonal_columna = BOARD_LENGTH - 1;
  char first_char_in_secondary_diagonal =
      board[secondary_diagonal_fila][secondary_diagonal_columna];
  bool secondary_diagonal_win = true;
  while (secondary_diagonal_fila >= 0 && secondary_diagonal_columna >= 0 &&
         secondary_diagonal_win) {
    if (board[secondary_diagonal_fila][secondary_diagonal_columna] !=
            first_char_in_secondary_diagonal ||
        board[secondary_diagonal_fila][secondary_diagonal_columna] == '-') {
      secondary_diagonal_win = false;
    }
    secondary_diagonal_fila--;
    secondary_diagonal_columna--;
  }
  if (secondary_diagonal_win) {
    winner = first_char_in_secondary_diagonal;
  }

  return winner;
}
// ------------------------------

void init_board(char board[BOARD_LENGTH][BOARD_LENGTH]) {
  int fila = 0;
  int columna = 0;

  while (fila < BOARD_LENGTH) {
    board[fila][columna] = '-';
    while (columna < BOARD_LENGTH) {
      board[fila][columna] = '-';
      columna++;
    }
    columna = 0;
    fila++;
  }
}

int main(void) {
  printf("TicTacToe [InCoMpLeTo :'(]\n");

  char board[BOARD_LENGTH][BOARD_LENGTH];
  init_board(board);

  char turn = 'X';
  char winner = '-';
  int cell = 0;
  while (winner == '-' && has_free_cell(board)) {
    print_board(board);
    printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
           CELL_MAX);
    int scanf_result = scanf("%d", &cell);
    if (scanf_result <= 0) {
      printf("Error al leer un número desde teclado\n");
      exit(EXIT_FAILURE);
    }
    if (cell >= 0 && cell <= CELL_MAX) {
      int row = cell / BOARD_LENGTH;
      int colum = cell % BOARD_LENGTH;
      if (board[row][colum] == '-') {
        board[row][colum] = turn;
        turn = turn == 'X' ? 'O' : 'X';
        winner = get_winner(board);
      } else {
        printf("\nCelda ocupada!\n");
      }
    } else {
      printf("\nCelda inválida!\n");
    }
  }
  print_board(board);
  if (winner == '-') {
    printf("Empate!\n");
  } else {
    printf("Ganó %c\n", winner);
  }
  return 0;
}

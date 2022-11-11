#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *transpositionalCipher(char plainText[], int key, char action[]);
int charactersCount(char text[]);
void pause();
bool requireKey(int key);
void displayMatrix(char **matrix, int colCount, int rowCount);

void main() {
  // Initial variable declaration
  char plainText[MAX];
  char *cipherText = NULL, *newPlainText = NULL;
  int choice, key = 0;

  // Menu page
  do {
    // system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set key (row length)\n");
    printf("[3] Encrypt plain text\n");
    printf("[4] Decrypt cipher text\n");
    printf("---------------------\n");
    printf("Plain text: %s\n", plainText);
    printf("Key: %d\n", key);
    printf("Cipher text: %s\n", cipherText);
    printf("New plain text: %s\n", newPlainText);
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user plain text input
    if (choice == 1) {
      printf("Set plain text: ");
      fflush(stdin);
      scanf("%[^\n]", plainText);
    }

    // Request user key input
    if (choice == 2) {
      printf("Set key (row length): ");
      fflush(stdin);
      scanf("%d", &key);
    }

    // Run polyalphabetic encryption
    if (choice == 3) {
      // Fails the cipher if key does not exist
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (cipherText != NULL) {
          free(cipherText);
        }
        cipherText = transpositionalCipher(plainText, key, "encrypt");
        printf("Cipher Text: %s\n", cipherText);
      }
    }

    // Run polyalphabetic decryption
    if (choice == 4) {
      // Fails the cipher if key is not set or >= 0
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (newPlainText != NULL) {
          free(newPlainText);
        }
        newPlainText = transpositionalCipher(cipherText, key, "decrypt");
        printf("Plain Text: %s\n", newPlainText);
      }
    }

    pause();
  } while (choice != 0);
}

/*
  Vigenère cipher is the sequence of Caesar ciphers with different
  transformations on each character of the plain text depending on the current
  character selected in the key. The current character of the key is determined
  by looping through all the characters of the key string iteratively similar to
  a circular array traversal.

  To apply this cipher, manipulate character ASCII values with the ff. formulas:
  ENCRYPTION: shiftCipher(CHAR) = (TEXT_CHAR - FIRST_VAL + (KEY_CHAR -
  FIRST_VAL)) % 10 + FIRST_VAL DECRYPTION: shiftCipher(CHAR) = (TEXT_CHAR -
  FIRST_VAL + (LAST_VAL - (KEY_CHAR - FIRST_VAL))) % 10 + FIRST_VAL

  The following block of code below follows the formula
  of the Vigenère cipher in implementing the polyalphabeic cipher.

  Ex. For simplicity, in numbers 1 - 10, Vigenère cipher encrypts and decrypts
  plain texts by shifting each number(N) by shift(S), where N = 3 and S = 2,
  follows the ff. pattern:
  * shiftCipher(3) = (3 - 1 + 2) % 10 + 1
  *             n  = (4) % 10 + 1
  *             n  = 4 + 1
  *             n  = 5
  * shiftCipher(5) = (5 - 1 + (10 - 2)) % 10 + 1
  *             n  = (5 - 1 + 8) % 10 + 1
  *             n  = (12) % 10 + 1
  *             n  = 2 + 1
  *             n  = 3
*/
char *transpositionalCipher(char plainText[], int colCount, char action[]) {
  int textIdx, rowIdx, colIdx, rowCount = charactersCount(plainText) / colCount;
  // Allocate pointer memory
  char *result = calloc(strlen(plainText), sizeof(char));
  char **matrix = calloc(rowCount, sizeof(char *));
  // guard clause to fail cipher if memory wasnt allocated
  if (matrix == NULL || result == NULL) {
    printf("NULL");
    return NULL;
  }
  printf("1");

  for (rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    matrix[rowIdx] = calloc(colCount, sizeof(char));
  }

  printf("2");

  for (textIdx = 0, colIdx = 0, rowIdx = 0; textIdx <= strlen(plainText);
       textIdx++) {
    if (plainText[textIdx] == ' ') {
      textIdx++;
    } else {
      matrix[rowIdx][colIdx] = plainText[textIdx];
    }
    printf("test");
    if (colIdx == colCount - 1) {
      rowIdx++;
      colIdx = 0;
    } else {
      colIdx++;
    }
  }

  displayMatrix(matrix, colCount, rowCount);
  printf("3");

  for (colIdx = 0, rowCount = 0, textIdx = 0; textIdx <= strlen(plainText);
       textIdx++) {
    if (plainText[textIdx] == ' ') {
      result[textIdx] = plainText[textIdx];
    } else {
      result[textIdx] = matrix[colIdx][rowIdx];
      colIdx++;

      if (rowIdx == rowCount - 1) {
        rowIdx = 0;
        colIdx++;
      } else {
        rowIdx++;
      }
    }

    return result;
  }
}

int charactersCount(char text[]) {
  int count = 0;
  for (int textIdx = 0; textIdx <= strlen(text); textIdx++) {
    if (text[textIdx] != ' ') {
      count++;
    }
  }
  return count;
}

void pause() {
  printf("**press any key to continue**\n");
  getch();
}

/*
  Function to require key input from user
*/
bool requireKey(int key) {
  if (key <= 0) {
    printf("Please enter a valid key!\n");
    return false;
  }

  return true;
}

/*
    Function to display the current values in the matrix. This function is for
   debug only
*/
void displayMatrix(char **matrix, int colCount, int rowCount) {
  printf("matrix: \n");
  for (int rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    for (int colIdx = 0; colIdx < colCount; colIdx++) {
      printf("[%c] ", matrix[rowIdx][colIdx]);
    }
    printf("\n");
  }
  printf("\n");
}

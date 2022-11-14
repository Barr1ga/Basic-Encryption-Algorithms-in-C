#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ENCRYPT 1
#define DECRYPT 0

char *encrypt(char plainText[], char key[], char pad);
char *decrypt(char cipherText[], char key[], char pad);
char *getFileContent(char fileName[]);
bool writeFileContent(char *text, char fileName[]);
void pause();
bool requireKey(char key[]);
void displayMatrix(char **matrix, int colCount, int rowCount);
double charactersCount(char text[]);

void main() {
  // Initial variable declaration
  char *cipherText = NULL, *newPlainText = NULL, *key = NULL, *plainText = NULL,
       pad = (char)0;
  int choice;

  // Menu page
  do {
    // system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Set key\n");
    printf("[4] Set key from file\n");
    printf("[5] Set cipher text\n");
    printf("[6] Set cipher text from file\n");
    printf("[7] Encrypt plain text\n");
    printf("[8] Decrypt cipher text\n");
    printf("[9] Save plain text to file\n");
    printf("[10] Save cipher to file\n");
    printf("[11] Save key to file\n");
    printf("[12] Save new plain text to file\n");
    printf("---------------------\n");
    printf("Plain text: %s\n", plainText);
    printf("Key: %s\n", key);
    printf("Cipher text: %s\n", cipherText);
    printf("New plain text: %s\n", newPlainText);
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user plain text input
    if (choice == 1) {
      if (plainText != NULL) {
        free(plainText);
      }
      plainText = calloc(MAX, sizeof(char));
      printf("Set plain text: ");
      fflush(stdin);
      scanf("%[^\n]", plainText);
    }

    // Set plain text from file
    if (choice == 2) {
      char fileName[MAX];
      if (plainText != NULL) {
        free(plainText);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      plainText = getFileContent(fileName);
      printf("Plain text: %s\n", plainText);
    }

    // Request user key input
    if (choice == 3) {
      printf("Set key: ");
      fflush(stdin);
      key = generateKey(plainText);
      printf("Key: %s\n", key);
    }

    // Request user key from file
    if (choice == 4) {
      char fileName[MAX];
      if (key != NULL) {
        free(key);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      key = getFileContent(fileName);
      printf("Key: %s\n", key);
    }

    // Request user cipher text input
    if (choice == 5) {
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = calloc(MAX, sizeof(char));
      printf("Set cipher text: ");
      fflush(stdin);
      scanf("%[^\n]", cipherText);
    }

    // Set cipher text from file
    if (choice == 6) {
      char fileName[MAX];
      if (cipherText != NULL) {
        free(cipherText);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      cipherText = getFileContent(fileName);
      printf("Cipher text: %s\n", cipherText);
    }

    // Run polyalphabetic encryption
    if (choice == 7) {
      // Fails the cipher if key does not exist
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (cipherText != NULL) {
          free(cipherText);
        }
        cipherText = encrypt(plainText, key, 'A');
        printf("Cipher Text: %s\n", cipherText);
      }
    }

    // Run polyalphabetic decryption
    if (choice == 8) {
      // Fails the cipher if key is not set or >= 0
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (newPlainText != NULL) {
          free(newPlainText);
        }
        newPlainText = decrypt(cipherText, key, 'B');
        printf("Plain Text: %s\n", newPlainText);
      }
    }

    // Save plain text to file
    if (choice == 9) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(plainText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save cipher text to file
    if (choice == 10) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(cipherText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save key to file
    if (choice == 11) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(key, fileName)) {
        printf("Saved\n");
      }
    }

    // Save new plain text to file
    if (choice == 12) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(newPlainText, fileName)) {
        printf("Saved\n");
      }
    }
    pause();
  } while (choice != 0);
}

/*
  In cryptography, a transposition cipher, also known as columnar transposition
  cipher, is a simple and easy to implement cipher. This cipher follows a simple
  rule for mixing up the characters in the plaintext to form the ciphertext.

  ENCRYPTION:
  To apply this cipher, the characters in the text string is arranged in a
  level-order format in a matrix whose size is defined by the ff. formula:
  ROWS = TOTAL_CHARACTERS / COLS, where COLS is equals to the length of
  the key string.

  The arranged characters in the matrix are then formed into the cipher through
  spelling each columns depending on the ASCII value of each character in the
  key

  DECRYPTION:
  The same way, the cipher string is arranged in the matrix in each column
  depending on the ASCII values of each character in the key. The arranged
  characters are then spelled in a level-order format into the new text string.
*/
char *encrypt(char plainText[], char key[], char pad) {
  int textIdx, rowIdx, colIdx, colCount = strlen(key), rowCount;
  // The total count of characters is extracted from the text string
  rowCount = ceil(((double)charactersCount(plainText)) / colCount);
  printf("rowCount: %d", rowCount);
  // Allocate pointer memory
  bool *keyChecker = calloc(strlen(key), sizeof(bool));
  char *result = calloc(strlen(plainText), sizeof(char));
  char **matrix = calloc(rowCount, sizeof(char *));

  // guard clause to fail cipher if memory wasnt allocated
  if (matrix == NULL || result == NULL || keyChecker == NULL) {
    return NULL;
  }

  // Allocate memory for each index in each rows of the matrix
  for (rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    matrix[rowIdx] = calloc(colCount, sizeof(char));
  }

  // Arrange the text string into the matrix in level-order format. To start,
  // loop through the text string
  for (textIdx = 0, colIdx = 0, rowIdx = 0; textIdx < strlen(plainText);
       textIdx++) {
    // If the current character is a displayable character, copy that character
    // into the matrix
    if (isgraph(plainText[textIdx]) && plainText[textIdx] != pad) {
      matrix[rowIdx][colIdx] = plainText[textIdx];

      // Move to the next row in the matrix if the end column is reached
      if (colIdx == colCount - 1) {
        rowIdx++;
        colIdx = 0;
      } else {
        colIdx++;
      }
    }
  }

  // pad remaining spaces with (makeshift empty character)
  for (; rowIdx < rowCount && colIdx < colCount; colIdx++) {
    matrix[rowIdx][colIdx] = pad;
  }

  // Spell the characters in the matrix to form the cipher. To start, loop
  // through the text string
  for (int keyIdx, colIdx = 0, rowIdx = rowCount, textIdx = 0;
       textIdx < strlen(plainText); textIdx++) {
    // Copy the current character if it is a space character
    if (isspace(plainText[textIdx])) {
      result[textIdx] = plainText[textIdx];
    } else {
      if (rowIdx == rowCount) {
        // Identify unvisited index of least ASCII value character in key
        for (char min = '~', keyIdx = 0; keyIdx < strlen(key); keyIdx++) {
          if (keyChecker[keyIdx] == false && key[keyIdx] <= min) {
            min = key[keyIdx];
            // Select current index as the column to fill
            colIdx = keyIdx;
          }
        }
        // Mark that index as visited
        keyChecker[colIdx] = true;
        rowIdx = 0;
      }

      if (isgraph(matrix[rowIdx][colIdx])) {
        result[textIdx] = matrix[rowIdx][colIdx];
      } else {
        textIdx--;
      }

      rowIdx++;
    }
  }

  // problem: cipher should skip the pad characters.

  return result;
}

char *decrypt(char cipherText[], char key[], char pad) {
  int textIdx, rowIdx, colIdx, colCount = strlen(key), rowCount;
  // The total count of characters is extracted from the text string
  rowCount = ceil(((double)charactersCount(cipherText)) / colCount);

  // Allocate pointer memory
  bool *keyChecker = calloc(strlen(key), sizeof(bool));
  char *result = calloc(strlen(cipherText), sizeof(char));
  char **matrix = calloc(rowCount, sizeof(char *));

  // guard clause to fail cipher if memory wasnt allocated
  if (matrix == NULL || result == NULL || keyChecker == NULL) {
    return NULL;
  }

  // Allocate memory for each index in each rows of the matrix
  for (rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    matrix[rowIdx] = calloc(colCount, sizeof(char));
  }

  // Arrange the text string into the matrix in level-order format. To start,
  // loop through the text string
  for (textIdx = 0, rowIdx = rowCount; textIdx < strlen(cipherText);
       textIdx++) {
    // Move to the next character in the text string if it is a space character
    if (isspace(cipherText[textIdx])) {
      textIdx++;
    }

    if (rowIdx == rowCount) {
      // Identify unvisited index of least ASCII value character in key
      for (char min = '~', keyIdx = 0; keyIdx < strlen(key); keyIdx++) {
        if (keyChecker[keyIdx] == false && key[keyIdx] <= min) {
          min = key[keyIdx];
          colIdx = keyIdx;
        }
      }
      // Mark that index as visited
      keyChecker[colIdx] = true;
      rowIdx = 0;
    }
    matrix[rowIdx][colIdx] = cipherText[textIdx];
    rowIdx++;
  }

  // pad remaining spaces (makeshift empty character)
  for (; rowIdx < rowCount && colIdx < colCount; colIdx++) {
    matrix[rowCount - 1][colIdx] = pad;
  }

  // Spell the characters in the matrix in level-order format to form the new
  // text string. To start, loop through the text string
  for (textIdx = 0, rowIdx = 0, colIdx = 0; textIdx < strlen(cipherText);
       textIdx++) {
    if (cipherText[textIdx] == ' ') {
      result[textIdx] = cipherText[textIdx];
      textIdx++;
    }

    // If the current character is a displayable character, copy that character
    // into the text string (result)
    if (isgraph(matrix[rowIdx][colIdx])) {
      result[textIdx] = matrix[rowIdx][colIdx];
    } else {
      textIdx--;
    }

    // Move to the next column in the matrix if the end row is reached
    if (colIdx == colCount - 1) {
      rowIdx++;
      colIdx = 0;
    } else {
      colIdx++;
    }
  }

  return result;
}

/*
 Function to read contents from a file into a text string
*/
char *getFileContent(char fileName[]) {
  int size = MAX, textIdx = 0;
  char *result = calloc(size, sizeof(char)), *temp, character;
  FILE *file = fopen(fileName, "r");

  // Guard clause to fail file reading if memory wasnt allocated or file pointer
  // returns null
  if (result == NULL || file == NULL) {
    return NULL;
  }

  // Loop through the file contents by character
  while ((character = fgetc(file)) != EOF) {
    // Reallocate memory to fit data if index reaches the last byte
    if (textIdx == size - 1) {
      size += MAX;
      temp = realloc(result, sizeof(char) * size);
      if (temp != NULL) {
        result = temp;
        free(temp);
      }
    }

    // Save current character from file
    result[textIdx] = character;
    textIdx++;
  }

  // Close file pointer
  fclose(file);
  result[textIdx] = '\0';
  return result;
}

/*
 Function to write contents from a text string into a file
*/
bool writeFileContent(char *text, char fileName[]) {
  FILE *file = fopen(fileName, "w");

  // Guard clause to fail writing if text string and file pointer is null
  if (file == NULL || text == NULL) {
    return false;
  }

  // Write into file
  fprintf(file, "%s", text);

  // Close file pointer
  fclose(file);
  return true;
}

void pause() {
  printf("**press any key to continue**\n");
  getch();
}

/*
  Function to require key input from user
*/
bool requireKey(char *key) {
  if (key == NULL) {
    printf("Please enter a valid key!\n");
    return false;
  }

  return true;
}

double charactersCount(char text[]) {
  double count = 0;
  for (int textIdx = 0; textIdx < strlen(text); textIdx++) {
    if (!isspace(text[textIdx])) {
      count += 1;
    }
  }
  return count;
}

/*
    Function to display the current values in the matrix. This function is for
   debug only
*/
void displayMatrix(char **matrix, int colCount, int rowCount) {
  printf("\n");

  for (int rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    for (int colIdx = 0; colIdx < colCount; colIdx++) {
      printf("[%c] ", matrix[rowIdx][colIdx]);
    }
    printf("\n");
  }
  printf("\n");
}

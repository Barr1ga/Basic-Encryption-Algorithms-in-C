#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *shiftCipher(char text[], int shift, char action[]);
char *getFileContent(char fileName[]);
bool writeFileContent(char *text, char fileName[]);
void pause();
bool requireShift(int shift);

void main() {
  // Initial variable declaration
  char *text = NULL, *cipher = NULL, *decryptedDoc = NULL;
  int choice, shift = 0;

  // Menu page
  do {
    system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Set shift count\n");
    printf("[4] Set cipher text\n");
    printf("[5] Set cipher text from file\n");
    printf("[6] Encrypt plain text\n");
    printf("[7] Decrypt plain text\n");
    printf("[8] Save plain text to file\n");
    printf("[9] Save cipher to file\n");
    printf("[10] Save new plain text to file\n");
    printf("---------------------\n");
    printf("Plain text: %s\n", text);
    printf("Shift count: %d\n", shift);
    printf("Cipher text: %s\n", cipher);
    printf("New plain text: %s\n", decryptedDoc);
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user key input
    if (choice == 1) {
      if (text != NULL) {
        free(text);
      }
      text = calloc(MAX, sizeof(char));
      printf("Set plain text: ");
      fflush(stdin);
      scanf("%[^\n]", text);
    }

    // Set plain text from file
    if (choice == 2) {
      char fileName[MAX];
      if (text != NULL) {
        free(text);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      text = getFileContent(fileName);
    }

    // Request user shift count input
    if (choice == 3) {
      printf("Enter shift count: ");
      fflush(stdin);
      scanf("%d", &shift);
    }

    // Request user cipher text input
    if (choice == 4) {
      if (cipher != NULL) {
        free(cipher);
      }
      cipher = calloc(MAX, sizeof(char));
      printf("Set cipher text: ");
      fflush(stdin);
      scanf("%[^\n]", cipher);
    }

    // Set cipher text from file
    if (choice == 5) {
      char fileName[MAX];
      if (cipher != NULL) {
        free(cipher);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      cipher = getFileContent(fileName);
      printf("Cipher text: %s\n", cipher);
    }

    // Run shift encryption
    if (choice == 6) {
      // Fails the cipher if key does not exist
      if (requireShift(shift) == true) {
        printf("Shift count [%d]\n", shift);
        // If exists, free allocated memory
        if (cipher != NULL) {
          free(cipher);
        }
        cipher = shiftCipher(text, shift, "encrypt");
        printf("Cipher: %s\n", cipher);
      }
    }

    // Run shift decryption
    if (choice == 7) {
      // Fails the cipher if key does not exist
      if (requireShift(shift) == true) {
        printf("Shift count [%d]\n", shift);
        // If exists, free allocated memory
        if (decryptedDoc != NULL) {
          free(decryptedDoc);
        }
        decryptedDoc = shiftCipher(cipher, shift, "decrypt");
        printf("Decrypted document: %s\n", decryptedDoc);
      }
    }

    // Save plain text to file
    if (choice == 8) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(text, fileName)) {
        printf("Saved\n");
      }
    }

    // Save cipher text to file
    if (choice == 9) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(cipher, fileName)) {
        printf("Saved\n");
      }
    }

    // Save new plain text to file
    if (choice == 10) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(decryptedDoc, fileName)) {
        printf("Saved\n");
      }
    }
    pause();
  } while (choice != 0);
}

/*
  A shift cipher involves replacing each letter in the message by a letter that
  is some fixed number of positions further along in the alphabet.

  To apply this cipher, manipulate character ASCII values with the ff. formulas:
  ENCRYPTION: shiftCipher(CHAR) = (CHAR - FIRST_VAL + SHIFT) % 10 + FIRST_VAL
  DECRYPTION: shiftCipher(CHAR) = (CHAR - FIRST_VAL + (LAST_VAL - SHIFT)) % 10 +
  FIRST_VAL

  The following block of code below follows the formula
  of the shift cipher.

  Ex. For simplicity, in numbers 1 - 10, shift cipher encrypts and decrypts
  plain texts by shifting each number(N) by shift(S), where N = 3 and S = 2,
  follows the ff.
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
char *shiftCipher(char text[], int shift, char action[]) {
  int i;
  char *result = calloc(strlen(text), sizeof(char));
  if (result != NULL) {
    shift = strcmp(action, "encrypt") == 0 ? shift : 26 - shift;
    for (i = 0; i <= strlen(text); i++) {
      // If current character is digit, shift character ASCII values
      if (isalnum(text[i])) {
        if (isdigit(text[i])) {
          result[i] = (text[i] - '0' + shift) % 10 + '0';
        }
        // If current character is digit, shift character ASCII values
        if (islower(text[i])) {
          result[i] = (text[i] - 'a' + shift) % 26 + 'a';
        }
        // If current character is digit, shift character ASCII values
        if (isupper(text[i])) {
          result[i] = (text[i] - 'A' + shift) % 26 + 'A';
        }
        // If current character is neither, directly copy
      } else {
        result[i] = text[i];
      }
    }

    return result;
  }
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
  Function to require shift input from user
*/
bool requireShift(int shift) {
  if (shift == 0) {
    printf("Please enter a valid shift count!\n");
    return false;
  }

  return true;
}
